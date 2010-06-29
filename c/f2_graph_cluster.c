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

f2ptr f2__bruno_graph__cluster(f2ptr cause, f2ptr this) {
  if (! raw__bruno_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return new__string(cause, "this is a test.");
}
def_pcfunk1(bruno_graph__cluster, this, return f2__bruno_graph__cluster(this_cause, this));

// **

void f2__graph_cluster__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "graph_cluster", "", &f2__graph_cluster__reinitialize_globalvars);
  
  //f2ptr cause = initial_cause();
}

void f2__graph_cluster__initialize() {
  f2__graph_cluster__reinitialize_globalvars();
  //f2ptr cause = initial_cause();
  
  f2__primcfunk__init__1(bruno_graph__cluster, this, "Cluster this bruno_graph.");
}

