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

def_primobject_3_slot(graph_node, label, edges_left_node_hash_edge_hash, edges_right_node_hash_edge_hash);

f2ptr f2__graph_node__new(f2ptr cause, f2ptr label) {
  f2ptr edges_left_node_hash_edge_hash  = f2__ptypehash__new(cause);
  f2ptr edges_right_node_hash_edge_hash = f2__ptypehash__new(cause);
  return f2graph_node__new(cause, label, edges_left_node_hash_edge_hash, edges_right_node_hash_edge_hash);
}
def_pcfunk1(graph_node__new, label, return f2__graph_node__new(this_cause, label));

boolean_t raw__graph_node__has_edges(f2ptr cause, f2ptr this) {
  f2ptr edges_left_node_hash_edge_hash                = f2__graph_node__edges_left_node_hash_edge_hash( cause, this);
  f2ptr edges_right_node_hash_edge_hash               = f2__graph_node__edges_right_node_hash_edge_hash(cause, this);
  f2ptr edges_left_node_hash_edge_hash__key_count     = f2__ptypehash__key_count(cause, edges_left_node_hash_edge_hash);
  f2ptr edges_right_node_hash_edge_hash__key_count    = f2__ptypehash__key_count(cause, edges_right_node_hash_edge_hash);
  u64   edges_left_node_hash_edge_hash__key_count__i  = f2integer__i(edges_left_node_hash_edge_hash__key_count, cause);
  u64   edges_right_node_hash_edge_hash__key_count__i = f2integer__i(edges_right_node_hash_edge_hash__key_count, cause);
  return ((edges_left_node_hash_edge_hash__key_count__i != 0) || (edges_right_node_hash_edge_hash__key_count__i != 0));
}

f2ptr f2__graph_node__has_edges(f2ptr cause, f2ptr this) {
  if (! raw__graph_node__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__graph_node__has_edges(cause, this));
}
def_pcfunk1(graph_node__has_edges, this, return f2__graph_node__has_edges(this_cause, this));

// graph_edge

def_primobject_3_slot(graph_edge, label, left_node, right_node);

f2ptr f2__graph_edge__new(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return f2graph_edge__new(cause, label, left_node, right_node);
}
def_pcfunk3(graph_edge__new, label, left_node, right_node, return f2__graph_edge__new(this_cause, label, left_node, right_node));



// graph_edge_type

def_primobject_3_slot(graph_edge_type, label, left_node_hash, right_node_hash);

f2ptr f2__graph_edge_type__new(f2ptr cause, f2ptr label) {
  f2ptr left_node_hash  = f2__ptypehash__new(cause);
  f2ptr right_node_hash = f2__ptypehash__new(cause);
  return f2graph_edge_type__new(cause, label, left_node_hash, right_node_hash);
}
def_pcfunk1(graph_edge_type__new, label, return f2__graph_edge_type__new(this_cause, label));


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

f2ptr raw__graph__lookup_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  f2ptr node_label_hash = f2__graph__node_label_hash(cause, this);
  f2ptr node            = f2__ptypehash__lookup(cause, node_label_hash, node_label);
  return node;
}

f2ptr f2__graph__lookup_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__lookup_node(cause, this, node_label);
}
def_pcfunk2(graph__lookup_node, this, node, return f2__graph__lookup_node(this_cause, this, node));

f2ptr raw__graph__add_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  f2ptr node_label_hash = f2__graph__node_label_hash(cause, this);
  f2ptr node            = f2__ptypehash__lookup(cause, node_label_hash, node_label);
  if (node == nil) {
    node = f2__graph_node__new(cause, node_label);
    f2__ptypehash__add(cause, node_label_hash, node_label, node);
  }
  return node;
}

f2ptr f2__graph__add_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__add_node(cause, this, node_label);
}
def_pcfunk2(graph__add_node, this, node_label, return f2__graph__add_node(this_cause, this, node_label));


boolean_t raw__graph__remove_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  f2ptr node_label_hash = f2__graph__node_label_hash(cause, this);
  f2ptr node            = f2__ptypehash__lookup(cause, node_label_hash, node_label);
  if (! node) {
    return boolean__false;
  }
  {
    f2ptr edges_seq  = nil;
    {
      f2ptr edges_left_node_hash_edge_hash = f2__graph_node__edges_left_node_hash_edge_hash(cause, node);
      ptypehash__value__iteration(cause, edges_left_node_hash_edge_hash, edges_left_node_hash,
				  ptypehash__value__iteration(cause, edges_left_node_hash, edges,
							      {
								f2ptr edges_iter = edges;
								while (edges_iter) {
								  f2ptr edge = f2__cons__car(cause, edges_iter);
								  edges_seq = f2cons__new(cause, edge, edges_seq);
								  edges_iter = f2__cons__cdr(cause, edges_iter);
								}
							      }
							      ));
    }
    {
      f2ptr edges_iter = edges_seq;
      while (edges_iter) {
	f2ptr edge = f2__cons__car(cause, edges_iter);
	f2ptr edge_label = f2__graph_edge__label(cause, edge);
	f2ptr left_node  = f2__graph_edge__left_node(cause, edge);
	f2ptr right_node = f2__graph_edge__right_node(cause, edge);
	f2ptr left_node_label = f2__graph_node__label(cause, left_node);
	f2ptr right_node_label = f2__graph_node__label(cause, right_node);
	raw__graph__remove_edge(cause, this, edge_label, left_node_label, right_node_label);
	edges_iter = f2__cons__cdr(cause, edges_iter);
      }
    }
  }
  {
    f2ptr edges_seq  = nil;
    {
      f2ptr edges_right_node_hash_edge_hash = f2__graph_node__edges_right_node_hash_edge_hash(cause, node);
      ptypehash__value__iteration(cause, edges_right_node_hash_edge_hash, edges_right_node_hash,
				  ptypehash__value__iteration(cause, edges_right_node_hash, edges,
							      {
								f2ptr edges_iter = edges;
								while (edges_iter) {
								  f2ptr edge = f2__cons__car(cause, edges_iter);
								  edges_seq = f2cons__new(cause, edge, edges_seq);
								  edges_iter = f2__cons__cdr(cause, edges_iter);
								}
							      }
							      ));
    }
    {
      f2ptr edges_iter = edges_seq;
      while (edges_iter) {
	f2ptr edge = f2__cons__car(cause, edges_iter);
	f2ptr edge_label = f2__graph_edge__label(cause, edge);
	f2ptr left_node  = f2__graph_edge__left_node(cause, edge);
	f2ptr right_node = f2__graph_edge__right_node(cause, edge);
	f2ptr left_node_label = f2__graph_node__label(cause, left_node);
	f2ptr right_node_label = f2__graph_node__label(cause, right_node);
	raw__graph__remove_edge(cause, this, edge_label, left_node_label, right_node_label);
	edges_iter = f2__cons__cdr(cause, edges_iter);
      }
    }
  }
  f2ptr root_node = f2__graph__root_node(cause, this);
  if (root_node != nil) {
    f2ptr root_node__label = f2__graph_node__label(cause, root_node);
    if (raw__eq(cause, root_node__label, node_label)) {
      raw__graph__make_rootless(cause, this);
    }
  }
  f2__ptypehash__remove(cause, node_label_hash, node_label);
  return boolean__true;
}

f2ptr f2__graph__remove_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__graph__remove_node(cause, this, node_label));
}
def_pcfunk2(graph__remove_node, this, node_label, return f2__graph__remove_node(this_cause, this, node_label));


f2ptr raw__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label) {
  f2ptr left_node  = raw__graph__add_node(cause, this, left_node_label);
  f2ptr right_node = raw__graph__add_node(cause, this, right_node_label);
  {
    f2ptr edge_type_label_hash = f2__graph__edge_type_label_hash(cause, this);
    f2ptr edge_type            = f2__ptypehash__lookup(cause, edge_type_label_hash, edge_label);
    if (edge_type == nil) {
      edge_type = f2__graph_edge_type__new(cause, edge_label);
      f2__ptypehash__add(cause, edge_type_label_hash, edge_label, edge_type);
    }
    {
      f2ptr left_node_hash  = f2__graph_edge_type__left_node_hash( cause, edge_type);
      f2ptr right_node_hash = f2__graph_edge_type__right_node_hash(cause, edge_type);
      f2__ptypehash__add(cause, left_node_hash,  left_node_label,  left_node);
      f2__ptypehash__add(cause, right_node_hash, right_node_label, right_node);
    }
  }
  f2ptr edge = f2__graph_edge__new(cause, edge_label, left_node, right_node);
  {
    f2ptr edges_right_node_hash_edge_hash = f2__graph_node__edges_right_node_hash_edge_hash(cause, left_node);
    f2ptr edges_left_node_hash_edge_hash  = f2__graph_node__edges_left_node_hash_edge_hash( cause, right_node);
    f2ptr edges_right_node_hash           = f2__ptypehash__lookup(cause, edges_right_node_hash_edge_hash, edge_label);
    f2ptr edges_left_node_hash            = f2__ptypehash__lookup(cause, edges_left_node_hash_edge_hash,  edge_label);
    if (edges_right_node_hash == nil) {
      edges_right_node_hash = f2__ptypehash__new(cause);
      f2__ptypehash__add(cause, edges_right_node_hash_edge_hash, edge_label, edges_right_node_hash);
    }
    if (edges_left_node_hash == nil) {
      edges_left_node_hash = f2__ptypehash__new(cause);
      f2__ptypehash__add(cause, edges_left_node_hash_edge_hash, edge_label, edges_left_node_hash);
    }
    f2__ptypehash__add(cause, edges_right_node_hash, right_node_label, f2cons__new(cause, edge, f2__ptypehash__lookup(cause, edges_right_node_hash, right_node_label)));
    f2__ptypehash__add(cause, edges_left_node_hash,  left_node_label,  f2cons__new(cause, edge, f2__ptypehash__lookup(cause, edges_left_node_hash,  left_node_label)));
  }
  return edge;
}

f2ptr f2__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__add_edge(cause, this, edge_label, left_node_label, right_node_label);
}
def_pcfunk4(graph__add_edge, this, edge_label, left_node_label, right_node_label, return f2__graph__add_edge(this_cause, this, edge_label, left_node_label, right_node_label));

boolean_t raw__graph__contains_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  f2ptr node = raw__graph__lookup_node(cause, this, node_label);
  return (node != nil);
}

f2ptr f2__graph__contains_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__graph__contains_node(cause, this, node_label));
}
def_pcfunk2(graph__contains_node, this, node_label, return f2__graph__contains_node(this_cause, this, node_label));

f2ptr raw__graph__contains_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label) {
  f2ptr left_node = raw__graph__lookup_node(cause, this, left_node_label);
  if (! left_node) {
    return nil;
  }
  f2ptr edges_right_node_hash_edge_hash = f2__graph_node__edges_right_node_hash_edge_hash(cause, left_node);
  f2ptr edges_right_node_hash           = f2__ptypehash__lookup(cause, edges_right_node_hash_edge_hash, edge_label);
  if (! edges_right_node_hash) {
    return nil;
  }
  f2ptr edges = f2__ptypehash__lookup(cause, edges_right_node_hash, right_node_label);
  if (! edges) {
    return nil;
  }
  return f2integer__new(cause, raw__simple_length(cause, edges));
}

f2ptr f2__graph__contains_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__contains_edge(cause, this, edge_label, left_node_label, right_node_label);
}
def_pcfunk4(graph__contains_edge, this, edge_label, left_node_label, right_node_label, return f2__graph__contains_edge(this_cause, this, edge_label, left_node_label, right_node_label));

f2ptr raw__graph__lookup_edge_type(f2ptr cause, f2ptr this, f2ptr edge_label) {
  f2ptr edge_type_label_hash = f2__graph__edge_type_label_hash(cause, this);
  return f2__ptypehash__lookup(cause, edge_type_label_hash, edge_label);
}

f2ptr f2__graph__lookup_edge_type(f2ptr cause, f2ptr this, f2ptr edge_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__lookup_edge_type(cause, this, edge_label);
}
def_pcfunk2(graph__lookup_edge_type, this, edge_label, return f2__graph__lookup_edge_type(this_cause, this, edge_label));

boolean_t raw__graph__contains_edge_type(f2ptr cause, f2ptr this, f2ptr edge_label) {
  f2ptr edge_type = raw__graph__lookup_edge_type(cause, this, edge_label);
  return (edge_type != nil);
}

f2ptr f2__graph__contains_edge_type(f2ptr cause, f2ptr this, f2ptr edge_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__graph__contains_edge_type(cause, this, edge_label));
}
def_pcfunk2(graph__contains_edge_type, this, edge_label, return f2__graph__contains_edge_type(this_cause, this, edge_label));

boolean_t raw__graph__remove_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label) {
  f2ptr edge_type_label_hash = f2__graph__edge_type_label_hash(cause, this);
  f2ptr edge_type            = f2__ptypehash__lookup(cause, edge_type_label_hash, edge_label);
  if (! edge_type) {
    return boolean__false;
  }
  {
    f2ptr left_node = raw__graph__lookup_node(cause, this, left_node_label);
    if (! left_node) {
      return boolean__false;
    }
    f2ptr edges_right_node_hash_edge_hash = f2__graph_node__edges_right_node_hash_edge_hash(cause, left_node);
    f2ptr edges_right_node_hash           = f2__ptypehash__lookup(cause, edges_right_node_hash_edge_hash, edge_label);
    if (! edges_right_node_hash) {
      return boolean__false;
    }
    f2ptr edges = f2__ptypehash__lookup(cause, edges_right_node_hash, right_node_label);
    if (! edges) {
      return boolean__false;
    }
    edges = f2__cons__cdr(cause, edges);
    if (edges) {
      f2__ptypehash__add(cause, edges_right_node_hash, right_node_label, edges);
    } else {
      f2__ptypehash__remove(cause, edges_right_node_hash, right_node_label);
      f2ptr key_count    = f2__ptypehash__key_count(cause, edges_right_node_hash);
      u64   key_count__i = f2integer__i(key_count, cause);
      if (key_count__i == 0) {
	f2__ptypehash__remove(cause, edges_right_node_hash_edge_hash, edge_label);
	// remove left_node from edge_type because no more right_nodes are connected to the left_node
	f2ptr left_node_hash = f2__graph_edge_type__left_node_hash(cause, edge_type);
	f2__ptypehash__remove(cause, left_node_hash, left_node_label);
      }
    }
  }
  {
    f2ptr right_node = raw__graph__lookup_node(cause, this, right_node_label);
    if (! right_node) {
      // we should never get here.
      return boolean__false;
    }
    f2ptr edges_left_node_hash_edge_hash = f2__graph_node__edges_left_node_hash_edge_hash(cause, right_node);
    f2ptr edges_left_node_hash           = f2__ptypehash__lookup(cause, edges_left_node_hash_edge_hash, edge_label);
    if (! edges_left_node_hash) {
      // we should never get here.
      return boolean__false;
    }
    f2ptr edges = f2__ptypehash__lookup(cause, edges_left_node_hash, left_node_label);
    if (! edges) {
      // we should never get here.
      return boolean__false;
    }
    edges = f2__cons__cdr(cause, edges);
    if (edges) {
      f2__ptypehash__add(cause, edges_left_node_hash, left_node_label, edges);
    } else {
      f2__ptypehash__remove(cause, edges_left_node_hash, left_node_label);
      f2ptr key_count    = f2__ptypehash__key_count(cause, edges_left_node_hash);
      u64   key_count__i = f2integer__i(key_count, cause);
      if (key_count__i == 0) {
	f2__ptypehash__remove(cause, edges_left_node_hash_edge_hash, edge_label);
	// remove right_node from edge_type because no more left_nodes are connected to the right_node
	f2ptr right_node_hash = f2__graph_edge_type__right_node_hash(cause, edge_type);
	f2__ptypehash__remove(cause, right_node_hash, right_node_label);
	f2ptr right_node_hash__key_count    = f2__ptypehash__key_count(cause, right_node_hash);
	u64   right_node_hash__key_count__i = f2integer__i(right_node_hash__key_count, cause);
	if (right_node_hash__key_count__i == 0) {
	  f2__ptypehash__remove(cause, edge_type_label_hash, edge_label);
	}
      }
    }
  }
  return boolean__true;
}

f2ptr f2__graph__remove_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__graph__remove_edge(cause, this, edge_label, left_node_label, right_node_label));
}
def_pcfunk4(graph__remove_edge, this, edge_label, left_node_label, right_node_label, return f2__graph__remove_edge(this_cause, this, edge_label, left_node_label, right_node_label));

f2ptr raw__graph__replace_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label, f2ptr new_edge_label) {
  boolean_t removed_edge = raw__graph__remove_edge(cause, this, edge_label, left_node_label, right_node_label);
  if (! removed_edge) {
    return nil;
  }
  return raw__graph__add_edge(cause, this, new_edge_label, left_node_label, right_node_label);
}

f2ptr f2__graph__replace_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label, f2ptr new_edge_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__replace_edge(cause, this, edge_label, left_node_label, right_node_label, new_edge_label);
}
def_pcfunk5(graph__replace_edge, this, edge_label, left_node_label, right_node_label, new_edge_label, return f2__graph__replace_edge(this_cause, this, edge_label, left_node_label, right_node_label, new_edge_label));

boolean_t raw__graph__replace_edge_type(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr new_edge_label) {
  f2ptr edge_type = raw__graph__lookup_edge_type(cause, this, edge_label);
  if (! edge_type) {
    return boolean__false;
  }
  f2ptr edges_to_replace = nil;
  graph_edge_type__edge__iteration(cause, edge_type, edge, edges_to_replace = f2cons__new(cause, edge, edges_to_replace));
  {
    f2ptr iter = edges_to_replace;
    while (iter) {
      f2ptr edge = f2__cons__car(cause, iter);
      f2ptr edge__label             = f2__graph_edge__label(cause, edge);
      f2ptr edge__left_node         = f2__graph_edge__left_node(cause, edge);
      f2ptr edge__left_node__label  = f2__graph_node__label(cause, edge__left_node);
      f2ptr edge__right_node        = f2__graph_edge__right_node(cause, edge);
      f2ptr edge__right_node__label = f2__graph_node__label(cause, edge__right_node);
      raw__graph__replace_edge(cause, this, edge__label, edge__left_node__label, edge__right_node__label, new_edge_label);
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return boolean__true;
}

f2ptr f2__graph__replace_edge_type(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr new_edge_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__graph__replace_edge_type(cause, this, edge_label, new_edge_label));
}
def_pcfunk3(graph__replace_edge_type, this, edge_label, new_edge_label, return f2__graph__replace_edge_type(this_cause, this, edge_label, new_edge_label));

f2ptr f2__graph__nodes(f2ptr cause, f2ptr this) {
  f2ptr nodes = nil;
  graph__node__iteration(cause, this, node, nodes = f2cons__new(cause, node, nodes));
  return nodes;
}
def_pcfunk1(graph__nodes, this, return f2__graph__nodes(this_cause, this));

f2ptr f2__graph__edges(f2ptr cause, f2ptr this) {
  f2ptr edges = nil;
  graph__edge__iteration(cause, this, node, edges = f2cons__new(cause, node, edges));
  return edges;
}
def_pcfunk1(graph__edges, this, return f2__graph__edges(this_cause, this));

// graph-equals

boolean_t raw__graph__equals(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__node_label_hash               = f2__graph__node_label_hash(cause, this);
  f2ptr this__node_label_hash__key_count    = f2__ptypehash__key_count(cause, this__node_label_hash);
  u64   this__node_label_hash__key_count__i = f2integer__i(this__node_label_hash__key_count, cause);
  f2ptr that__node_label_hash               = f2__graph__node_label_hash(cause, that);
  f2ptr that__node_label_hash__key_count    = f2__ptypehash__key_count(cause, that__node_label_hash);
  u64   that__node_label_hash__key_count__i = f2integer__i(that__node_label_hash__key_count, cause);
  if (this__node_label_hash__key_count__i != that__node_label_hash__key_count__i) {
    return boolean__false;
  }
  graph__node__iteration(cause, this, node,
			 f2ptr node__label = f2__graph_node__label(cause, node);
			 if (! raw__graph__contains_node(cause, that, node__label)) {
			   return boolean__false;
			 }
			 );
  graph__edge__iteration(cause, this, edge,
			 f2ptr edge__label       = f2__graph_edge__label(     cause, edge);
			 f2ptr left_node         = f2__graph_edge__left_node( cause, edge);
			 f2ptr left_node__label  = f2__graph_node__label(     cause, left_node);
			 f2ptr right_node        = f2__graph_edge__right_node(cause, edge);
			 f2ptr right_node__label = f2__graph_node__label(     cause, right_node);
			 if (! raw__graph__contains_edge(cause, that, edge__label, left_node__label, right_node__label)) {
			     return boolean__false;
			 }
			 );
  return boolean__true;
}

f2ptr f2__graph__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__graph__equals(cause, this, that));
}
def_pcfunk2(graph__equals, this, that, return f2__graph__equals(this_cause, this, that));

// graph-equals_hash_value

f2ptr raw__graph__equals_hash_value(f2ptr cause, f2ptr this) {
  u64 hash_value__i = 1;
  {
    f2ptr node_label_hash               = f2__graph__node_label_hash(cause, this);
    f2ptr node_label_hash__key_count    = f2__ptypehash__key_count(cause, node_label_hash);
    u64   node_label_hash__key_count__i = f2integer__i(node_label_hash__key_count, cause);
    hash_value__i *= (node_label_hash__key_count__i + 1);
    graph__node__iteration(cause, this, node,
			   f2ptr node__label = f2__graph_node__label(cause, node);
			   {
			     f2ptr eq_hash_value = f2__object__eq_hash_value(cause, node__label);
			     if (raw__integer__is_type(cause, eq_hash_value)) {
			       u64 eq_hash_value__i = f2integer__i(eq_hash_value, cause);
			       hash_value__i *= (eq_hash_value__i + 1);
			     }
			   }
			   );
    graph__edge__iteration(cause, this, edge,
			   f2ptr edge__label       = f2__graph_edge__label(     cause, edge);
			   f2ptr left_node         = f2__graph_edge__left_node( cause, edge);
			   f2ptr left_node__label  = f2__graph_node__label(     cause, left_node);
			   f2ptr right_node        = f2__graph_edge__right_node(cause, edge);
			   f2ptr right_node__label = f2__graph_node__label(     cause, right_node);
			   {
			     f2ptr eq_hash_value = f2__object__eq_hash_value(cause, edge__label);
			     if (raw__integer__is_type(cause, eq_hash_value)) {
			       u64 eq_hash_value__i = f2integer__i(eq_hash_value, cause);
			       hash_value__i *= (eq_hash_value__i + 1);
			     }
			   }
			   {
			     f2ptr eq_hash_value = f2__object__eq_hash_value(cause, left_node__label);
			     if (raw__integer__is_type(cause, eq_hash_value)) {
			       u64 eq_hash_value__i = f2integer__i(eq_hash_value, cause);
			       hash_value__i *= (eq_hash_value__i + 1);
			     }
			   }
			   {
			     f2ptr eq_hash_value = f2__object__eq_hash_value(cause, right_node__label);
			     if (raw__integer__is_type(cause, eq_hash_value)) {
			       u64 eq_hash_value__i = f2integer__i(eq_hash_value, cause);
			       hash_value__i *= (eq_hash_value__i + 1);
			     }
			   }
			   );
  }
  return f2integer__new(cause, hash_value__i);
}

f2ptr f2__graph__equals_hash_value(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__equals_hash_value(cause, this);
}
def_pcfunk1(graph__equals_hash_value, this, return f2__graph__equals_hash_value(this_cause, this));

boolean_t raw__graph__replace_node(f2ptr cause, f2ptr this, f2ptr old_node_label, f2ptr new_node_label) {
  f2ptr old_node                                  = raw__graph__lookup_node(cause, this, old_node_label);
  if (! old_node) {
    return boolean__false;
  }
  f2ptr old_left_edges                            = nil;
  f2ptr old_right_edges                           = nil;
  f2ptr old_node__edges_left_node_hash_edge_hash  = f2__graph_node__edges_left_node_hash_edge_hash( cause, old_node);
  f2ptr old_node__edges_right_node_hash_edge_hash = f2__graph_node__edges_right_node_hash_edge_hash(cause, old_node);
  ptypehash__value__iteration(cause, old_node__edges_left_node_hash_edge_hash, old_node__edges_left_node_hash,
			      ptypehash__value__iteration(cause, old_node__edges_left_node_hash, old_node__edges,
							  f2ptr iter = old_node__edges;
							  while (iter) {
							    f2ptr edge = f2__cons__car(cause, iter);
							    old_left_edges = f2cons__new(cause, edge, old_left_edges);
							    iter = f2__cons__cdr(cause, iter);
							  }
							  );
			      );
  ptypehash__value__iteration(cause, old_node__edges_right_node_hash_edge_hash, old_node__edges_right_node_hash,
			      ptypehash__value__iteration(cause, old_node__edges_right_node_hash, old_node__edges,
							  f2ptr iter = old_node__edges;
							  while (iter) {
							    f2ptr edge = f2__cons__car(cause, iter);
							    old_right_edges = f2cons__new(cause, edge, old_right_edges);
							    iter = f2__cons__cdr(cause, iter);
							  }
							  );
			      );
  {
    f2ptr root_node = f2__graph__root_node(cause, this);
    if (root_node) {
      f2ptr root_node__label = f2__graph_node__label(cause, root_node);
      if (raw__eq(cause, root_node__label, old_node_label)) {
	f2__graph__make_rooted(cause, this, new_node_label);
      }
    }
  }
  raw__graph__remove_node(cause, this, old_node_label);
  {
    f2ptr iter = old_left_edges;
    while (iter) {
      f2ptr left_edge = f2__cons__car(cause, iter);
      {
	f2ptr edge__label      = f2__graph_edge__label(    cause, left_edge);
	f2ptr left_node        = f2__graph_edge__left_node(cause, left_edge);
	f2ptr left_node__label = f2__graph_node__label(    cause, left_node);
	raw__graph__add_edge(cause, this, edge__label, left_node__label, new_node_label);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  {
    f2ptr iter = old_right_edges;
    while (iter) {
      f2ptr right_edge = f2__cons__car(cause, iter);
      {
	f2ptr edge__label       = f2__graph_edge__label(     cause, right_edge);
	f2ptr right_node        = f2__graph_edge__right_node(cause, right_edge);
	f2ptr right_node__label = f2__graph_node__label(     cause, right_node);
	raw__graph__add_edge(cause, this, edge__label, new_node_label, right_node__label);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return boolean__true;
}

f2ptr f2__graph__replace_node(f2ptr cause, f2ptr this, f2ptr old_node_label, f2ptr new_node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__graph__replace_node(cause, this, old_node_label, new_node_label));
}
def_pcfunk3(graph__replace_node, this, old_node, new_node, return f2__graph__replace_node(this_cause, this, old_node, new_node));


boolean_t raw__graph__is_rooted(f2ptr cause, f2ptr this) {
  return (f2__graph__root_node(cause, this) != nil);
}

// rooted graph

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

void raw__graph__make_rooted(f2ptr cause, f2ptr this, f2ptr root_node_label) {
  f2ptr root_node = f2__graph__add_node(cause, this, root_node_label);
  f2__graph__root_node__set(cause, this, root_node);
}

f2ptr f2__graph__make_rooted(f2ptr cause, f2ptr this, f2ptr root_node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  raw__graph__make_rooted(cause, this, root_node_label);
  return nil;
}
def_pcfunk2(graph__make_rooted, this, root_node, return f2__graph__make_rooted(this_cause, this, root_node));

void raw__graph__make_rootless(f2ptr cause, f2ptr this) {
  f2__graph__root_node__set(cause, this, nil);
}

f2ptr f2__graph__make_rootless(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  raw__graph__make_rootless(cause, this);
  return nil;
}
def_pcfunk1(graph__make_rootless, this, return f2__graph__make_rootless(this_cause, this));

f2ptr raw__rooted_graph__as__frame(f2ptr cause, f2ptr this) {
  f2ptr root_node        = f2__graph__root_node(cause, this);
  f2ptr root_node__label = f2__graph_node__label(cause, root_node);
  f2ptr root_frame       = f2__frame__new(cause);
  f2ptr frame_node_hash  = f2__ptypehash__new(cause);
  f2__ptypehash__add(cause, frame_node_hash, root_node__label, root_frame);
  graph__edge__iteration(cause, this, edge,
			 f2ptr left_node        = f2__graph_edge__left_node(cause, edge);
			 f2ptr left_node__label = f2__graph_node__label(    cause, left_node);
			 f2ptr frame            = f2__ptypehash__lookup(    cause, frame_node_hash, left_node__label);
			 if (! frame) {
			   frame = f2__frame__new(cause);
			   f2__ptypehash__add(cause, frame_node_hash, left_node__label, frame);
			 }
			 );
  graph__edge__iteration(cause, this, edge,
			 f2ptr edge__label       = f2__graph_edge__label(     cause, edge);
			 f2ptr left_node         = f2__graph_edge__left_node( cause, edge);
			 f2ptr left_node__label  = f2__graph_node__label(     cause, left_node);
			 f2ptr right_node        = f2__graph_edge__right_node(cause, edge);
			 f2ptr right_node__label = f2__graph_node__label(     cause, right_node);
			 f2ptr frame             = f2__ptypehash__lookup(cause, frame_node_hash, left_node__label);
			 f2ptr right_node_value  = f2__ptypehash__lookup(cause, frame_node_hash, right_node__label);
			 if (! right_node_value) {
			   right_node_value = right_node__label;
			 }
			 f2__frame__add_var_value(cause, frame, edge__label, right_node__label);
			 );
  return root_frame;
}

f2ptr f2__rooted_graph__as__frame(f2ptr cause, f2ptr this) {
  if (! raw__rooted_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
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
  {
    graph__node__iteration(cause, this, node,
			   f2ptr node__label = f2__graph_node__label(cause, node);
			   if (raw__graph__contains_node(cause, that, node__label)) {
			     raw__graph__add_node(cause, graph, node__label);
			   }
			   );
    graph__edge__iteration(cause, this, edge,
			   f2ptr edge__label       = f2__graph_edge__label(     cause, edge);
			   f2ptr left_node         = f2__graph_edge__left_node( cause, edge);
			   f2ptr left_node__label  = f2__graph_node__label(     cause, left_node);
			   f2ptr right_node        = f2__graph_edge__right_node(cause, edge);
			   f2ptr right_node__label = f2__graph_node__label(     cause, right_node);
			   if (raw__graph__contains_edge(cause, that, edge__label, left_node__label, right_node__label)) {
			     raw__graph__add_edge(cause, graph, edge__label, left_node__label, right_node__label);
			   }
			   );
  }
  return graph;
}

f2ptr f2__graph__intersect(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__intersect(cause, this, that);
}
def_pcfunk2(graph__intersect, this, that, return f2__graph__intersect(this_cause, this, that));

f2ptr raw__graph__union(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr graph = f2__graph__new(cause);
  {
    graph__node__iteration(cause, this, node,
			   f2ptr node__label = f2__graph_node__label(cause, node);
			   raw__graph__add_node(cause, graph, node__label);
			   );
    graph__node__iteration(cause, that, node,
			   f2ptr node__label = f2__graph_node__label(cause, node);
			   raw__graph__add_node(cause, graph, node__label);
			   );
    graph__edge__iteration(cause, this, edge,
			   f2ptr edge__label       = f2__graph_edge__label(     cause, edge);
			   f2ptr left_node         = f2__graph_edge__left_node( cause, edge);
			   f2ptr left_node__label  = f2__graph_node__label(     cause, left_node);
			   f2ptr right_node        = f2__graph_edge__right_node(cause, edge);
			   f2ptr right_node__label = f2__graph_node__label(     cause, right_node);
			   if (! raw__graph__contains_edge(cause, graph, edge__label, left_node__label, right_node__label)) {
			     raw__graph__add_edge(cause, graph, edge__label, left_node__label, right_node__label);
			   }
			   );
    graph__edge__iteration(cause, that, edge,
			   f2ptr edge__label       = f2__graph_edge__label(     cause, edge);
			   f2ptr left_node         = f2__graph_edge__left_node( cause, edge);
			   f2ptr left_node__label  = f2__graph_node__label(     cause, left_node);
			   f2ptr right_node        = f2__graph_edge__right_node(cause, edge);
			   f2ptr right_node__label = f2__graph_node__label(     cause, right_node);
			   if (! raw__graph__contains_edge(cause, graph, edge__label, left_node__label, right_node__label)) {
			     raw__graph__add_edge(cause, graph, edge__label, left_node__label, right_node__label);
			   }
			   );
  }
  return graph;
}

f2ptr f2__graph__union(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__union(cause, this, that);
}
def_pcfunk2(graph__union, this, that, return f2__graph__union(this_cause, this, that));

f2ptr raw__graph__copy(f2ptr cause, f2ptr this) {
  f2ptr graph = f2__graph__new(cause);
  {
    graph__node__iteration(cause, this, node,
			   f2ptr node__label = f2__graph_node__label(cause, node);
			   raw__graph__add_node(cause, graph, node__label);
			   );
    graph__edge__iteration(cause, this, edge,
			   f2ptr edge__label       = f2__graph_edge__label(     cause, edge);
			   f2ptr left_node         = f2__graph_edge__left_node( cause, edge);
			   f2ptr left_node__label  = f2__graph_node__label(     cause, left_node);
			   f2ptr right_node        = f2__graph_edge__right_node(cause, edge);
			   f2ptr right_node__label = f2__graph_node__label(     cause, right_node);
			   raw__graph__add_edge(cause, graph, edge__label, left_node__label, right_node__label);
			   );
    if (raw__graph__is_rooted(cause, this)) {
      f2ptr root_node        = f2__graph__root_node(cause, this);
      f2ptr root_node__label = f2__graph_node__label(cause, root_node);
      raw__graph__make_rooted(cause, graph, root_node__label);
    }
    f2ptr this__variable_name_hash = f2__graph__variable_name_hash(cause, this);
    if (this__variable_name_hash) {
      f2ptr graph__variable_name_hash = f2__ptypehash__new(cause);
      f2__graph__variable_name_hash__set(cause, graph, graph__variable_name_hash);
      ptypehash__iteration(cause, this__variable_name_hash, variable_name, variable, f2__ptypehash__add(cause, graph__variable_name_hash, variable_name, variable));
    }
  }
  return graph;
}

f2ptr f2__graph__copy(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__copy(cause, this);
}
def_pcfunk1(graph__copy, this, return f2__graph__copy(this_cause, this));


f2ptr raw__graph__part_not_contained_by(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr graph = f2__graph__new(cause);
  {
    graph__node__iteration(cause, this, node,
			   f2ptr node__label = f2__graph_node__label(cause, node);
			   if (! raw__graph__contains_node(cause, that, node__label)) {
			     raw__graph__add_node(cause, graph, node__label);
			   }
			   );
    graph__edge__iteration(cause, this, edge,
			   f2ptr edge__label       = f2__graph_edge__label(     cause, edge);
			   f2ptr left_node         = f2__graph_edge__left_node( cause, edge);
			   f2ptr left_node__label  = f2__graph_node__label(     cause, left_node);
			   f2ptr right_node        = f2__graph_edge__right_node(cause, edge);
			   f2ptr right_node__label = f2__graph_node__label(     cause, right_node);
			   if (! raw__graph__contains_edge(cause, that, edge__label, left_node__label, right_node__label)) {
			     raw__graph__add_edge(cause, graph, edge__label, left_node__label, right_node__label);
			   }
			   );
  }
  return graph;
}

f2ptr f2__graph__part_not_contained_by(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, this))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__part_not_contained_by(cause, this, that);
}
def_pcfunk2(graph__part_not_contained_by, this, that, return f2__graph__part_not_contained_by(this_cause, this, that));

f2ptr raw__graph__variables(f2ptr cause, f2ptr this) {
  f2ptr variables          = nil;
  f2ptr variable_name_hash = f2__graph__variable_name_hash(cause, this);
  if (variable_name_hash) {
    ptypehash__value__iteration(cause, variable_name_hash, variable, variables = f2cons__new(cause, variable, variables));
  }
  return variables;
}

f2ptr f2__graph__variables(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__variables(cause, this);
}
def_pcfunk1(graph__variables, this, return f2__graph__variables(this_cause, this));


f2ptr raw__graph__lookup_variable(f2ptr cause, f2ptr this, f2ptr variable_name) {
  f2ptr variable_name_hash = f2__graph__variable_name_hash(cause, this);
  if (! variable_name_hash) {
    return nil;
  }
  return f2__ptypehash__lookup(cause, variable_name_hash, variable_name);
}

f2ptr raw__graph__add_variable(f2ptr cause, f2ptr this, f2ptr variable_name) {
  f2ptr variable_name_hash = f2__graph__variable_name_hash(cause, this);
  if (! variable_name_hash) {
    variable_name_hash = f2__ptypehash__new(cause);
    f2__graph__variable_name_hash__set(cause, this, variable_name_hash);
  }
  f2ptr variable = f2__ptypehash__lookup(cause, variable_name_hash, variable_name);
  if (! variable) {
    variable = f2__graph_variable__new(cause, variable_name);
    raw__ptypehash__add(cause, variable_name_hash, variable_name, variable);
  }
  return variable;
}

f2ptr raw__graph__make_node_variable(f2ptr cause, f2ptr this, f2ptr node_label, f2ptr variable_name) {
  f2ptr variable = raw__graph__lookup_variable(cause, this, variable_name);
  if (! variable) {
    variable = raw__graph__add_variable(cause, this, variable_name);
  }
  raw__graph__replace_node(cause, this, node_label, variable);
  return variable;
}

f2ptr f2__graph__make_node_variable(f2ptr cause, f2ptr this, f2ptr node_label, f2ptr variable_name) {
  if (! raw__graph__contains_node(cause, this, node_label)) {
    return nil;
  }
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__make_node_variable(cause, this, node_label, variable_name);
}
def_pcfunk3(graph__make_node_variable, this, node_label, variable_name, return f2__graph__make_node_variable(this_cause, this, node_label, variable_name));

f2ptr raw__graph__make_node_wildcard(f2ptr cause, f2ptr this, f2ptr node_label) {
  return raw__graph__make_node_variable(cause, this, node_label, __funk2.globalenv.astrisk__symbol);
}

f2ptr f2__graph__make_node_wildcard(f2ptr cause, f2ptr this, f2ptr node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__make_node_wildcard(cause, this, node_label);
}
def_pcfunk2(graph__make_node_wildcard, this, node_label, return f2__graph__make_node_wildcard(this_cause, this, node_label));

f2ptr raw__graph__make_edge_variable(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label, f2ptr variable_name) {
  if (! raw__graph__contains_edge(cause, this, edge_label, left_node_label, right_node_label)) {
    return nil;
  }
  f2ptr variable = raw__graph__lookup_variable(cause, this, variable_name);
  if (! variable) {
    variable = raw__graph__add_variable(cause, this, variable_name);
  }
  raw__graph__replace_edge(cause, this, edge_label, left_node_label, right_node_label, variable);
  return variable;
}

f2ptr f2__graph__make_edge_variable(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label, f2ptr variable_name) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__make_edge_variable(cause, this, edge_label, left_node_label, right_node_label, variable_name);
}
def_pcfunk5(graph__make_edge_variable, this, edge_label, left_node_label, right_node_label, variable_name, return f2__graph__make_edge_variable(this_cause, this, edge_label, left_node_label, right_node_label, variable_name));

f2ptr raw__graph__make_edge_wildcard(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label) {
  return raw__graph__make_edge_variable(cause, this, edge_label, left_node_label, right_node_label, __funk2.globalenv.astrisk__symbol);
}

f2ptr f2__graph__make_edge_wildcard(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__make_edge_wildcard(cause, this, edge_label, left_node_label, right_node_label);
}
def_pcfunk4(graph__make_edge_wildcard, this, edge_label, left_node_label, right_node_label, return f2__graph__make_edge_wildcard(this_cause, this, edge_label, left_node_label, right_node_label));

boolean_t raw__graph__bind_variable(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value) {
  f2ptr variable_name_hash = f2__graph__variable_name_hash(cause, this);
  f2ptr variable           = f2__ptypehash__lookup(cause, variable_name_hash, variable_name);
  if (! variable) {
    return boolean__false;
  }
  f2ptr variable_node      = raw__graph__lookup_node(cause, this, variable);
  f2ptr variable_edge_type = raw__graph__lookup_edge_type(cause, this, variable);
  if (variable_node) {
    raw__graph__replace_node(cause, this, variable, value);
  }
  if (variable_edge_type) {
    raw__graph__replace_edge_type(cause, this, variable, value);
  }
  f2__ptypehash__remove(cause, variable_name_hash, variable_name);
  return boolean__true;
}

f2ptr f2__graph__bind_variable(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__graph__bind_variable(cause, this, variable_name, value));
}
def_pcfunk3(graph__bind_variable, this, variable_name, value, return f2__graph__bind_variable(this_cause, this, variable_name, value));

f2ptr raw__graph__an_arbitrary_node(f2ptr cause, f2ptr this) {
  f2ptr node_label_hash = f2__graph__node_label_hash(cause, this);
  return f2__ptypehash__an_arbitrary_value(cause, node_label_hash);
}

f2ptr raw__graph__an_arbitrary_edge(f2ptr cause, f2ptr this) {
  f2ptr edge_type_label_hash               = f2__graph__edge_type_label_hash(cause, this);
  f2ptr an_arbitrary_edge_type             = f2__ptypehash__an_arbitrary_value(cause, edge_type_label_hash);
  f2ptr left_node_hash                     = f2__graph_edge_type__left_node_hash(cause, an_arbitrary_edge_type);
  f2ptr an_arbitrary_left_node             = f2__ptypehash__an_arbitrary_value(cause, left_node_hash);
  f2ptr edges_right_node_hash_edge_hash    = f2__graph_node__edges_right_node_hash_edge_hash(cause, an_arbitrary_left_node);
  f2ptr an_arbitrary_edges_right_node_hash = f2__ptypehash__an_arbitrary_value(cause, edges_right_node_hash_edge_hash);
  f2ptr an_arbitrary_edges                 = f2__ptypehash__an_arbitrary_value(cause, an_arbitrary_edges_right_node_hash);
  release__assert(an_arbitrary_edges, cause, "raw__graph__an_arbitrary_edge error: found nil set of edges.");
  return f2__cons__car(cause, an_arbitrary_edges);
}


// this is a normal graph without variables.
// that is a pattern graph with variables at nodes and edges
f2ptr raw__graph__contains_match_with_bindings(f2ptr cause, f2ptr this, f2ptr that, f2ptr bindings) {
  u64 this__node_count = graph__node_count(cause, this);
  u64 that__node_count = graph__node_count(cause, that);
  if (this__node_count < that__node_count) {
    return nil;
  }
  // return no matches if nodes don't match.
  graph__node__iteration(cause, that, that_node,
			 f2ptr that_node__label = f2__graph_node__label(cause, that_node);
			 if (! raw__graph_variable__is_type(cause, that_node__label)) {
			   if (! raw__graph__contains_node(cause, this, that_node__label)) {
			     return nil;
			   }
			 }
			 );
  // return no matches if edges don't match.
  graph__edge__iteration(cause, that, that__edge,
			 f2ptr that__edge__label             = f2__graph_edge__label(     cause, that__edge);
			 f2ptr that__edge__left_node         = f2__graph_edge__left_node( cause, that__edge);
			 f2ptr that__edge__right_node        = f2__graph_edge__right_node(cause, that__edge);
			 f2ptr that__edge__left_node__label  = f2__graph_node__label(     cause, that__edge__left_node);
			 f2ptr that__edge__right_node__label = f2__graph_node__label(     cause, that__edge__right_node);
			 if ((! raw__graph_variable__is_type(cause, that__edge__label)) &&
			     (! raw__graph_variable__is_type(cause, that__edge__left_node__label)) &&
			     (! raw__graph_variable__is_type(cause, that__edge__right_node__label))) {
			   if (! raw__graph__contains_edge(cause, this, that__edge__label, that__edge__left_node__label, that__edge__right_node__label)) {
			     return nil;
			   }
			 }
			 );
  f2ptr this_unmatched_subgraph = f2__graph__copy(cause, this);
  f2ptr that_unmatched_subgraph = f2__graph__copy(cause, that);
  // remove edges that don't contain variables.
  graph__edge__iteration(cause, that, that__edge,
			 f2ptr that__edge__label             = f2__graph_edge__label(     cause, that__edge);
			 f2ptr that__edge__left_node         = f2__graph_edge__left_node( cause, that__edge);
			 f2ptr that__edge__right_node        = f2__graph_edge__right_node(cause, that__edge);
			 f2ptr that__edge__left_node__label  = f2__graph_node__label(     cause, that__edge__left_node);
			 f2ptr that__edge__right_node__label = f2__graph_node__label(     cause, that__edge__right_node);
			 if ((! raw__graph_variable__is_type(cause, that__edge__label)) &&
			     (! raw__graph_variable__is_type(cause, that__edge__left_node__label)) &&
			     (! raw__graph_variable__is_type(cause, that__edge__right_node__label))) {
			   if (raw__graph__contains_edge(cause, this, that__edge__label, that__edge__left_node__label, that__edge__right_node__label)) {
			     raw__graph__remove_edge(cause, this_unmatched_subgraph, that__edge__label, that__edge__left_node__label, that__edge__right_node__label);
			     raw__graph__remove_edge(cause, that_unmatched_subgraph, that__edge__label, that__edge__left_node__label, that__edge__right_node__label);
			   }
			 }
			 );
  { // remove edgeless nodes
    f2ptr matched_edgeless_node_labels = nil;
    graph__node__iteration(cause, that_unmatched_subgraph, that_unmatched_subgraph__node,
			   f2ptr that_unmatched_subgraph__node__label = f2__graph_node__label(cause, that_unmatched_subgraph__node);
			   if (! raw__graph_variable__is_type(cause, that_unmatched_subgraph__node__label)) {
			     int that_unmatched_subgraph__node__edge_count = 0;
			     graph_node__in_edge__iteration( cause, that_unmatched_subgraph__node, in_edge,  that_unmatched_subgraph__node__edge_count ++);
			     graph_node__out_edge__iteration(cause, that_unmatched_subgraph__node, out_edge, that_unmatched_subgraph__node__edge_count ++);
			     if (that_unmatched_subgraph__node__edge_count == 0) {
			       f2ptr that_unmatched_subgraph__node__label = f2__graph_node__label(cause, that_unmatched_subgraph__node);
			       matched_edgeless_node_labels = f2cons__new(cause, that_unmatched_subgraph__node__label, matched_edgeless_node_labels);
			     }
			   }
			   );
    {
      f2ptr iter = matched_edgeless_node_labels;
      while (iter) {
	f2ptr matched_edgeless_node_label = f2__cons__car(cause, iter);
	raw__graph__remove_node(cause, this_unmatched_subgraph, matched_edgeless_node_label);
	raw__graph__remove_node(cause, that_unmatched_subgraph, matched_edgeless_node_label);
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  {
    f2ptr variable_name_hash = f2__graph__variable_name_hash(cause, that);
    if (! variable_name_hash) {
      //printf("\nsuccessful bind.");
      return bindings;
    }
    f2ptr variable_name = f2__ptypehash__an_arbitrary_key(cause, variable_name_hash);
    if (! variable_name) {
      //printf("\nsuccessful bind.");
      return bindings;
    }
    //printf("\nattempting to bind variable: "); f2__print(cause, variable_name);
    f2ptr possible_labels = nil;
    graph__node__iteration(cause, this_unmatched_subgraph, this_unmatched_subgraph__node,
			   f2ptr this_unmatched_subgraph__node__label = f2__graph_node__label(cause, this_unmatched_subgraph__node);
			   possible_labels = f2cons__new(cause, this_unmatched_subgraph__node__label, possible_labels);
			   );
    graph__edge__iteration(cause, this_unmatched_subgraph, this_unmatched_subgraph__edge,
			   f2ptr this_unmatched_subgraph__edge__label = f2__graph_edge__label(cause, this_unmatched_subgraph__edge);
			   possible_labels = f2cons__new(cause, this_unmatched_subgraph__edge__label, possible_labels);
			   );
    {
      f2ptr iter = possible_labels;
      while (iter) {
	f2ptr possible_label = f2__cons__car(cause, iter);
	{
	  f2ptr new_bindings;
	  if (bindings) {
	    new_bindings = f2__ptypehash__copy(cause, bindings);
	  } else {
	    new_bindings = f2__ptypehash__new(cause);
	  }
	  f2__ptypehash__add(cause, new_bindings, variable_name, possible_label);
	  f2ptr that_unmatched_subgraph_bound = f2__graph__copy(cause, that_unmatched_subgraph);
	  //printf("\nattempting to bind variable "); f2__print(cause, variable_name);
	  //printf("  to "); f2__print(cause, possible_label);
	  if (! raw__graph__bind_variable(cause, that_unmatched_subgraph_bound, variable_name, possible_label)) {
	    return f2larva__new(cause, 134, nil);
	  }
	  //printf("  and searching for match within bindings: "); f2__print(cause, new_bindings);
	  f2ptr successful_bindings = raw__graph__contains_match_with_bindings(cause, this_unmatched_subgraph, that_unmatched_subgraph_bound, new_bindings);
	  if (successful_bindings) {
	    //printf("\nfound successful bindings.");
	    return successful_bindings;
	  }
	  //printf("\ndid not find successful bindings for "); f2__print(cause, variable_name);
	  //printf("    and "); f2__print(cause, possible_label);
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  return nil;
}

f2ptr f2__graph__contains_match_with_bindings(f2ptr cause, f2ptr this, f2ptr that, f2ptr bindings) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__contains_match_with_bindings(cause, this, that, bindings);
}
def_pcfunk3(graph__contains_match_with_bindings, this, that, bindings, return f2__graph__contains_match_with_bindings(this_cause, this, that, bindings));

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
      f2ptr edge_code               = f2__graphviz__labelled_edge(cause, edge__label, f2__graphviz__exp__as__name(cause, edge__left_node__label), f2__graphviz__exp__as__name(cause, edge__right_node__label));
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
    return f2larva__new(cause, 1, nil);
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


// pattern_graph

def_primobject_2_slot(pattern_graph, variable_label_hash, graph);

f2ptr f2__pattern_graph__new(f2ptr cause) {
  return f2pattern_graph__new(cause, f2__ptypehash__new(cause), f2__graph__new(cause));
}
def_pcfunk0(pattern_graph__new, return f2__pattern_graph__new(this_cause));





// graph_variable

def_primobject_1_slot(graph_variable, name);

f2ptr f2__graph_variable__new(f2ptr cause, f2ptr name) {
  return f2graph_variable__new(cause, name);
}
def_pcfunk1(graph_variable__new, name, return f2__graph_variable__new(this_cause, name));

f2ptr f2__graph_variable__new_wildcard(f2ptr cause) {
  return f2__graph_variable__new(cause, __funk2.globalenv.astrisk__symbol);
}

boolean_t raw__graph_variable__is_wildcard(f2ptr cause, f2ptr this) {
  f2ptr name = f2__graph_variable__name(cause, this);
  return raw__eq(cause, name, __funk2.globalenv.astrisk__symbol);
}

f2ptr f2__graph_variable__is_wildcard(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__graph_variable__is_wildcard(cause, this));
}
def_pcfunk1(graph_variable__is_wildcard, this, return f2__graph_variable__is_wildcard(this_cause, this));

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
  return raw__eq_hash_value(cause, raw__graph_variable__name(cause, this));
}

f2ptr f2__graph_variable__eq_hash_value(f2ptr cause, f2ptr this) {
  if (! raw__graph_variable__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph_variable__eq_hash_value(cause, this);
}
def_pcfunk1(graph_variable__eq_hash_value, this, return f2__graph_variable__eq_hash_value(this_cause, this));

f2ptr f2graph_variable__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph_variable__primobject_type__new(cause);
  {char* slot_name = "eq";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq_hash_value__funk);}
  return this;
}


f2ptr f2__common_variable_subgraph_possibility__new(f2ptr cause, f2ptr worth, f2ptr common_subgraph, f2ptr this_remaining_subgraph, f2ptr that_remaining_subgraph) {
  f2ptr this = raw__array__new(cause, 4);
  raw__array__elt__set(cause, this, 0, worth);
  raw__array__elt__set(cause, this, 1, common_subgraph);
  raw__array__elt__set(cause, this, 2, this_remaining_subgraph);
  raw__array__elt__set(cause, this, 3, that_remaining_subgraph);
  return this;
}

f2ptr raw__common_variable_subgraph_possibility__worth(                  f2ptr cause, f2ptr this) {return raw__array__elt(cause, this, 0);}
f2ptr raw__common_variable_subgraph_possibility__common_subgraph(        f2ptr cause, f2ptr this) {return raw__array__elt(cause, this, 1);}
f2ptr raw__common_variable_subgraph_possibility__this_remaining_subgraph(f2ptr cause, f2ptr this) {return raw__array__elt(cause, this, 2);}
f2ptr raw__common_variable_subgraph_possibility__that_remaining_subgraph(f2ptr cause, f2ptr this) {return raw__array__elt(cause, this, 3);}

f2ptr f2__common_variable_subgraph_possibility__new_with_compression(f2ptr cause, u64 worth, f2ptr common_subgraph, f2ptr this_remaining_subgraph, f2ptr that_remaining_subgraph) {
  {
    f2ptr common_edges = nil;
    graph__edge__iteration(cause, this_remaining_subgraph, this__edge,
			   f2ptr this__edge__label             = f2__graph_edge__label(     cause, this__edge);
			   f2ptr this__edge__left_node         = f2__graph_edge__left_node( cause, this__edge);
			   f2ptr this__edge__left_node__label  = f2__graph_node__label(     cause, this__edge__left_node);
			   f2ptr this__edge__right_node        = f2__graph_edge__right_node(cause, this__edge);
			   f2ptr this__edge__right_node__label = f2__graph_node__label(     cause, this__edge__right_node);
			   if (raw__graph__contains_edge(cause, that_remaining_subgraph, this__edge__label, this__edge__left_node__label, this__edge__right_node__label)) {
			     common_edges = f2cons__new(cause, this__edge, common_edges);
			   }
			   );
    {
      f2ptr iter = common_edges;
      while (iter) {
	f2ptr edge = f2__cons__car(cause, iter);
	{
	  f2ptr edge__label             = f2__graph_edge__label(     cause, edge);
	  f2ptr edge__left_node         = f2__graph_edge__left_node( cause, edge);
	  f2ptr edge__left_node__label  = f2__graph_node__label(     cause, edge__left_node);
	  f2ptr edge__right_node        = f2__graph_edge__right_node(cause, edge);
	  f2ptr edge__right_node__label = f2__graph_node__label(     cause, edge__right_node);
	  raw__graph__remove_edge(cause, this_remaining_subgraph, edge__label, edge__left_node__label, edge__right_node__label);
	  raw__graph__remove_edge(cause, that_remaining_subgraph, edge__label, edge__left_node__label, edge__right_node__label);
	  raw__graph__add_edge(   cause, common_subgraph,         edge__label, edge__left_node__label, edge__right_node__label);
	  worth ++;
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  {
    f2ptr edgeless_common_node_labels = nil;
    graph__node__iteration(cause, this_remaining_subgraph, this__node,
			   f2ptr this__node__label = f2__graph_node__label(cause, this__node);
			   f2ptr that__node        = raw__graph__lookup_node(cause, that_remaining_subgraph, this__node__label);
			   if (that__node) {
			     if ((! raw__graph_node__has_edges(cause, this__node)) &&
				 (! raw__graph_node__has_edges(cause, that__node))) {
			       edgeless_common_node_labels = f2cons__new(cause, this__node__label, edgeless_common_node_labels);
			     }
			   }
			   );
    {
      f2ptr iter = edgeless_common_node_labels;
      while (iter) {
	f2ptr node_label = f2__cons__car(cause, iter);
	raw__graph__remove_node(cause, this_remaining_subgraph, node_label);
	raw__graph__remove_node(cause, that_remaining_subgraph, node_label);
	raw__graph__add_node(   cause, common_subgraph,         node_label);
	worth ++;
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  return f2__common_variable_subgraph_possibility__new(cause, f2integer__new(cause, worth), common_subgraph, this_remaining_subgraph, that_remaining_subgraph);
}

f2ptr raw__common_variable_subgraph_possibility__compare(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__worth    = raw__common_variable_subgraph_possibility__worth(cause, this);
  f2ptr that__worth    = raw__common_variable_subgraph_possibility__worth(cause, that);
  s64   this__worth__i = f2integer__i(this__worth, cause);
  s64   that__worth__i = f2integer__i(that__worth, cause);
  return f2bool__new(this__worth__i < that__worth__i);
}
// no type checking, not meant to be user-accessible
def_pcfunk2(common_variable_subgraph_possibility__compare, this, that, return raw__common_variable_subgraph_possibility__compare(this_cause, this, that));

f2ptr f2__common_variable_subgraph_possibility_redblacktree__new(f2ptr cause) {
  f2ptr comparison_funk = __funk2.graph.common_variable_subgraph_possibility__compare__funk;
  return f2__redblacktree__new(cause, comparison_funk);
}

f2ptr raw__common_variable_subgraph_possibility_redblacktree__consider_inserting(f2ptr cause, f2ptr this, f2ptr possibility) {
  boolean_t okay_to_insert = boolean__false;
  u64       size           = raw__redblacktree__size(cause, this);
  if (size < 100) {
    okay_to_insert = boolean__true;
  } else {
    f2ptr worth            = raw__common_variable_subgraph_possibility__worth(cause, possibility);
    u64   worth__i         = f2integer__i(worth, cause);
    f2ptr minimum          = raw__redblacktree__minimum(cause, this);
    f2ptr minimum_worth    = raw__common_variable_subgraph_possibility__worth(cause, minimum);
    u64   minimum_worth__i = f2integer__i(minimum_worth, cause);
    if (minimum_worth__i < worth__i) {
      raw__redblacktree__remove(cause, this, minimum);
    }
    okay_to_insert = boolean__true;
  }
  return f2__redblacktree__insert(cause, this, possibility);
}

f2ptr raw__graph__find_common_variable_subgraph(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr best_possibility           = nil;
  u64   best_possibility__worth__i = 0;
  f2ptr subgraph_possibilities     = f2__common_variable_subgraph_possibility_redblacktree__new(cause);
  {
    f2ptr new_common_subgraph         = f2__graph__new(cause);
    f2ptr new_this_remaining_subgraph = f2__graph__copy(cause, this);
    f2ptr new_that_remaining_subgraph = f2__graph__copy(cause, that);
    f2ptr new_possibility             = f2__common_variable_subgraph_possibility__new_with_compression(cause, 0, new_common_subgraph, new_this_remaining_subgraph, new_that_remaining_subgraph);
    f2__redblacktree__insert(cause, subgraph_possibilities, new_possibility);
    best_possibility = new_possibility;
    f2ptr new_possibility__worth = raw__common_variable_subgraph_possibility__worth(cause, new_possibility);
    best_possibility__worth__i   = f2integer__i(new_possibility__worth, cause);
  }
  f2__print(cause, subgraph_possibilities);
  while (f2__redblacktree__head(cause, subgraph_possibilities) != nil) {
    f2ptr new_subgraph_possibilities = f2__common_variable_subgraph_possibility_redblacktree__new(cause);
    redblacktree__iteration(cause, subgraph_possibilities, possibility,
			    printf("\npossibility:"); f2__print(cause, possibility);
			    f2ptr worth                   = raw__common_variable_subgraph_possibility__worth(                  cause, possibility);
			    u64   worth__i                = f2integer__i(worth, cause);
			    f2ptr common_subgraph         = raw__common_variable_subgraph_possibility__common_subgraph(        cause, possibility);
			    f2ptr this_remaining_subgraph = raw__common_variable_subgraph_possibility__this_remaining_subgraph(cause, possibility);
			    f2ptr that_remaining_subgraph = raw__common_variable_subgraph_possibility__that_remaining_subgraph(cause, possibility);
			    { // make node in first graph a variable with a node in second graph.
			      f2ptr new_common_subgraph         = f2__graph__copy(cause, common_subgraph);
			      f2ptr new_this_remaining_subgraph = f2__graph__copy(cause, this_remaining_subgraph);
			      f2ptr new_that_remaining_subgraph = f2__graph__copy(cause, that_remaining_subgraph);
			      f2ptr this__arbitrary_node        = raw__graph__an_arbitrary_node(cause, new_this_remaining_subgraph);
			      f2ptr that__arbitrary_node        = raw__graph__an_arbitrary_node(cause, new_that_remaining_subgraph);
			      f2ptr this__arbitrary_node__label = f2__graph_node__label(cause, this__arbitrary_node);
			      f2ptr that__arbitrary_node__label = f2__graph_node__label(cause, that__arbitrary_node);
			      f2ptr gensym_variable_name        = f2__gensym(cause);
			      raw__graph__make_node_variable(cause, new_this_remaining_subgraph, this__arbitrary_node__label, gensym_variable_name);
			      raw__graph__make_node_variable(cause, new_that_remaining_subgraph, that__arbitrary_node__label, gensym_variable_name);
			      f2ptr new_possibility = f2__common_variable_subgraph_possibility__new_with_compression(cause, worth__i, new_common_subgraph, new_this_remaining_subgraph, new_that_remaining_subgraph);
			      {
				f2ptr new_worth    = raw__common_variable_subgraph_possibility__worth(cause, new_possibility);
				u64   new_worth__i = f2integer__i(new_worth, cause);
				if (new_worth__i > best_possibility__worth__i) {
				  best_possibility           = new_possibility;
				  best_possibility__worth__i = new_worth__i;
				}
			      }
			      raw__common_variable_subgraph_possibility_redblacktree__consider_inserting(cause, new_subgraph_possibilities, new_possibility);
			    }
			    { // skip node in this graph.
			      f2ptr new_common_subgraph         = f2__graph__copy(cause, common_subgraph);
			      f2ptr new_this_remaining_subgraph = f2__graph__copy(cause, this_remaining_subgraph);
			      f2ptr new_that_remaining_subgraph = f2__graph__copy(cause, that_remaining_subgraph);
			      f2ptr this__arbitrary_node        = raw__graph__an_arbitrary_node(cause, new_this_remaining_subgraph);
			      f2ptr this__arbitrary_node__label = f2__graph_node__label(cause, this__arbitrary_node);
			      raw__graph__remove_node(cause, new_this_remaining_subgraph, this__arbitrary_node__label);
			      f2ptr new_possibility = f2__common_variable_subgraph_possibility__new_with_compression(cause, worth__i, new_common_subgraph, new_this_remaining_subgraph, new_that_remaining_subgraph);
			      raw__common_variable_subgraph_possibility_redblacktree__consider_inserting(cause, new_subgraph_possibilities, new_possibility);
			    }
			    { // skip node in that graph.
			      f2ptr new_common_subgraph         = f2__graph__copy(cause, common_subgraph);
			      f2ptr new_this_remaining_subgraph = f2__graph__copy(cause, this_remaining_subgraph);
			      f2ptr new_that_remaining_subgraph = f2__graph__copy(cause, that_remaining_subgraph);
			      f2ptr that__arbitrary_node        = raw__graph__an_arbitrary_node(cause, new_that_remaining_subgraph);
			      f2ptr that__arbitrary_node__label = f2__graph_node__label(cause, that__arbitrary_node);
			      raw__graph__remove_node(cause, new_that_remaining_subgraph, that__arbitrary_node__label);
			      f2ptr new_possibility = f2__common_variable_subgraph_possibility__new_with_compression(cause, worth__i, new_common_subgraph, new_this_remaining_subgraph, new_that_remaining_subgraph);
			      raw__common_variable_subgraph_possibility_redblacktree__consider_inserting(cause, new_subgraph_possibilities, new_possibility);
			    }
			    );
    subgraph_possibilities = new_subgraph_possibilities;
  }
  return best_possibility;
}

f2ptr f2__graph__find_common_variable_subgraph(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__find_common_variable_subgraph(cause, this, that);
}
def_pcfunk2(graph__find_common_variable_subgraph, this, that, return f2__graph__find_common_variable_subgraph(this_cause, this, that));

// **

void f2__graph__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "graph", "", &f2__graph__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __graph_node__symbol      = new__symbol(cause, "graph_node");
  __graph_edge__symbol      = new__symbol(cause, "graph_edge");
  __graph_edge_type__symbol = new__symbol(cause, "graph_edge_type");
  __graph__symbol           = new__symbol(cause, "graph");
  __trans__symbol           = new__symbol(cause, "trans");
  __pattern_graph__symbol   = new__symbol(cause, "pattern_graph");
  __graph_variable__symbol  = new__symbol(cause, "graph_variable");
}

void f2__graph__initialize() {
  f2__graph__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // graph_node
  initialize_primobject_3_slot(graph_node, label, edges_left_node_hash_edge_hash, edges_right_node_hash_edge_hash);
  
  f2__primcfunk__init__1(graph_node__has_edges, this, "returns true if node has at least one edge, false otherwise.");
  
  // graph_edge
  initialize_primobject_3_slot(graph_edge, label, left_node, right_node);
  
  // graph_edge_type
  initialize_primobject_3_slot(graph_edge_type, label, left_node_hash, right_node_hash);
  
  // graph
  initialize_primobject_4_slot(graph, variable_name_hash, root_node, node_label_hash, edge_type_label_hash);
  
  {char* symbol_str = "equals"; __funk2.globalenv.object_type.primobject.primobject_type_graph.equals__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph__equals, this, that, cfunk, 0, "checks for equality between two graphs."); __funk2.globalenv.object_type.primobject.primobject_type_graph.equals__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_graph.equals_hash_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(graph__equals_hash_value, this, cfunk, 0, "calculates the equals_hash_value for a graph."); __funk2.globalenv.object_type.primobject.primobject_type_graph.equals_hash_value__funk = never_gc(cfunk);}
  {char* symbol_str = "part_not_contained_by"; __funk2.globalenv.object_type.primobject.primobject_type_graph.part_not_contained_by__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph__part_not_contained_by, this, that, cfunk, 0, "calculates the subgraph of this graph that is not contained in that graph."); __funk2.globalenv.object_type.primobject.primobject_type_graph.part_not_contained_by__funk = never_gc(cfunk);}
  {char* symbol_str = "as-frame"; __funk2.globalenv.object_type.primobject.primobject_type_graph.as__frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(rooted_graph__as__frame, this, cfunk, 0, "returns a rooted graph as a frame."); __funk2.globalenv.object_type.primobject.primobject_type_graph.as__frame__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__2(graph__add_node,                      this, node,                                                          "add a node to a graph by mutation.");
  f2__primcfunk__init__2(graph__lookup_node,                   this, node,                                                          "lookup a node if it exists within this graph.");
  f2__primcfunk__init__4(graph__add_edge,                      this, label, left_node, right_node,                                  "add an edge to a graph by mutation.");
  f2__primcfunk__init__2(graph__contains_node,                 this, node,                                                          "returns boolean true if this graph contains node.");
  f2__primcfunk__init__4(graph__contains_edge,                 this, label, left_node, right_node,                                  "returns boolean true if this graph contains edge.");
  f2__primcfunk__init__2(graph__lookup_edge_type,              this, edge_label,                                                    "returns edge type object if one exists for this edge label.");
  f2__primcfunk__init__2(graph__contains_edge_type,            this, edge_label,                                                    "returns boolean true if this graph contains at least one edge with the label.");
  f2__primcfunk__init__2(graph__intersect,                     this, that,                                                          "returns the intersection of two graphs.");
  f2__primcfunk__init__2(graph__union,                         this, that,                                                          "returns the union of two graphs.");
  f2__primcfunk__init__2(graph__remove_node,                   this, node,                                                          "remove node from this graph.");
  f2__primcfunk__init__4(graph__remove_edge,                   this, label, left_node, right_node,                                  "remove an edge from a perception graph.");
  f2__primcfunk__init__1(graph__copy,                          this,                                                                "returns a copy of this graph.");
  f2__primcfunk__init__2(graph__part_not_contained_by,         this, that,                                                          "determines the maximal part of this graph that is not contained in that graph.");
  f2__primcfunk__init__1(graph__variables,                     this,                                                                "returns variable names in a new list.");
  f2__primcfunk__init__1(graph__nodes,                         this,                                                                "returns a new list of all nodes in this graph.");
  f2__primcfunk__init__1(graph__edges,                         this,                                                                "returns a new list of all edges in this graph.");
  f2__primcfunk__init__3(graph__replace_node,                  this, old_node, new_node,                                            "replaces old node with new node.");
  f2__primcfunk__init__5(graph__replace_edge,                  this, edge_label, left_node_label, right_node_label, new_edge_label, "replaces old node with new node.");
  f2__primcfunk__init__3(graph__replace_edge_type,             this, edge_label, new_edge_label,                                    "replaces old edge type with new edge type.");
  f2__primcfunk__init__2(graph__make_rooted,                   this, root_node,                                                     "makes graph rooted with root node.");
  f2__primcfunk__init__1(graph__make_rootless,                 this,                                                                "makes graph rootless.");
  f2__primcfunk__init__3(graph__make_node_variable,            this, node, variable_name,                                           "makes a node in the graph a variable for matching.");
  f2__primcfunk__init__2(graph__make_node_wildcard,            this, node,                                                          "makes a node in the graph a wildcard variable for matching.");
  f2__primcfunk__init__5(graph__make_edge_variable,            this, edge_label, left_node_label, right_node_label, variable_name,  "makes an edge in the graph a variable for matching.");
  f2__primcfunk__init__4(graph__make_edge_wildcard,            this, edge_label, left_node_label, right_node_label,                 "makes an edge in the graph a wildcard variable for matching.");
  f2__primcfunk__init__3(graph__contains_match_with_bindings,  this, that, bindings,                                                "returns variable bindings for match.");
  f2__primcfunk__init__3(graph__bind_variable,                 this, variable_name, value,                                          "returns true if variable is successfully bound, false otherwise.");
  f2__primcfunk__init__1(graph__as__dot_code,                  this,                                                                "returns dot code in a string suitable for graphing with graphviz.");
  {
    {char* str = "common_variable_subgraph_possibility-compare"; __funk2.graph.common_variable_subgraph_possibility__compare__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
    {f2__primcfunk__init__with_c_cfunk_var__2_arg(common_variable_subgraph_possibility__compare, this, that, cfunk, 0,              "Internal part of graph-find_common_variable_subgraph.  Should not be end-user-accessible."); __funk2.graph.common_variable_subgraph_possibility__compare__funk = never_gc(cfunk);}
    f2__primcfunk__init__2(graph__find_common_variable_subgraph, this, that,                                                        "return the largest common variable subgraph shared by two graphs.");
  }
  
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
  
  // pattern_graph
  initialize_primobject_2_slot(pattern_graph, variable_label_hash, graph);
  
  // graph_variable
  initialize_primobject_1_slot(graph_variable, name);

  {char* symbol_str = "eq"; __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph_variable__eq, this, that, cfunk, 0, "checks for equality between two graph variables."); __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq__funk = never_gc(cfunk);}
  {char* symbol_str = "eq_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq_hash_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(graph_variable__eq_hash_value, this, cfunk, 0, "returns hash value for graph variable."); __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq_hash_value__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__1(graph_variable__is_wildcard, this, "returns true if this graph variable can take any value without restrictions.");
  
}

