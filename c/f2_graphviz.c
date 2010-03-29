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

f2ptr f2__graphviz__digraph(f2ptr cause, f2ptr codes) {
  return f2__stringlist__rawcode(cause, f2__conslistlist__append(cause,
								 f2cons__new(cause, new__string(cause, "digraph G {"), nil),
								 codes,
								 f2cons__new(cause, new__string(cause, "}"), nil)));
}

// **

void f2__graphviz__reinitialize_globalvars() {
}

void f2__graphviz__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "graphviz", "", &f2__graphviz__reinitialize_globalvars);
  
  f2__graphviz__reinitialize_globalvars();
  
  f2__primcfunk__init__1(graphviz__digraph, codes, "compiles code for graphviz digraph.");
  
}

