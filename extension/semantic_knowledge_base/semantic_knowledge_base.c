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

#include "../../c/funk2.h"


// semantic_frame

f2ptr raw__semantic_frame__new(f2ptr cause, f2ptr semantic_frames) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),            new__symbol(cause, "semantic_frame"),
					    new__symbol(cause, "semantic_frames"), semantic_frames));
}

f2ptr f2__semantic_frame__new(f2ptr cause, f2ptr semantic_frames) {
  if ((semantic_frames != nil) && (! raw__cons__is_type(cause, semantic_frames))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__new(cause, semantic_frames);
}
export_cefunk0_and_rest(semantic_frame__new, user_semantic_frames, 0, "Takes frames and returns a new semantic_frame object.");


boolean_t raw__semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_frame");
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

f2ptr f2__semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_frame__is_type(cause, thing));
}
export_cefunk1(semantic_frame__is_type, thing, 0, "Returns whether or not thing is of type semantic_frame.");


f2ptr raw__semantic_frame__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_frame__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__type(cause, this);
}
export_cefunk1(semantic_frame__type, thing, 0, "Returns the specific type of object that this semantic_frame is.");


f2ptr raw__semantic_frame__semantic_frames(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_frames"), nil);
}

f2ptr f2__semantic_frame__semantic_frames(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__semantic_frames(cause, this);
}
export_cefunk1(semantic_frame__semantic_frames, thing, 0, "Returns the semantic_frames of the semantic_frame.");


f2ptr raw__semantic_frame__semantic_frames__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frames"), value);
}

f2ptr f2__semantic_frame__semantic_frames__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__semantic_frames__set(cause, this, value);
}
export_cefunk2(semantic_frame__semantic_frames__set, thing, value, 0, "Sets the semantic_frames of the semantic_frame.");


f2ptr raw__semantic_frame__as__graph(f2ptr cause, f2ptr this) {
  f2ptr node_ptypehash = f2__ptypehash__new(cause);
  f2ptr graph          = f2__graph__new(cause);
  f2ptr iter = raw__semantic_frame__semantic_frames(cause, this);
  while (iter != nil) {
    f2ptr root_frame = f2__cons__car(cause, iter);
    raw__frame__add_recursively_to_graph_with_ptypehash(cause, root_frame, graph, node_ptypehash);
    iter = f2__cons__cdr(cause, iter);
  }
  return graph;
}

f2ptr f2__semantic_frame__as__graph(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__as__graph(cause, this);
}
export_cefunk1(semantic_frame__as__graph, this, 0, "Converts the semantic_frame to a graph.");


f2ptr f2__semantic_frame_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_frames"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__semantic_frames")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_frames"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__semantic_frames__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graph"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__as__graph")));}
  return this;
}


// semantic_knowledge_base

f2ptr raw__semantic_knowledge_base__new(f2ptr cause, f2ptr semantic_frames) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),            new__symbol(cause, "semantic_knowledge_base"),
					    new__symbol(cause, "semantic_frames"), semantic_frames));
}

f2ptr f2__semantic_knowledge_base__new(f2ptr cause, f2ptr semantic_frames) {
  if ((semantic_frames != nil) && (! raw__cons__is_type(cause, semantic_frames))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__new(cause, semantic_frames);
}
export_cefunk0_and_rest(semantic_knowledge_base__new, user_semantic_frames, 0, "Takes frames and returns a new semantic_knowledge_base object.");


boolean_t raw__semantic_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_knowledge_base");
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

f2ptr f2__semantic_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_knowledge_base__is_type(cause, thing));
}
export_cefunk1(semantic_knowledge_base__is_type, thing, 0, "Returns whether or not thing is of type semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_knowledge_base__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__type(cause, this);
}
export_cefunk1(semantic_knowledge_base__type, thing, 0, "Returns the specific type of object that this semantic_knowledge_base is.");


f2ptr raw__semantic_knowledge_base__semantic_frames(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_frames"), nil);
}

f2ptr f2__semantic_knowledge_base__semantic_frames(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__semantic_frames(cause, this);
}
export_cefunk1(semantic_knowledge_base__semantic_frames, thing, 0, "Returns the semantic_frames of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__semantic_frames__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frames"), value);
}

f2ptr f2__semantic_knowledge_base__semantic_frames__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__semantic_frames__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base__semantic_frames__set, thing, value, 0, "Sets the semantic_frames of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__as__graph(f2ptr cause, f2ptr this) {
  f2ptr node_ptypehash = f2__ptypehash__new(cause);
  f2ptr graph          = f2__graph__new(cause);
  f2ptr iter = raw__semantic_knowledge_base__semantic_frames(cause, this);
  while (iter != nil) {
    f2ptr root_frame = f2__cons__car(cause, iter);
    raw__frame__add_recursively_to_graph_with_ptypehash(cause, root_frame, graph, node_ptypehash);
    iter = f2__cons__cdr(cause, iter);
  }
  return graph;
}

f2ptr f2__semantic_knowledge_base__as__graph(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__as__graph(cause, this);
}
export_cefunk1(semantic_knowledge_base__as__graph, this, 0, "Converts the semantic_knowledge_base to a graph.");


f2ptr f2__semantic_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_frames"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_frames")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_frames"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_frames__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graph"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__as__graph")));}
  return this;
}


// **

f2ptr f2__semantic_knowledge_base__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_ping, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_frame"),          f2__semantic_frame_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base"), f2__semantic_knowledge_base_type__new(cause));
  printf("\nsemantic_knowledge_base initialized."); fflush(stdout);
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_initialize, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension_destroy(f2ptr cause) {
  printf("\nsemantic_knowledge_base destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_destroy, 0, "");


