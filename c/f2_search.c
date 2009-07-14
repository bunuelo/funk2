// 
// Copyright (c) 2007-2009 Bo Morgan.
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

f2ptr f2__search(f2ptr thread, f2ptr cause, f2ptr start_states, f2ptr expand_funk, f2ptr beam_width, f2ptr heuristic_funk) {
  return nil;
}

def_pcfunk4(search, start_states, expand_funk, beam_width, heuristic_funk, return f2__search(simple_thread, this_cause, start_states, expand_funk, beam_width, heuristic_funk));

// **

void f2__search__reinitialize_globalvars() {

}

void f2__search__initialize() {
  pause_gc();
  
  f2__sort__reinitialize_globalvars();
  
  f2__primcfunk__init__4(search, start_states, expand_funk, beam_width, heuristic_funk, "A-star beam search.");
  
  resume_gc();
  try_gc();
}

