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

f2ptr f2__search_node__new(f2ptr cause, f2ptr state, f2ptr heuristic_value) {
  f2ptr this = raw__array__new(cause, 2);
  raw__array__elt__set(cause, this, 0, state);
  raw__array__elt__set(cause, this, 1, heuristic_value);
  return this;
}

f2ptr f2__search_node__state(          f2ptr cause, f2ptr this) {return raw__array__elt(cause, this, 0);}
f2ptr f2__search_node__heuristic_value(f2ptr cause, f2ptr this) {return raw__array__elt(cause, this, 1);}


f2ptr f2__search(f2ptr fiber, f2ptr cause, f2ptr start_states, f2ptr expand_funk, f2ptr beam_width, f2ptr heuristic_funk) {
  assert_argument_type(conslist, start_states);
  assert_argument_type(funkable, expand_funk);
  assert_argument_type(integer,  beam_width);
  assert_argument_type(funkable, heuristic_funk);
  s64   search_nodes__count = 0;
  f2ptr search_nodes        = nil;
  {
    f2ptr iter = start_states;
    while (iter) {
      f2ptr start_state     = f2cons__car(iter, cause);
      // not done.
      //f2ptr heuristic_value = ;
      f2__force_funk_apply(cause, fiber, heuristic_funk, f2list1__new(cause, start_state));
      f2ptr search_node     = f2__search_node__new(cause, start_state, nil);
      search_nodes = f2cons__new(cause, search_node, search_nodes);
      search_nodes__count ++;
      iter = f2cons__cdr(iter, cause);
    }
  }
  f2ptr sort_array = raw__array__new(cause, search_nodes__count);
  {
    f2ptr iter = search_nodes;
    s64 index;
    for (index = 0; index < search_nodes__count; index ++) {
      f2ptr search_node = f2cons__car(iter, cause);
      raw__array__elt__set(cause, sort_array, index, search_node);
      iter = f2cons__cdr(iter, cause);
    }
  }
  return nil;
}

def_pcfunk4(search, start_states, expand_funk, beam_width, heuristic_funk, return f2__search(simple_fiber, this_cause, start_states, expand_funk, beam_width, heuristic_funk));

// **

void f2__search__reinitialize_globalvars() {

}

void f2__search__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "search", "", &f2__search__reinitialize_globalvars);
  
  f2__sort__reinitialize_globalvars();
  
  f2__primcfunk__init__4(search, start_states, expand_funk, beam_width, heuristic_funk, "A-star beam search.");
}

