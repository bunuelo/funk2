// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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
#include "graph_isomorphism.h"


f2ptr raw__error_correcting_graph_isomorphism__new(f2ptr cause,
						   f2ptr cost,
						   f2ptr these_nodes_remaining_label_hash,
						   f2ptr those_nodes_remaining_label_hash,
						   f2ptr these_edges_remaining_label_hash,
						   f2ptr those_edges_remaining_label_hash,
						   f2ptr matched_nodes,
						   f2ptr changed_node_labels,
						   f2ptr changed_edge_labels,
						   f2ptr added_nodes,
						   f2ptr added_edges,
						   f2ptr removed_nodes,
						   f2ptr removed_edges) {
  return f2__frame__new(cause, f2list26__new(cause,
					     new__symbol(cause, "type"),                             new__symbol(cause, "error_correcting_graph_isomorphism"),
					     new__symbol(cause, "cost"),                             cost,
					     new__symbol(cause, "these_nodes_remaining_label_hash"), these_nodes_remaining_label_hash,
					     new__symbol(cause, "those_nodes_remaining_label_hash"), those_nodes_remaining_label_hash,
					     new__symbol(cause, "these_edges_remaining_label_hash"), these_edges_remaining_label_hash,
					     new__symbol(cause, "those_edges_remaining_label_hash"), those_edges_remaining_label_hash,
					     new__symbol(cause, "matched_nodes"),                    matched_nodes,
					     new__symbol(cause, "changed_node_labels"),              changed_node_labels,
					     new__symbol(cause, "changed_edge_labels"),              changed_edge_labels,
					     new__symbol(cause, "added_nodes"),                      added_nodes,
					     new__symbol(cause, "added_edges"),                      added_edges,
					     new__symbol(cause, "removed_nodes"),                    removed_nodes,
					     new__symbol(cause, "removed_edges"),                    removed_edges));
}

f2ptr f2__error_correcting_graph_isomorphism__new(f2ptr cause,
						  f2ptr cost,
						  f2ptr these_nodes_remaining_label_hash,
						  f2ptr those_nodes_remaining_label_hash,
						  f2ptr these_edges_remaining_label_hash,
						  f2ptr those_edges_remaining_label_hash,
						  f2ptr matched_nodes,
						  f2ptr changed_node_labels,
						  f2ptr changed_edge_labels,
						  f2ptr added_nodes,
						  f2ptr added_edges,
						  f2ptr removed_nodes,
						  f2ptr removed_edges) {
  return raw__error_correcting_graph_isomorphism__new(cause,
						      cost,
						      these_nodes_remaining_label_hash,
						      those_nodes_remaining_label_hash,
						      these_edges_remaining_label_hash,
						      those_edges_remaining_label_hash,
						      matched_nodes,
						      changed_node_labels,
						      changed_edge_labels,
						      added_nodes,
						      added_edges,
						      removed_nodes,
						      removed_edges);
}
export_cefunk12(error_correcting_graph_isomorphism__new,
		cost,
		these_nodes_remaining_label_hash,
		those_nodes_remaining_label_hash,
		these_edges_remaining_label_hash,
		those_edges_remaining_label_hash,
		matched_nodes,
		changed_node_labels,
		changed_edge_labels,
		added_nodes,
		added_edges,
		removed_nodes,
		removed_edges, 0, "Returns a new error_correcting_graph_isomorphism object.");


boolean_t raw__error_correcting_graph_isomorphism__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "error_correcting_graph_isomorphism");
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

f2ptr f2__error_correcting_graph_isomorphism__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__error_correcting_graph_isomorphism__is_type(cause, thing));
}
export_cefunk1(error_correcting_graph_isomorphism__is_type, thing, 0, "Returns whether or not thing is of type error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__error_correcting_graph_isomorphism__type(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__type(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__type, thing, 0, "Returns the specific type of object that this error_correcting_graph_isomorphism is.");


f2ptr raw__error_correcting_graph_isomorphism__cost(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "cost"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__cost(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__cost(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__cost, thing, 0, "Returns the cost of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__cost__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "cost"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__cost__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__cost__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__cost__set, thing, value, 0, "Sets the cost of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__these_nodes_remaining_label_hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "these_nodes_remaining_label_hash"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__these_nodes_remaining_label_hash(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__these_nodes_remaining_label_hash(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__these_nodes_remaining_label_hash, thing, 0, "Returns the these_nodes_remaining_label_hash of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__these_nodes_remaining_label_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "these_nodes_remaining_label_hash"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__these_nodes_remaining_label_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__these_nodes_remaining_label_hash__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__these_nodes_remaining_label_hash__set, thing, value, 0, "Sets the these_nodes_remaining_label_hash of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__those_nodes_remaining_label_hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "those_nodes_remaining_label_hash"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__those_nodes_remaining_label_hash(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__those_nodes_remaining_label_hash(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__those_nodes_remaining_label_hash, thing, 0, "Returns the those_nodes_remaining_label_hash of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__those_nodes_remaining_label_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "those_nodes_remaining_label_hash"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__those_nodes_remaining_label_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__those_nodes_remaining_label_hash__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__those_nodes_remaining_label_hash__set, thing, value, 0, "Sets the those_nodes_remaining_label_hash of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__these_edges_remaining_label_hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "these_edges_remaining_label_hash"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__these_edges_remaining_label_hash(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__these_edges_remaining_label_hash(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__these_edges_remaining_label_hash, thing, 0, "Returns the these_edges_remaining_label_hash of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__these_edges_remaining_label_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "these_edges_remaining_label_hash"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__these_edges_remaining_label_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__these_edges_remaining_label_hash__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__these_edges_remaining_label_hash__set, thing, value, 0, "Sets the these_edges_remaining_label_hash of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__those_edges_remaining_label_hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "those_edges_remaining_label_hash"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__those_edges_remaining_label_hash(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__those_edges_remaining_label_hash(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__those_edges_remaining_label_hash, thing, 0, "Returns the those_edges_remaining_label_hash of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__those_edges_remaining_label_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "those_edges_remaining_label_hash"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__those_edges_remaining_label_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__those_edges_remaining_label_hash__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__those_edges_remaining_label_hash__set, thing, value, 0, "Sets the those_edges_remaining_label_hash of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__matched_nodes(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "matched_nodes"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__matched_nodes(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__matched_nodes(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__matched_nodes, thing, 0, "Returns the matched_nodes of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__matched_nodes__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "matched_nodes"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__matched_nodes__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__matched_nodes__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__matched_nodes__set, thing, value, 0, "Sets the matched_nodes of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__changed_node_labels(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "changed_node_labels"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__changed_node_labels(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__changed_node_labels(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__changed_node_labels, thing, 0, "Returns the changed_node_labels of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__changed_node_labels__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "changed_node_labels"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__changed_node_labels__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__changed_node_labels__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__changed_node_labels__set, thing, value, 0, "Sets the changed_node_labels of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__changed_edge_labels(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "changed_edge_labels"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__changed_edge_labels(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__changed_edge_labels(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__changed_edge_labels, thing, 0, "Returns the changed_edge_labels of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__changed_edge_labels__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "changed_edge_labels"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__changed_edge_labels__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__changed_edge_labels__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__changed_edge_labels__set, thing, value, 0, "Sets the changed_edge_labels of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__added_nodes(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "added_nodes"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__added_nodes(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__added_nodes(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__added_nodes, thing, 0, "Returns the added_nodes of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__added_nodes__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "added_nodes"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__added_nodes__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__added_nodes__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__added_nodes__set, thing, value, 0, "Sets the added_nodes of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__added_edges(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "added_edges"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__added_edges(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__added_edges(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__added_edges, thing, 0, "Returns the added_edges of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__added_edges__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "added_edges"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__added_edges__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__added_edges__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__added_edges__set, thing, value, 0, "Sets the added_edges of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__removed_nodes(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "removed_nodes"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__removed_nodes(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__removed_nodes(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__removed_nodes, thing, 0, "Returns the removed_nodes of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__removed_nodes__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "removed_nodes"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__removed_nodes__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__removed_nodes__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__removed_nodes__set, thing, value, 0, "Sets the removed_nodes of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__removed_edges(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "removed_edges"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__removed_edges(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__removed_edges(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__removed_edges, thing, 0, "Returns the removed_edges of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__removed_edges__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "removed_edges"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__removed_edges__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__removed_edges__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__removed_edges__set, thing, value, 0, "Sets the removed_edges of the error_correcting_graph_isomorphism.");



f2ptr f2__error_correcting_graph_isomorphism_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "cost"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__cost")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "cost"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__cost__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "these_nodes_remaining_label_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__these_nodes_remaining_label_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "these_nodes_remaining_label_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__these_nodes_remaining_label_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "those_nodes_remaining_label_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__those_nodes_remaining_label_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "those_nodes_remaining_label_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__those_nodes_remaining_label_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "these_edges_remaining_label_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__these_edges_remaining_label_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "these_edges_remaining_label_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__these_edges_remaining_label_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "those_edges_remaining_label_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__those_edges_remaining_label_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "those_edges_remaining_label_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__those_edges_remaining_label_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "matched_nodes"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__matched_nodes")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "matched_nodes"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__matched_nodes__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "changed_node_labels"),              f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__changed_node_labels")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "changed_node_labels"),              f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__changed_node_labels__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "changed_edge_labels"),              f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__changed_edge_labels")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "changed_edge_labels"),              f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__changed_edge_labels__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "added_nodes"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__added_nodes")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "added_nodes"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__added_nodes__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "added_edges"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__added_edges")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "added_edges"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__added_edges__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "removed_nodes"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__removed_nodes")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "removed_nodes"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__removed_nodes__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "removed_edges"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__removed_edges")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "removed_edges"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__removed_edges__set")));}
  return this;
}


f2ptr raw__graph_isomorphism__isomorphism__cost(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr isomorphism = f2__cons__car(cause, args_iter); args_iter = f2__cons__cdr(cause, args_iter);
  return raw__error_correcting_graph_isomorphism__cost(cause, isomorphism);
}

f2ptr raw__graph_isomorphism__isomorphism__cost_compare(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr isomorphism_1__cost = f2__cons__car(cause, args_iter); args_iter = f2__cons__cdr(cause, args_iter);
  f2ptr isomorphism_2__cost = f2__cons__car(cause, args_iter);
  s64   isomorphism_1__cost__i = f2integer__i(isomorphism_1__cost, cause);
  s64   isomorphism_2__cost__i = f2integer__i(isomorphism_2__cost, cause);
  return f2bool__new(isomorphism_1__cost__i < isomorphism_2__cost__i);
}

f2ptr raw__graph__isomorphism(f2ptr cause, f2ptr this, f2ptr that, s64 beam_width) {
  f2ptr this__node_set           = f2__graph__node_set(cause, this);
  f2ptr that__node_set           = f2__graph__node_set(cause, that);
  f2ptr this__edge_set           = f2__graph__edge_set(cause, this);
  f2ptr that__edge_set           = f2__graph__edge_set(cause, that);
  f2ptr value_cfunk              = f2cfunk__new(cause, nil, 
						f2list1__new(cause, new__symbol(cause, "x")),
						nil,
						f2pointer__new(cause, raw_executable__to__relative_ptr(raw__graph_isomorphism__isomorphism__cost)), global_environment(), nil, nil);
  f2ptr value_compare_cfunk      = f2cfunk__new(cause, nil, 
						f2list2__new(cause, new__symbol(cause, "x"), new__symbol(cause, "y")),
						nil,
						f2pointer__new(cause, raw_executable__to__relative_ptr(raw__graph_isomorphism__isomorphism__cost_compare)), global_environment(), nil, nil);
  f2ptr search_beam_redblacktree = f2__redblacktree__new(cause, value_cfunk, value_compare_cfunk);
  
  f2ptr initial_isomorphism;
  {
    f2ptr cost = f2integer__new(cause, 0);
    f2ptr these_nodes_remaining_label_hash = f2__ptypehash__new(cause);
    set__iteration(cause, this__node_set, node,
		   f2ptr node__label = f2__graph_node__label(cause, node);
		   raw__ptypehash__add(cause, these_nodes_remaining_label_hash, node__label, node));
    f2ptr those_nodes_remaining_label_hash = f2__ptypehash__new(cause);
    set__iteration(cause, that__node_set, node,
		   f2ptr node__label = f2__graph_node__label(cause, node);
		   raw__ptypehash__add(cause, those_nodes_remaining_label_hash, node__label, node));
    f2ptr these_edges_remaining_label_hash = f2__ptypehash__new(cause);
    set__iteration(cause, this__edge_set, edge,
		   f2ptr edge__label = f2__graph_edge__label(cause, edge);
		   raw__ptypehash__add(cause, these_edges_remaining_label_hash, edge__label, edge));
    f2ptr those_edges_remaining_label_hash = f2__ptypehash__new(cause);
    set__iteration(cause, that__edge_set, edge,
		   f2ptr edge__label = f2__graph_edge__label(cause, edge);
		   raw__ptypehash__add(cause, those_edges_remaining_label_hash, edge__label, edge));
    f2ptr matched_nodes       = nil;
    f2ptr changed_node_labels = nil;
    f2ptr changed_edge_labels = nil;
    f2ptr added_nodes         = nil;
    f2ptr added_edges         = nil;
    f2ptr removed_nodes       = nil;
    f2ptr removed_edges       = nil;
    initial_isomorphism = raw__error_correcting_graph_isomorphism__new(cause,
								       cost,
								       these_nodes_remaining_label_hash,
								       those_nodes_remaining_label_hash,
								       these_edges_remaining_label_hash,
								       those_edges_remaining_label_hash,
								       matched_nodes,
								       changed_node_labels,
								       changed_edge_labels,
								       added_nodes,
								       added_edges,
								       removed_nodes,
								       removed_edges);
  }
  raw__redblacktree__insert(cause, search_beam_redblacktree, initial_isomorphism);
  f2ptr best_complete_isomorphism = nil;
  while (! raw__redblacktree__is_empty(cause, search_beam_redblacktree)) {
    f2ptr expansion_redblacktree = f2__redblacktree__new(cause, value_cfunk, value_compare_cfunk);
    {
      s64 beam_index = 0;
      while ((beam_index < beam_width) &&
	     (! raw__redblacktree__is_empty(cause, search_beam_redblacktree))) {
	f2ptr minimum_cost_isomorphism = raw__redblacktree__minimum(cause, search_beam_redblacktree);
	raw__redblacktree__remove(cause, search_beam_redblacktree, minimum_cost_isomorphism);
	{
	  // expand minimum_cost_isomorphism
	  {
	    // expand minimum_cost_isomorphism by finding a node with a matching label and matching edges
	  }
	  // check for complete isomorphisms and update best_complete_isomorphism
	}
	beam_index ++;
      }
    }
    search_beam_redblacktree = expansion_redblacktree;
  }
  return best_complete_isomorphism;
}

f2ptr f2__graph__isomorphism(f2ptr cause, f2ptr this, f2ptr that, f2ptr beam_width) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, that)) ||
      (! raw__integer__is_type(cause, beam_width))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__isomorphism(cause, this, that, beam_width);
}
export_cefunk3(graph__isomorphism, this, that, beam_width, 0, "A* breadth-first beam search for an error correcting isomorphism between this and that graph.");



// **

f2ptr f2__graph_isomorphism__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(graph_isomorphism__core_extension__ping, 0, "");

f2ptr f2__graph_isomorphism__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "error_correcting_graph_isomorphism"), f2__error_correcting_graph_isomorphism_type__new(cause));
  printf("\ngraph_isomorphism initialized."); fflush(stdout);
  return nil;
}
export_cefunk0(graph_isomorphism__core_extension__initialize, 0, "");

f2ptr f2__graph_isomorphism__core_extension__destroy(f2ptr cause) {
  printf("\ngraph_isomorphism destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(graph_isomorphism__core_extension__destroy, 0, "");


