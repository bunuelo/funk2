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
#include "graph_isomorphism.h"


f2ptr raw__error_correcting_graph_isomorphism__new(f2ptr cause, f2ptr width) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),  new__symbol(cause, "error_correcting_graph_isomorphism"),
					    new__symbol(cause, "width"), width));
}

f2ptr f2__error_correcting_graph_isomorphism__new(f2ptr cause, f2ptr width) {
  return raw__error_correcting_graph_isomorphism__new(cause, width);
}
export_cefunk1(error_correcting_graph_isomorphism__new, width, 0, "Returns a new error_correcting_graph_isomorphism object.");


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


f2ptr raw__error_correcting_graph_isomorphism__width(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"), nil);
}

f2ptr f2__error_correcting_graph_isomorphism__width(f2ptr cause, f2ptr this) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__width(cause, this);
}
export_cefunk1(error_correcting_graph_isomorphism__width, thing, 0, "Returns the width of the error_correcting_graph_isomorphism.");


f2ptr raw__error_correcting_graph_isomorphism__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "width"), value);
}

f2ptr f2__error_correcting_graph_isomorphism__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__error_correcting_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__error_correcting_graph_isomorphism__width__set(cause, this, value);
}
export_cefunk2(error_correcting_graph_isomorphism__width__set, thing, value, 0, "Sets the width of the error_correcting_graph_isomorphism.");




f2ptr f2__error_correcting_graph_isomorphism_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "width"),   f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__width")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "width"),   f2__core_extension_funk__new(cause, new__symbol(cause, "graph_isomorphism"), new__symbol(cause, "error_correcting_graph_isomorphism__width__set")));}
  return this;
}






//f2ptr raw__graph__isormorphism(f2ptr cause, f2ptr this, f2ptr that) {
//  f2ptr this__node_set = raw__graph__node_set(cause, this);
//  f2ptr that__node_set = raw__graph__node_set(cause, that);
//  f2ptr this__node_map = 
//}




// **

f2ptr f2__graph_isomorphism__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(graph_isomorphism__core_extension_ping, 0, "");

f2ptr f2__graph_isomorphism__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "error_correcting_graph_isomorphism"), f2__error_correcting_graph_isomorphism_type__new(cause));
  printf("\ngraph_isomorphism initialized."); fflush(stdout);
  return nil;
}
export_cefunk0(graph_isomorphism__core_extension_initialize, 0, "");

f2ptr f2__graph_isomorphism__core_extension_destroy(f2ptr cause) {
  printf("\ngraph_isomorphism destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(graph_isomorphism__core_extension_destroy, 0, "");


