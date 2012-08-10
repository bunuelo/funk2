// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#include "../../c/funk2.h"
#include "../semantic_knowledge_base/semantic_knowledge_base.h"
#include "meta_semantic_knowledge_base.h"





// meta_semantic_frame

f2ptr raw__meta_semantic_frame__new(f2ptr cause, f2ptr realm) {
  f2ptr this = f2__semantic_frame__new(cause, realm);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "meta_semantic_frame"));
  return this;
}

f2ptr f2__meta_semantic_frame__new(f2ptr cause, f2ptr realm) {
  return raw__meta_semantic_frame__new(cause, realm);
}
export_cefunk1(meta_semantic_frame__new, realm, 0, "Returns a new meta_semantic_frame object.");


boolean_t raw__meta_semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "meta_semantic_frame");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__meta_semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__meta_semantic_frame__is_type(cause, thing));
}
export_cefunk1(meta_semantic_frame__is_type, thing, 0, "Returns whether or not thing is of type meta_semantic_frame.");


f2ptr raw__meta_semantic_frame__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__meta_semantic_frame__type(f2ptr cause, f2ptr this) {
  if (! raw__meta_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_frame__type(cause, this);
}
export_cefunk1(meta_semantic_frame__type, thing, 0, "Returns the specific type of object that this meta_semantic_frame is.");


f2ptr f2__meta_semantic_frame_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_frame__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_frame__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_frame__type")));}
  return this;
}



// meta_semantic_object

f2ptr raw__meta_semantic_object__new(f2ptr cause, f2ptr realm) {
  f2ptr this = f2__semantic_frame__new(cause, realm);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "meta_semantic_object"));
  return this;
}

f2ptr f2__meta_semantic_object__new(f2ptr cause, f2ptr realm) {
  return raw__meta_semantic_object__new(cause, realm);
}
export_cefunk1(meta_semantic_object__new, realm, 0, "Returns a new meta_semantic_object object.");


boolean_t raw__meta_semantic_object__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "meta_semantic_object");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__meta_semantic_object__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__meta_semantic_object__is_type(cause, thing));
}
export_cefunk1(meta_semantic_object__is_type, thing, 0, "Returns whether or not thing is of type meta_semantic_object.");


f2ptr raw__meta_semantic_object__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__meta_semantic_object__type(f2ptr cause, f2ptr this) {
  if (! raw__meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_object__type(cause, this);
}
export_cefunk1(meta_semantic_object__type, thing, 0, "Returns the specific type of object that this meta_semantic_object is.");


f2ptr f2__meta_semantic_object_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_object__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_object__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_object__type")));}
  return this;
}



// meta_semantic_knowledge_base

/*
f2ptr raw__meta_semantic_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  f2ptr this = f2__semantic_knowledge_base__new(cause, name, semantic_realm);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "meta_semantic_knowledge_base"));
  return this;
}

f2ptr f2__meta_semantic_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__new(cause, name, semantic_realm);
}
export_cefunk2(meta_semantic_knowledge_base__new, name, semantic_realm, 0, "Given a name and a semantic_realm, returns a new meta_semantic_knowledge_base object.");
*/



f2ptr raw__meta_semantic_knowledge_base__type_create(f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "meta_semantic_knowledge_base"));
  }
  assert_value(raw__semantic_knowledge_base__type_create(cause, this, name, semantic_realm));
  return this;
}

f2ptr raw__meta_semantic_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__meta_semantic_knowledge_base__type_create(cause, this, name, semantic_realm));
  return this;
}

f2ptr f2__meta_semantic_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__meta_semantic_knowledge_base__new(cause, name, semantic_realm);
}
export_cefunk2(meta_semantic_knowledge_base__new, name, semantic_realm, 0, "Given a name and a semantic_realm, returns a new meta_semantic_knowledge_base object.");





boolean_t raw__meta_semantic_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "meta_semantic_knowledge_base");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__meta_semantic_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__meta_semantic_knowledge_base__is_type(cause, thing));
}
export_cefunk1(meta_semantic_knowledge_base__is_type, thing, 0, "Returns whether or not thing is of type meta_semantic_knowledge_base.");


f2ptr raw__meta_semantic_knowledge_base__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__meta_semantic_knowledge_base__type(f2ptr cause, f2ptr this) {
  if (! raw__meta_semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__type(cause, this);
}
export_cefunk1(meta_semantic_knowledge_base__type, thing, 0, "Returns the specific type of object that this meta_semantic_knowledge_base is.");


f2ptr raw__meta_semantic_knowledge_base__add_trans_level_edges_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, s64 maximum_size, s64* exact_size) {
  f2ptr set = f2__set__new(cause);
  if (! raw__semantic_knowledge_base__recursively_add_semantic_frames_to_set(cause, this, set, maximum_size, exact_size)) {
    return f2larva__new(cause, 42132, nil);
  }
  set__iteration(cause, set, semantic_frame,
		 f2ptr add_trans_edges_funk = f2__object__slot__type_funk(cause, semantic_frame, new__symbol(cause, "execute"), new__symbol(cause, "add_trans_level_edges_to_graph_with_node_ptypehash"));
		 if (raw__funkable__is_type(cause, add_trans_edges_funk)) {
		   f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), add_trans_edges_funk, f2list3__new(cause, semantic_frame, graph, node_ptypehash));
		   if (raw__larva__is_type(cause, result)) {
		     return result;
		   }
		 }
		 );
  return nil;
}

f2ptr f2__meta_semantic_knowledge_base__add_trans_level_edges_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, f2ptr maximum_size, f2ptr exact_size_place) {
  if ((! raw__meta_semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, graph)) ||
      (! raw__ptypehash__is_type(cause, node_ptypehash)) ||
      (! raw__integer__is_type(cause, maximum_size)) ||
      ((exact_size_place != nil) && (! raw__place__is_type(cause, exact_size_place)))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 maximum_size__i = f2integer__i(maximum_size, cause);
  s64 exact_size__i   = 0;
  f2ptr result = raw__meta_semantic_knowledge_base__add_trans_level_edges_to_graph_with_node_ptypehash(cause, this, graph, node_ptypehash, maximum_size__i, &exact_size__i);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  if (raw__place__is_type(cause, exact_size_place)) {
    f2__place__thing__set(cause, exact_size_place, f2integer__new(cause, exact_size__i));
  }
  return result;
}
export_cefunk5(meta_semantic_knowledge_base__add_trans_level_edges_to_graph_with_node_ptypehash, this, graph, node_ptypehash, maximum_size, exact_size_place, 0, "Adds trans-level edges from all nodes (if they exist).");


f2ptr f2__meta_semantic_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_knowledge_base")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                                                f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                                            f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                                               f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_trans_level_edges_to_graph_with_node_ptypehash"), f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__add_trans_level_edges_to_graph_with_node_ptypehash")));}
  return this;
}



// relationship_meta_semantic_object

f2ptr raw__relationship_meta_semantic_object__new(f2ptr cause, f2ptr realm, f2ptr source, f2ptr key_type, f2ptr key, f2ptr target) {
  f2ptr this = f2__meta_semantic_frame__new(cause, realm);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "relationship_meta_semantic_object"));
  raw__frame__add_var_value(cause, this, new__symbol(cause, "source"),   source);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "key_type"), key_type);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "key"),      key);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "target"),   target);
  return this;
}

f2ptr f2__relationship_meta_semantic_object__new(f2ptr cause, f2ptr realm, f2ptr relationship__source, f2ptr relationship__key_type, f2ptr relationship__key, f2ptr relationship__target) {
  return raw__relationship_meta_semantic_object__new(cause, realm, relationship__source, relationship__key_type, relationship__key, relationship__target);
}
export_cefunk5(relationship_meta_semantic_object__new, realm, source, key_type, key, target, 0, "Returns a new relationship_meta_semantic_object object.");


boolean_t raw__relationship_meta_semantic_object__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "relationship_meta_semantic_object");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__relationship_meta_semantic_object__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__relationship_meta_semantic_object__is_type(cause, thing));
}
export_cefunk1(relationship_meta_semantic_object__is_type, thing, 0, "Returns whether or not thing is of type relationship_meta_semantic_object.");


f2ptr raw__relationship_meta_semantic_object__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__relationship_meta_semantic_object__type(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_object__type(cause, this);
}
export_cefunk1(relationship_meta_semantic_object__type, thing, 0, "Returns the specific type of object that this relationship_meta_semantic_object is.");



f2ptr raw__relationship_meta_semantic_object__source(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "source"), nil);
}

f2ptr f2__relationship_meta_semantic_object__source(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_object__source(cause, this);
}
export_cefunk1(relationship_meta_semantic_object__source, this, 0, "Returns the source for this relationship_meta_semantic_object.");



f2ptr raw__relationship_meta_semantic_object__key_type(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "key_type"), nil);
}

f2ptr f2__relationship_meta_semantic_object__key_type(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_object__key_type(cause, this);
}
export_cefunk1(relationship_meta_semantic_object__key_type, this, 0, "Returns the key_type for this relationship_meta_semantic_object.");



f2ptr raw__relationship_meta_semantic_object__key(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "key"), nil);
}

f2ptr f2__relationship_meta_semantic_object__key(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_object__key(cause, this);
}
export_cefunk1(relationship_meta_semantic_object__key, this, 0, "Returns the key for this relationship_meta_semantic_object.");



f2ptr raw__relationship_meta_semantic_object__target(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "target"), nil);
}

f2ptr f2__relationship_meta_semantic_object__target(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_object__target(cause, this);
}
export_cefunk1(relationship_meta_semantic_object__target, this, 0, "Returns the target for this relationship_meta_semantic_object.");



f2ptr raw__relationship_meta_semantic_object__as__graphviz_color(f2ptr cause, f2ptr this) {
  return new__string(cause, "#00007f");
}

f2ptr f2__relationship_meta_semantic_object__as__graphviz_color(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_object__as__graphviz_color(cause, this);
}
export_cefunk1(relationship_meta_semantic_object__as__graphviz_color, this, 0, "Simply returns the color for rendering this relationship_meta_semantic_object in graphviz.");


f2ptr raw__relationship_meta_semantic_object__label(f2ptr cause, f2ptr this) {
  f2ptr key_type = raw__relationship_meta_semantic_object__key_type(cause, this);
  f2ptr key      = raw__relationship_meta_semantic_object__key(cause, this);
  return f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list3__new(cause, f2__exp__as__string(cause, key_type), new__string(cause, "-"), f2__exp__as__string(cause, key))));
}

f2ptr f2__relationship_meta_semantic_object__label(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_object__label(cause, this);
}
export_cefunk1(relationship_meta_semantic_object__label, this, 0, "Returns a symbolic label for this relationship.");


f2ptr raw__relationship_meta_semantic_object__as__graphviz_label(f2ptr cause, f2ptr this) {
  f2ptr key_type = raw__relationship_meta_semantic_object__key_type(cause, this);
  f2ptr key      = raw__relationship_meta_semantic_object__key(cause, this);
  return f2__stringlist__concat(cause, f2list3__new(cause, f2__exp__as__string(cause, key_type), new__string(cause, "-"), f2__exp__as__string(cause, key)));
}

f2ptr f2__relationship_meta_semantic_object__as__graphviz_label(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_object__as__graphviz_label(cause, this);
}
export_cefunk1(relationship_meta_semantic_object__as__graphviz_label, this, 0, "Simply returns the color for rendering this relationship_meta_semantic_object in graphviz.");


f2ptr raw__relationship_meta_semantic_object__as__graphviz_edge_code(f2ptr cause, f2ptr this) {
  f2ptr edge_label           = raw__relationship_meta_semantic_object__label(cause, this);
  f2ptr semantic_frame       = raw__relationship_meta_semantic_object__source(cause, this);
  f2ptr value                = raw__relationship_meta_semantic_object__target(cause, this);
  f2ptr semantic_frame__name = f2__graphviz__exp__as__name(cause, semantic_frame);
  if (raw__larva__is_type(cause, semantic_frame__name)) {
    return semantic_frame__name;
  }
  f2ptr value__name = f2__graphviz__exp__as__name(cause, value);
  if (raw__larva__is_type(cause, value__name)) {
    return value__name;
  }
  f2ptr this__color = f2__graphviz__exp__as__color(cause, this);
  if (raw__larva__is_type(cause, this__color)) {
    return this__color;
  }
  return f2__graphviz__raw_labelled_edge(cause, edge_label, semantic_frame__name, value__name, this__color);
}

f2ptr f2__relationship_meta_semantic_object__as__graphviz_edge_code(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_object__as__graphviz_edge_code(cause, this);
}
export_cefunk1(relationship_meta_semantic_object__as__graphviz_edge_code, this, 0, "Returns the edge dot code for this relationship.");


f2ptr raw__relationship_meta_semantic_object__as__graphviz_name(f2ptr cause, f2ptr this) {
  f2ptr edge_label           = raw__relationship_meta_semantic_object__label(cause, this);
  f2ptr semantic_frame       = raw__relationship_meta_semantic_object__source(cause, this);
  f2ptr value                = raw__relationship_meta_semantic_object__target(cause, this);
  f2ptr semantic_frame__name = f2__graphviz__exp__as__name(cause, semantic_frame);
  if (raw__larva__is_type(cause, semantic_frame__name)) {
    return semantic_frame__name;
  }
  f2ptr value__name = f2__graphviz__exp__as__name(cause, value);
  if (raw__larva__is_type(cause, value__name)) {
    return value__name;
  }
  return f2__graphviz__edge_name(cause, edge_label, semantic_frame__name, value__name);
}

f2ptr f2__relationship_meta_semantic_object__as__graphviz_name(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_object__as__graphviz_name(cause, this);
}
export_cefunk1(relationship_meta_semantic_object__as__graphviz_name, this, 0, "Returns the edge dot name for this relationship.");


void raw__relationship_meta_semantic_object__add_trans_level_edges_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash) {
  f2ptr this_node = f2__ptypehash__lookup(cause, node_ptypehash, this);
  if (this_node == nil) {
    this_node = f2__graph_node__new(cause, this);
    f2__ptypehash__add(cause, node_ptypehash, this, this_node);
    f2__graph__add_node(cause, graph, this_node);
  }
  {
    f2ptr source      = f2__relationship_meta_semantic_object__source(cause, this);
    f2ptr source_node = nil;
    if (! raw__semantic_frame__is_type(cause, source)) {
      source_node = f2__graph_node__new(cause, source);
      f2__graph__add_node(cause, graph, source_node);
    } else {
      source_node = f2__ptypehash__lookup(cause, node_ptypehash, source);
      if (source_node == nil) {
	source_node = f2__graph_node__new(cause, source);
	f2__ptypehash__add(cause, node_ptypehash, source, source_node);
	f2__graph__add_node(cause, graph, source_node);
      }
    }
    f2__graph__add_new_edge(cause, graph, new__symbol(cause, "source"), this_node, source_node);
  }
  {
    f2ptr key_type          = f2__relationship_meta_semantic_object__key_type(cause, this);
    f2ptr key               = f2__relationship_meta_semantic_object__key(cause, this);
    f2ptr key_type_key_node = nil;
    key_type_key_node = f2__graph_node__new(cause, f2__stringlist__concat(cause, f2list3__new(cause,
											      f2__exp__as__string(cause, key_type),
											      new__string(cause, "-"),
											      f2__exp__as__string(cause, key))));
    f2__graph__add_node(cause, graph, key_type_key_node);
    f2__graph__add_new_edge(cause, graph, new__symbol(cause, "key_type-key"), this_node, key_type_key_node);
  }
  {
    f2ptr target      = f2__relationship_meta_semantic_object__target(cause, this);
    f2ptr target_node = nil;
    if (! raw__semantic_frame__is_type(cause, target)) {
      target_node = f2__graph_node__new(cause, target);
      f2__graph__add_node(cause, graph, target_node);
    } else {
      target_node = f2__ptypehash__lookup(cause, node_ptypehash, target);
      if (target_node == nil) {
	target_node = f2__graph_node__new(cause, target);
	f2__ptypehash__add(cause, node_ptypehash, target, target_node);
	f2__graph__add_node(cause, graph, target_node);
      }
    }
    f2__graph__add_new_edge(cause, graph, new__symbol(cause, "target"), this_node, target_node);
  }
}

f2ptr f2__relationship_meta_semantic_object__add_trans_level_edges_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash) {
  if ((! raw__relationship_meta_semantic_object__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, graph)) ||
      (! raw__ptypehash__is_type(cause, node_ptypehash))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__relationship_meta_semantic_object__add_trans_level_edges_to_graph_with_node_ptypehash(cause, this, graph, node_ptypehash);
  return nil;
}
export_cefunk3(relationship_meta_semantic_object__add_trans_level_edges_to_graph_with_node_ptypehash, this, graph, node_ptypehash, 0, "Adds the trans-level source and target edges to a given graph using the given node_ptypehash.");


f2ptr raw__relationship_meta_semantic_object__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "relationship_meta_semantic_object"),
						new__symbol(cause, "source"),            f2__relationship_meta_semantic_object__source(cause, this),
						new__symbol(cause, "key_type"),          f2__relationship_meta_semantic_object__key_type(cause, this),
						new__symbol(cause, "key"),               f2__relationship_meta_semantic_object__key(cause, this),
						new__symbol(cause, "target"),            f2__relationship_meta_semantic_object__target(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__relationship_meta_semantic_object__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(relationship_meta_semantic_object, this);
  assert_argument_type(terminal_print_frame,              terminal_print_frame);
  return raw__relationship_meta_semantic_object__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(relationship_meta_semantic_object__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__relationship_meta_semantic_object_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "meta_semantic_object")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                                                f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                                            f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                                               f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "source"),                                             f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__source")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_type"),                                           f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__key_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key"),                                                f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "target"),                                             f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__target")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graphviz_color"),                                  f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__as__graphviz_color")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "label"),                                              f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__label")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graphviz_label"),                                  f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__as__graphviz_label")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graphviz_name"),                                   f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__as__graphviz_name")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graphviz_edge_code"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__as__graphviz_edge_code")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_trans_level_edges_to_graph_with_node_ptypehash"), f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__add_trans_level_edges_to_graph_with_node_ptypehash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_object__terminal_print_with_frame")));}
  return this;
}



// **

f2ptr f2__meta_semantic_knowledge_base__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(meta_semantic_knowledge_base__core_extension__ping, 0, "");

f2ptr f2__meta_semantic_knowledge_base__core_extension__initialize(f2ptr cause) {
  f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__core_extension__ping")), nil);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  f2__add_type(cause, new__symbol(cause, "meta_semantic_frame"),               f2__meta_semantic_frame_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "meta_semantic_object"),              f2__meta_semantic_object_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "meta_semantic_knowledge_base"),      f2__meta_semantic_knowledge_base_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "relationship_meta_semantic_object"), f2__relationship_meta_semantic_object_type__new(cause));
  status("meta_semantic_knowledge_base initialized.");
  return nil;
}
export_cefunk0(meta_semantic_knowledge_base__core_extension__initialize, 0, "");

f2ptr f2__meta_semantic_knowledge_base__core_extension__destroy(f2ptr cause) {
  status("meta_semantic_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(meta_semantic_knowledge_base__core_extension__destroy, 0, "");


