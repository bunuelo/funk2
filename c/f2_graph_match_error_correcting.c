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

f2ptr f2__error_correcting__test(f2ptr cause) {
  return nil;
}
def_pcfunk0(error_correcting__test, return f2__error_correcting__test(this_cause));

// **

void f2__graph_match_error_correcting__reinitialize_globalvars() {
}

void f2__graph_match_error_correcting__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "graph_match_error_correcting", "", &f2__graph_match_error_correcting__reinitialize_globalvars);
  
  f2__graph_match_error_correcting__reinitialize_globalvars();
  
  f2__primcfunk__init__0(error_correcting__test, "Test error correcting graph matching.");
  
}

