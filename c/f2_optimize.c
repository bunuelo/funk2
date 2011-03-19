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

#include "funk2.h"

f2ptr raw__argument_data_node__new(f2ptr cause, f2ptr name) {
  f2ptr argument_data = raw__array__new(cause, 2);
  raw__array__elt__set(cause, argument_data, 0, new__symbol(cause, "argument_data"));
  raw__array__elt__set(cause, argument_data, 1, name);
  return f2__graph_node__new(cause, argument_data);
}

boolean_t raw__argument_data_node__is_type(f2ptr cause, f2ptr object) {
  if (! raw__graph_node__is_type(cause, object)) {
    return boolean__false;
  }
  f2ptr data = raw__graph_node__label(cause, object);
  return ((data != nil) &&
	  raw__array__is_type(cause, data) &&
	  (raw__array__length(cause, data) == 2) &&
	  raw__eq(cause, raw__array__elt(cause, data, 0), new__symbol(cause, "argument_data")));
}

f2ptr raw__argument_data_node__name(f2ptr cause, f2ptr this) {
  return raw__array__elt(cause, raw__graph_node__label(cause, this), 1);
}

f2ptr raw__funk__optimize(f2ptr cause, f2ptr this) {
  f2ptr args               = f2__funk__args(          cause, this);
  f2ptr body_bytecodes     = f2__funk__body_bytecodes(cause, this);
  f2ptr graph              = f2__graph__new(cause);
  f2ptr node_argument_hash = f2__ptypehash__new(cause);
  {
    f2ptr iter = args;
    while (iter != nil) {
      f2ptr argument = f2__cons__car(cause, iter);
      {
	f2ptr argument_data_node = f2__argument_data_node__new(cause, argument);
	raw__graph__add_node(cause, graph, argument_data_node);
	raw__ptypehash__add(cause, node_argument_hash, argument, argument_data_node);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  {
    f2ptr iter = body_bytecodes;
    while (iter != nil) {
      f2ptr bytecode = f2__cons__car(cause, iter);
      {
	
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return graph;
}

f2ptr f2__funk__optimize(f2ptr cause, f2ptr this) {
  assert_argument_type(funk, this);
  return raw__funk__optimize(cause, this);
}


// **

void f2__optimize__reinitialize_globalvars() {
}

void f2__optimize__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "optimize", "", &f2__optimize__reinitialize_globalvars);
  
  f2__optimize__reinitialize_globalvars();
  
}

