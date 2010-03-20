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

// perception_graph_edge

def_primobject_3_slot(perception_graph_edge, label, left_node, right_node);

f2ptr f2__perception_graph_edge__new(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return f2perception_graph_edge__new(cause, label, left_node, right_node);
}
def_pcfunk3(perception_graph_edge__new, label, left_node, right_node, return f2__perception_graph_edge__new(this_cause, label, left_node, right_node));


// perception_graph

def_primobject_4_slot(perception_graph, nodes, edges, edges_node_hash, edge_structure_hash_value);

f2ptr f2__perception_graph__new(f2ptr cause) {
  return f2perception_graph__new(cause, nil, nil, f2__ptypehash__new(cause), f2integer__new(cause, 1));
}
def_pcfunk0(perception_graph__new, return f2__perception_graph__new(this_cause));

f2ptr raw__perception_graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
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

f2ptr f2__perception_graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__add_node(cause, this, node);
}
def_pcfunk2(perception_graph__add_node, this, node, return f2__perception_graph__add_node(this_cause, this, node));


boolean_t raw__perception_graph__subtract_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr edges_node_hash = f2__perception_graph__edges_node_hash(cause, this);
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
	  f2ptr label      = f2__perception_graph_edge__label(cause, edge);
	  f2ptr left_node  = f2__perception_graph_edge__left_node(cause, edge);
	  f2ptr right_node = f2__perception_graph_edge__right_node(cause, edge);
	  raw__perception_graph__subtract_edge(cause, this, label, left_node, right_node);
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
	  f2ptr label      = f2__perception_graph_edge__label(cause, edge);
	  f2ptr left_node  = f2__perception_graph_edge__left_node(cause, edge);
	  f2ptr right_node = f2__perception_graph_edge__right_node(cause, edge);
	  raw__perception_graph__subtract_edge(cause, this, label, left_node, right_node);
	}
	iter = next;
      }
    }
  }
  raw__ptypehash__remove(cause, edges_node_hash, node);
  f2ptr nodes = f2__perception_graph__nodes(cause, this);
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
	  f2__perception_graph__nodes__set(cause, this, next);
	}
      }
      prev = iter;
      iter = next;
    }
  }
  return node_was_removed;
}

f2ptr f2__perception_graph__subtract_node(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__perception_graph__subtract_node(cause, this, node));
}
def_pcfunk2(perception_graph__subtract_node, this, node, return f2__perception_graph__subtract_node(this_cause, this, node));


f2ptr raw__perception_graph__add_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
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
  f2__perception_graph__edges__set(cause, this, f2cons__new(cause, edge, f2__perception_graph__edges(cause, this)));
  return edge;
}

f2ptr f2__perception_graph__add_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__add_edge(cause, this, label, left_node, right_node);
}
def_pcfunk4(perception_graph__add_edge, this, label, left_node, right_node, return f2__perception_graph__add_edge(this_cause, this, label, left_node, right_node));

f2ptr raw__perception_graph__node__ins_and_outs(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr edges_node_hash = f2__perception_graph__edges_node_hash(cause, this);
  return f2__ptypehash__lookup(cause, edges_node_hash, node);
}

f2ptr f2__perception_graph__node__ins_and_outs(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__node__ins_and_outs(cause, this, node);
}
def_pcfunk2(perception_graph__node__ins_and_outs, this, node, return f2__perception_graph__node__ins_and_outs(this_cause, this, node));

boolean_t raw__perception_graph__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  return (f2__perception_graph__node__ins_and_outs(cause, this, node) != nil);
}

f2ptr f2__perception_graph__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__perception_graph__contains_node(cause, this, node));
}
def_pcfunk2(perception_graph__contains_node, this, node, return f2__perception_graph__contains_node(this_cause, this, node));

f2ptr raw__perception_graph__node__ins(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr ins_and_outs = f2__perception_graph__node__ins_and_outs(cause, this, node);
  return f2__cons__car(cause, ins_and_outs);
}

f2ptr f2__perception_graph__node__ins(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__node__ins(cause, this, node);
}
def_pcfunk2(perception_graph__node__ins, this, node, return f2__perception_graph__node__ins(this_cause, this, node));


f2ptr raw__perception_graph__node__ins__set(f2ptr cause, f2ptr this, f2ptr node, f2ptr ins) {
  f2ptr ins_and_outs = f2__perception_graph__node__ins_and_outs(cause, this, node);
  return f2__cons__car__set(cause, ins_and_outs, ins);
}

f2ptr f2__perception_graph__node__ins__set(f2ptr cause, f2ptr this, f2ptr node, f2ptr ins) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__node__ins__set(cause, this, node, ins);
}
def_pcfunk3(perception_graph__node__ins__set, this, node, ins, return f2__perception_graph__node__ins__set(this_cause, this, node, ins));


f2ptr raw__perception_graph__node__outs(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr ins_and_outs = f2__perception_graph__node__ins_and_outs(cause, this, node);
  return f2__cons__cdr(cause, ins_and_outs);
}

f2ptr f2__perception_graph__node__outs(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__node__outs(cause, this, node);
}
def_pcfunk2(perception_graph__node__outs, this, node, return f2__perception_graph__node__outs(this_cause, this, node));


f2ptr raw__perception_graph__node__outs__set(f2ptr cause, f2ptr this, f2ptr node, f2ptr outs) {
  f2ptr ins_and_outs = f2__perception_graph__node__ins_and_outs(cause, this, node);
  return f2__cons__cdr__set(cause, ins_and_outs, outs);
}

f2ptr f2__perception_graph__node__outs__set(f2ptr cause, f2ptr this, f2ptr node, f2ptr outs) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__node__outs__set(cause, this, node, outs);
}
def_pcfunk3(perception_graph__node__outs__set, this, node, outs, return f2__perception_graph__node__outs__set(this_cause, this, node, outs));


boolean_t raw__perception_graph__contains_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if ((! raw__perception_graph__contains_node(cause, this, left_node)) ||
      (! raw__perception_graph__contains_node(cause, this, right_node))) {
    return boolean__false;
  }
  f2ptr left_node__outs = raw__perception_graph__node__outs(cause, this, left_node);
  {
    f2ptr iter = left_node__outs;
    while (iter) {
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr edge__label      = f2__perception_graph_edge__label(     cause, edge);
	f2ptr edge__right_node = f2__perception_graph_edge__right_node(cause, edge);
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

f2ptr f2__perception_graph__contains_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__contains_edge(cause, this, label, left_node, right_node);
}
def_pcfunk4(perception_graph__contains_edge, this, label, left_node, right_node, return f2__perception_graph__contains_edge(this_cause, this, label, left_node, right_node));

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

// equals_equals is ill-defined
boolean_t raw__perception_graph__equals_equals(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__nodes         = f2__perception_graph__nodes(cause, this);
  f2ptr that__nodes         = f2__perception_graph__nodes(cause, that);
  u64   this__nodes__length = raw__simple_length(cause, this__nodes);
  u64   that__nodes__length = raw__simple_length(cause, that__nodes);
  if (this__nodes__length != that__nodes__length) {
    return boolean__false;
  }
  f2ptr this__edges         = f2__perception_graph__edges(cause, this);
  f2ptr that__edges         = f2__perception_graph__edges(cause, that);
  u64   this__edges__length = raw__simple_length(cause, this__edges);
  u64   that__edges__length = raw__simple_length(cause, that__edges);
  if (this__edges__length != that__edges__length) {
    return boolean__false;
  }
  {
    f2ptr this__hash_value    = f2__perception_graph__equals_hash_value(cause, this);
    f2ptr that__hash_value    = f2__perception_graph__equals_hash_value(cause, that);
    u64   this__hash_value__i = f2integer__i(this__hash_value, cause);
    u64   that__hash_value__i = f2integer__i(that__hash_value, cause);
    if (this__hash_value__i != that__hash_value__i) {
      return boolean__false;
    }
  }
  {
    f2ptr this__equals_node_hash = f2__hash(cause);
    {
      f2ptr iter = this__nodes;
      while (iter) {
	f2ptr this__node = f2__cons__car(cause, iter);
	f2__hash__add(cause, this__equals_node_hash, this__node, __funk2.globalenv.true__symbol);
	iter = f2__cons__cdr(cause, iter);
      }
    }
    {
      f2ptr iter = that__nodes;
      while (iter) {
	f2ptr that__node = f2__cons__car(cause, iter);
	if (! raw__hash__contains(cause, this__equals_node_hash, that__node)) {
	  return boolean__false;
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  {
    f2ptr this__equals_edge_hash = f2__hash(cause);
    {
      f2ptr iter = this__edges;
      while (iter) {
	f2ptr this__edge = f2__cons__car(cause, iter);
	f2__hash__add(cause, this__equals_edge_hash, this__edge, __funk2.globalenv.true__symbol);
	iter = f2__cons__cdr(cause, iter);
      }
    }
    {
      f2ptr iter = that__edges;
      while (iter) {
	f2ptr that__edge = f2__cons__car(cause, iter);
	if (! raw__hash__contains(cause, this__equals_edge_hash, that__edge)) {
	  return boolean__false;
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  // still not complete.  consider:
  // 
  //      ()          ()
  //     ^ |         ^ |
  //    /  |        /  |
  //  ()   |  !=  ()   |
  //    ^  |        \  |
  //     \ v         v v
  //      ()          ()
  //
  // which the above still considers equal because all nodes and edges are contained in the other.
  //
  // this could/should be replaced by finding node bijection (mapping) if one exists (equal, otherwise not equal)
  return boolean__true;
}

boolean_t raw__perception_graph__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return boolean__false;
}

f2ptr f2__perception_graph__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__perception_graph__is_type(cause, this)) ||
      (! raw__perception_graph__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__perception_graph__equals(cause, this, that));
}
def_pcfunk2(perception_graph__equals, this, that, return f2__perception_graph__equals(this_cause, this, that));

f2ptr f2__perception_graph__equals_equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  if (raw__ptypehash__contains(cause, node_hash, this)) {
    return f2integer__new(cause, 1);
  }
  raw__ptypehash__add(cause, node_hash, this, __funk2.globalenv.true__symbol);
  u64 hash_value = 1;
  f2ptr edges = f2__perception_graph__edges(cause, this);
  {
    f2ptr iter = edges;
    while (iter) {
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr label      = f2__perception_graph_edge__label(     cause, edge);
 	f2ptr left_node  = f2__perception_graph_edge__left_node( cause, edge);
 	f2ptr right_node = f2__perception_graph_edge__right_node(cause, edge);
	if (label) {
	  f2ptr result = f2__object__equals_hash_value__loop_free(cause, label, node_hash);
	  {
	    if (raw__larva__is_type(cause, result)) {
	      return result;
	    }
	    u64 result__i = f2integer__i(result, cause);
	    hash_value *= result__i;
	  }
	}
	if (left_node) {
	  f2ptr result = f2__object__equals_hash_value__loop_free(cause, left_node, node_hash);
	  {
	    if (raw__larva__is_type(cause, result)) {
	      return result;
	    }
	    u64 result__i = f2integer__i(result, cause);
	    hash_value *= result__i;
	  }
	}
	if (right_node) {
	  f2ptr result = f2__object__equals_hash_value__loop_free(cause, right_node, node_hash);
	  {
	    if (raw__larva__is_type(cause, result)) {
	      return result;
	    }
	    u64 result__i = f2integer__i(result, cause);
	    hash_value *= result__i;
	  }
	}
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return f2integer__new(cause, hash_value);
}
def_pcfunk2(perception_graph__equals_equals_hash_value__loop_free, this, node_hash, return f2__perception_graph__equals_equals_hash_value__loop_free(this_cause, this, node_hash));

f2ptr f2__perception_graph__equals_equals_hash_value(f2ptr cause, f2ptr this) {
  f2ptr node_hash = f2__ptypehash__new(cause);
  return f2__perception_graph__equals_equals_hash_value__loop_free(cause, this, node_hash);
}

f2ptr f2__perception_graph__equals_hash_value(f2ptr cause, f2ptr this) {
  return nil;
}
def_pcfunk1(perception_graph__equals_hash_value, this, return f2__perception_graph__equals_hash_value(this_cause, this));

// perception_graph__bijection__search_possitibility

f2ptr f2__perception_graph__bijection__search_possibility__new(f2ptr cause, f2ptr bijection, f2ptr this_graph_left, f2ptr that_graph_left) {
  f2ptr this = raw__array__new(cause, 3);
  raw__array__elt__set(cause, this, 0, bijection);
  raw__array__elt__set(cause, this, 1, this_graph_left);
  raw__array__elt__set(cause, this, 2, that_graph_left);
  return this;
}

f2ptr raw__perception_graph__bijection__search_possibility__bijection(      f2ptr cause, f2ptr this) {return raw__array__elt(cause, this, 0);}
f2ptr raw__perception_graph__bijection__search_possibility__this_graph_left(f2ptr cause, f2ptr this) {return raw__array__elt(cause, this, 1);}
f2ptr raw__perception_graph__bijection__search_possibility__that_graph_left(f2ptr cause, f2ptr this) {return raw__array__elt(cause, this, 2);}

f2ptr raw__perception_graph__bijection(f2ptr cause, f2ptr this, f2ptr that) {
  {
    f2ptr this__nodes = f2__perception_graph__nodes(cause, this);
    f2ptr that__nodes = f2__perception_graph__nodes(cause, that);
    if ((this__nodes == nil) && (that__nodes == nil)) {
      f2ptr bijection = f2__perception_graph__new(cause);
      // return empty bijection graph.
      return bijection;
    }
    u64 this__nodes__length = raw__simple_length(cause, this__nodes);
    u64 that__nodes__length = raw__simple_length(cause, that__nodes);
    if (this__nodes__length != that__nodes__length) {
      // no bijection can be found.
      return nil;
    }
  }
  {
    f2ptr this__edges         = f2__perception_graph__edges(cause, this);
    f2ptr that__edges         = f2__perception_graph__edges(cause, that);
    u64   this__edges__length = raw__simple_length(cause, this__edges);
    u64   that__edges__length = raw__simple_length(cause, that__edges);
    if (this__edges__length != that__edges__length) {
      // no bijection can be found.
      return nil;
    }
  }
  f2ptr search_possibilities = nil;
  {
    f2ptr search_possibility = f2__perception_graph__bijection__search_possibility__new(cause, f2__perception_graph__new(cause), this, that);
    search_possibilities = f2cons__new(cause, search_possibility, search_possibilities);
  }
  while (search_possibilities) {
    f2ptr search_possibilities__next = f2__cons__cdr(cause, search_possibilities);
    {
      f2ptr search_possibility = f2__cons__car(cause, search_possibilities);
      {
	f2ptr bijection       = raw__perception_graph__bijection__search_possibility__bijection(      cause, search_possibility);
	f2ptr this_graph_left = raw__perception_graph__bijection__search_possibility__this_graph_left(cause, search_possibility);
	f2ptr that_graph_left = raw__perception_graph__bijection__search_possibility__that_graph_left(cause, search_possibility);
	{
	  
	}
      }
    }
    search_possibilities = search_possibilities__next;
  }
  return nil;
}

f2ptr f2__perception_graph__bijection(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__perception_graph__is_type(cause, this)) ||
      (! raw__perception_graph__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__bijection(cause, this, that);
}
def_pcfunk2(perception_graph__bijection, this, that, return f2__perception_graph__bijection(this_cause, this, that));

f2ptr f2perception_graph__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2perception_graph__primobject_type__new(cause);
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals_hash_value__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals_hash_value__loop_free__funk);}
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

f2ptr raw__perception_graph__subgraphs_of_node_range(f2ptr cause, f2ptr this, u64 min_node_count, u64 max_node_count) {
  f2ptr nodes         = f2__perception_graph__nodes(cause, this);
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
		f2ptr outs = f2__perception_graph__node__outs(cause, this, node);
		{
		  f2ptr iter = outs;
		  while (iter) {
		    f2ptr edge       = f2__cons__car(cause, iter);
		    f2ptr right_node = f2__perception_graph_edge__right_node(cause, edge);
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
		      f2ptr graph = f2__perception_graph__new(cause);
		      {
			u64 index;
			for (index = 0; index < node_choose.k; index ++) {
			  f2ptr node = nodes_array[node_choose.indices[index]];
			  f2__perception_graph__add_node(cause, graph, node);
			}
		      }
		      {
			u64 index;
			for (index = 0; index < edge_choose.k; index ++) {
			  f2ptr edge = edges_array[edge_choose.indices[index]];
			  {
			    f2ptr edge__label      = f2__perception_graph_edge__label(     cause, edge);
			    f2ptr edge__left_node  = f2__perception_graph_edge__left_node( cause, edge);
			    f2ptr edge__right_node = f2__perception_graph_edge__right_node(cause, edge);
			    f2__perception_graph__add_edge(cause, graph, edge__label, edge__left_node, edge__right_node);
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

f2ptr f2__perception_graph__subgraphs_of_node_range(f2ptr cause, f2ptr this, f2ptr min_node_count, f2ptr max_node_count) {
  if ((! raw__perception_graph__is_type(cause, this)) ||
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
  return raw__perception_graph__subgraphs_of_node_range(cause, this, min_node_count__i, max_node_count__i);
}
def_pcfunk3(perception_graph__subgraphs_of_node_range, this, min_node_count, max_node_count, return f2__perception_graph__subgraphs_of_node_range(this_cause, this, min_node_count, max_node_count));

f2ptr raw__perception_graph__subgraphs(f2ptr cause, f2ptr this) {
  f2ptr nodes         = f2__perception_graph__nodes(cause, this);
  u64   nodes__length = raw__simple_length(cause, nodes);
  return raw__perception_graph__subgraphs_of_node_range(cause, this, 0, nodes__length);
}

f2ptr f2__perception_graph__subgraphs(f2ptr cause, f2ptr this) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__subgraphs(cause, this);
}
def_pcfunk1(perception_graph__subgraphs, this, return f2__perception_graph__subgraphs(this_cause, this));

f2ptr raw__perception_graph__intersect(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__nodes         = f2__perception_graph__nodes(cause, this);
  f2ptr that__nodes         = f2__perception_graph__nodes(cause, that);
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
  f2ptr new_graph = f2__perception_graph__new(cause);
  {
    f2ptr small__nodes = f2__perception_graph__nodes(cause, small);
    f2ptr small__edges = f2__perception_graph__edges(cause, small);
    {
      f2ptr iter = small__nodes;
      while (iter) {
	f2ptr node = f2__cons__car(cause, iter);
	if (f2__perception_graph__contains_node(cause, large, node)) {
	  f2__perception_graph__add_node(cause, new_graph, node);
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
    {
      f2ptr iter = small__edges;
      while (iter) {
	f2ptr small__edge = f2__cons__car(cause, iter);
	{
	  f2ptr small__left_node = f2__perception_graph_edge__left_node(cause, small__edge);
	  if (f2__perception_graph__contains_node(cause, large, small__left_node)) {
	    f2ptr shared__left_node = small__left_node;
	    f2ptr small__right_node = f2__perception_graph_edge__right_node(cause, small__edge);
	    if (f2__perception_graph__contains_node(cause, large, small__right_node)) {
	      f2ptr shared__right_node = small__right_node;
	      f2ptr small__label = f2__perception_graph_edge__label(cause, small__edge);
	      f2ptr large__left_node__outs = f2__perception_graph__node__outs(cause, large, shared__left_node);
	      {
		f2ptr large_outs_iter = large__left_node__outs;
		while (large_outs_iter) {
		  f2ptr large__left_node__out_edge             = f2__cons__car(cause, large_outs_iter);
		  f2ptr large__left_node__out_edge__right_node = f2__perception_graph_edge__right_node(cause, large__left_node__out_edge);
		  if (raw__eq(cause, shared__right_node, large__left_node__out_edge__right_node)) {
		    f2ptr large__label = f2__perception_graph_edge__label(cause, large__left_node__out_edge);
		    if (raw__eq(cause, small__label, large__label)) {
		      f2ptr shared__label = small__label;
		      f2__perception_graph__add_edge(cause, new_graph, shared__label, shared__left_node, shared__right_node);
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

f2ptr f2__perception_graph__intersect(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__perception_graph__is_type(cause, this)) ||
      (! raw__perception_graph__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__intersect(cause, this, that);
}
def_pcfunk2(perception_graph__intersect, this, that, return f2__perception_graph__intersect(this_cause, this, that));

f2ptr raw__perception_graph__union(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr new_graph = f2__perception_graph__new(cause);
  {
    f2ptr this__nodes         = f2__perception_graph__nodes(cause, this);
    f2ptr that__nodes         = f2__perception_graph__nodes(cause, that);
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
	  f2__perception_graph__add_node(cause, new_graph, node);
	  iter = f2__cons__cdr(cause, iter);
	}
      }
      {
	f2ptr iter = small__nodes;
	while (iter) {
	  f2ptr node = f2__cons__car(cause, iter);
	  if (! f2__perception_graph__contains_node(cause, new_graph, node)) {
	    f2__perception_graph__add_node(cause, new_graph, node);
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
    }
    f2ptr this__edges         = f2__perception_graph__edges(cause, this);
    f2ptr that__edges         = f2__perception_graph__edges(cause, that);
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
	    f2ptr label      = f2__perception_graph_edge__label(     cause, edge);
	    f2ptr left_node  = f2__perception_graph_edge__left_node( cause, edge);
	    f2ptr right_node = f2__perception_graph_edge__right_node(cause, edge);
	    f2__perception_graph__add_edge(cause, new_graph, label, left_node, right_node);
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
      {
	f2ptr iter = small__edges;
	while (iter) {
	  f2ptr edge = f2__cons__car(cause, iter);
	  {
	    f2ptr label      = f2__perception_graph_edge__label(     cause, edge);
	    f2ptr left_node  = f2__perception_graph_edge__left_node( cause, edge);
	    f2ptr right_node = f2__perception_graph_edge__right_node(cause, edge);
	    if (! raw__perception_graph__contains_edge(cause, small, label, left_node, right_node)) {
	      f2__perception_graph__add_edge(cause, new_graph, label, left_node, right_node);
	    }
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
    }
  }
  return new_graph;
}

f2ptr f2__perception_graph__union(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__perception_graph__is_type(cause, this)) ||
      (! raw__perception_graph__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__union(cause, this, that);
}
def_pcfunk2(perception_graph__union, this, that, return f2__perception_graph__union(this_cause, this, that));

boolean_t raw__perception_graph__subtract_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  boolean_t left_node__outs__was_removed = boolean__false;
  f2ptr     left_node__outs              = raw__perception_graph__node__outs(cause, this, left_node);
  {
    f2ptr prev = nil;
    f2ptr iter = left_node__outs;
    while (iter) {
      f2ptr next = f2__cons__cdr(cause, iter);
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr edge__label      = f2__perception_graph_edge__label(     cause, edge);
	f2ptr edge__left_node  = f2__perception_graph_edge__left_node( cause, edge);
	f2ptr edge__right_node = f2__perception_graph_edge__right_node(cause, edge);
	if (raw__eq(cause, edge__label,      label)     &&
	    raw__eq(cause, edge__left_node,  left_node) &&
	    raw__eq(cause, edge__right_node, right_node)) {
	  if (prev) {
	    f2__cons__cdr__set(cause, prev, next);
	  } else {
	    left_node__outs = next;
	    raw__perception_graph__node__outs__set(cause, this, left_node, left_node__outs);
	  }
	  left_node__outs__was_removed = boolean__true;
	}
      }
      prev = iter;
      iter = next;
    }
  }
  boolean_t right_node__ins__was_removed = boolean__false;
  f2ptr     right_node__ins              = raw__perception_graph__node__ins(cause, this, right_node);
  {
    f2ptr prev = nil;
    f2ptr iter = right_node__ins;
    while (iter) {
      f2ptr next = f2__cons__cdr(cause, iter);
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr edge__label      = f2__perception_graph_edge__label(     cause, edge);
	f2ptr edge__left_node  = f2__perception_graph_edge__left_node( cause, edge);
	f2ptr edge__right_node = f2__perception_graph_edge__right_node(cause, edge);
	if (raw__eq(cause, edge__label,      label)     &&
	    raw__eq(cause, edge__left_node,  left_node) &&
	    raw__eq(cause, edge__right_node, right_node)) {
	  if (prev) {
	    f2__cons__cdr__set(cause, prev, next);
	  } else {
	    right_node__ins = next;
	    raw__perception_graph__node__ins__set(cause, this, right_node, right_node__ins);
	  }
	  right_node__ins__was_removed = boolean__true;
	}
      }
      prev = iter;
      iter = next;
    }
  }
  boolean_t edges__was_removed = boolean__false;
  f2ptr edges = f2__perception_graph__edges(cause, this);
  {
    f2ptr prev = nil;
    f2ptr iter = edges;
    while (iter) {
      f2ptr next = f2__cons__cdr(cause, iter);
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr edge__label      = f2__perception_graph_edge__label(     cause, edge);
	f2ptr edge__left_node  = f2__perception_graph_edge__left_node( cause, edge);
	f2ptr edge__right_node = f2__perception_graph_edge__right_node(cause, edge);
	if (raw__eq(cause, edge__label,      label)     &&
	    raw__eq(cause, edge__left_node,  left_node) &&
	    raw__eq(cause, edge__right_node, right_node)) {
	  if (prev) {
	    f2__cons__cdr__set(cause, prev, next);
	  } else {
	    f2__perception_graph__edges__set(cause, this, next);
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
    f2ptr right_node__outs = raw__perception_graph__node__outs(cause, this, right_node);
    if (right_node__outs == nil) {
      raw__perception_graph__subtract_node(cause, this, right_node);
    }
  }
  if (left_node__outs == nil) {
    f2ptr left_node__ins = raw__perception_graph__node__ins(cause, this, left_node);
    if (left_node__ins == nil) {
      raw__perception_graph__subtract_node(cause, this, left_node);
    }
  }
  return left_node__outs__was_removed;
}

f2ptr f2__perception_graph__subtract_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__perception_graph__subtract_edge(cause, this, label, left_node, right_node));
}
def_pcfunk4(perception_graph__subtract_edge, this, label, left_node, right_node, return f2__perception_graph__subtract_edge(this_cause, this, label, left_node, right_node));

f2ptr raw__perception_graph__copy(f2ptr cause, f2ptr this) {
  f2ptr new_graph = f2__perception_graph__new(cause);
  f2ptr nodes = f2__perception_graph__nodes(cause, this);
  {
    f2ptr iter = nodes;
    while (iter) {
      f2ptr node = f2__cons__car(cause, iter);
      raw__perception_graph__add_node(cause, new_graph, node);
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr edges = f2__perception_graph__edges(cause, this);
  {
    f2ptr iter = edges;
    while (iter) {
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr label      = f2__perception_graph_edge__label(     cause, edge);
	f2ptr left_node  = f2__perception_graph_edge__left_node( cause, edge);
	f2ptr right_node = f2__perception_graph_edge__right_node(cause, edge);
	raw__perception_graph__add_edge(cause, new_graph, label, left_node, right_node);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return new_graph;
}

f2ptr f2__perception_graph__copy(f2ptr cause, f2ptr this) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__perception_graph__copy(cause, this);
}
def_pcfunk1(perception_graph__copy, this, return f2__perception_graph__copy(this_cause, this));


void raw__perception_graph__subtract(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr edges = f2__perception_graph__edges(cause, that);
  {
    f2ptr iter = edges;
    while (iter) {
      f2ptr next = f2__cons__cdr(cause, iter);
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr label      = f2__perception_graph_edge__label(     cause, edge);
	f2ptr left_node  = f2__perception_graph_edge__left_node( cause, edge);
	f2ptr right_node = f2__perception_graph_edge__right_node(cause, edge);
	raw__perception_graph__subtract_edge(cause, this, label, left_node, right_node);
      }
      iter = next;
    }
  }
}

f2ptr f2__perception_graph__subtract(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__perception_graph__is_type(cause, this)) ||
      (! raw__perception_graph__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  raw__perception_graph__subtract(cause, this, that);
  return nil;
}
def_pcfunk2(perception_graph__subtract, this, that, return f2__perception_graph__subtract(this_cause, this, that));

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
  initialize_primobject_4_slot(perception_graph, nodes, edges, edges_node_hash, edge_structure_hash_value);
  
  {char* symbol_str = "equals"; __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(perception_graph__equals, this, that, cfunk, 0, "checks for equality between two graphs."); __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals_hash_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(perception_graph__equals_hash_value, this, cfunk, 0, "calculates the equals_hash_value for a graph."); __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals_hash_value__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals_hash_value__loop_free__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(perception_graph__equals_hash_value__loop_free, this, cfunk, 0, "calculates the equals_hash_value-loop_free for a graph."); __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__2(perception_graph__add_node,           this, node,                         "add a node to a graph by mutation.");
  f2__primcfunk__init__4(perception_graph__add_edge,           this, label, left_node, right_node, "add an edge to a graph by mutation.");
  f2__primcfunk__init__2(perception_graph__node__ins_and_outs, this, node,                         "get in and out edges of a node.");
  f2__primcfunk__init__2(perception_graph__contains_node,      this, node,                         "returns boolean true if this graph contains node.");
  f2__primcfunk__init__2(perception_graph__node__ins,          this, node,                         "returns node in edges.");
  f2__primcfunk__init__3(perception_graph__node__ins__set,     this, node, ins,                    "sets node in edges.");
  f2__primcfunk__init__2(perception_graph__node__outs,         this, node,                         "returns node out edges.");
  f2__primcfunk__init__3(perception_graph__node__outs__set,    this, node, outs,                   "sets node out edges.");
  f2__primcfunk__init__4(perception_graph__contains_edge,      this, label, left_node, right_node, "returns boolean true if this graph contains edge.");
  
  f2__primcfunk__init__1(perception_graph__new_from_string, string, "creates a perception_graph of characters from a string.  (function used for debugging graph matching)");
  f2__primcfunk__init__1(perception_graph__to_string, this, "creates a string from a perception_graph made from a string.  (function used for debugging graph matching)");
  f2__primcfunk__init__2(perception_graph__bijection, this, that, "find a node bijection between two graph if one exists.");
  f2__primcfunk__init__3(perception_graph__subgraphs_of_node_range, this, min_node_count, max_node_count, "returns all subgraphs with min_node_count to max_node_count nodes.");
  f2__primcfunk__init__1(perception_graph__subgraphs, this, "returns all subgraphs of graph.");
  f2__primcfunk__init__2(perception_graph__intersect, this, that, "returns the intersection of two graphs.");
  f2__primcfunk__init__2(perception_graph__union, this, that, "returns the union of two graphs.");
  f2__primcfunk__init__2(perception_graph__subtract_node, this, node, "subtract node from this graph.");
  f2__primcfunk__init__4(perception_graph__subtract_edge, this, label, left_node, right_node, "subtract an edge from a perception graph.");
  f2__primcfunk__init__1(perception_graph__copy, this, "returns a copy of this graph.");
  f2__primcfunk__init__2(perception_graph__subtract, this, that, "subtract edges in that graph from this graph.");
}

