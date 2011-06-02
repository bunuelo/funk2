// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#include "semantic_event_tree.h"

def_ceframe1(semantic_event_tree, semantic_event_tree, interval_tree);

f2ptr raw__semantic_event_tree__new(f2ptr cause) {
  f2ptr interval_tree = nil;
  return f2semantic_event_tree__new(cause, interval_tree);
}

f2ptr f2__semantic_event_tree__new(f2ptr cause) {
  return raw__semantic_event_tree__new(cause);
}
export_cefunk0(semantic_event_tree__new, 0, "Returns a new semantic_event_tree object.");


f2ptr f2__semantic_event_tree_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_event_tree_type__new(cause);
  return this;
}



// **

f2ptr f2__semantic_event_tree__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_event_tree__core_extension__ping, 0, "");

f2ptr f2__semantic_event_tree__core_extension__initialize(f2ptr cause) {
  status("semantic_event_tree initialized.");
  return nil;
}
export_cefunk0(semantic_event_tree__core_extension__initialize, 0, "");

f2ptr f2__semantic_event_tree__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_event_tree"), f2__semantic_event_tree_type__new_aux(cause));
  status("semantic_event_tree types defined.");
  return nil;
}
export_cefunk0(semantic_event_tree__core_extension__define_types, 0, "");

f2ptr f2__semantic_event_tree__core_extension__destroy(f2ptr cause) {
  status("semantic_event_tree destroyed.");
  return nil;
}
export_cefunk0(semantic_event_tree__core_extension__destroy, 0, "");


