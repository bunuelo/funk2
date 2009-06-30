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

f2ptr f2__exp__documentation(f2ptr cause, f2ptr exp) {
  if (raw__cfunkp(exp, cause)) {
    return f2cfunk__documentation(exp, cause);
  } else if (raw__metrocfunkp(exp, cause)) {
    return f2metrocfunk__documentation(exp, cause);
  } else if (raw__funkp(exp, cause)) {
    return f2funk__documentation(exp, cause);
  } else if (raw__metrop(exp, cause)) {
    return f2metro__documentation(exp, cause);
  } else {
    return nil;
  }
}

f2ptr f2__environment__apropos(f2ptr cause, f2ptr this, f2ptr find_string) {
  if (! raw__stringp(find_string, cause)) {
    return f2larva__new(cause, 1);
  }
  
  f2ptr frame             = f2environment__frame(this, cause);
  f2ptr funkvar_hashtable = frame__funkvar_hashtable(cause, frame);
  f2ptr bin_array         = f2hashtable__bin_array(funkvar_hashtable, cause);
  s64   length            = raw__array__length(cause, bin_array);
  
  printf("\nenvironment__apropos here.");
  printf("\nlength=" s64__fstr, length);
  printf("\n");
  
  f2ptr match_seq = nil;
  
  s64 index;
  for (index = 0; index < length; index ++) {
    f2ptr bin  = raw__array__elt(cause, bin_array, index);
    
    f2ptr iter = bin;
    while (iter) {
      f2ptr keyvalue_pair = f2cons__car(iter, cause);
      
      f2ptr key           = f2cons__car(keyvalue_pair, cause);
      f2ptr value         = f2cons__cdr(keyvalue_pair, cause);
      f2ptr documentation = f2__exp__documentation(cause, value);
      if (raw__stringp(documentation, cause)) {
      	if (raw__string__contains(cause, documentation, find_string)) {
      	  f2ptr match_pair = f2list2__new(cause, key, documentation);
      	  match_seq        = f2cons__new(cause, match_pair, match_seq);
      	}
      }
      
      iter = f2cons__cdr(iter, cause);
    }
  }
  return match_seq;
}

f2ptr f2__apropos(f2ptr cause, f2ptr find_string) {
  return f2__environment__apropos(cause, global_environment(), find_string);
}
def_pcfunk1(apropos, find_string, return f2__apropos(this_cause, find_string));



// **

void f2__apropos__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_apropos_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__apropos__initialize() {
  //f2ptr cause = initial_cause(); //f2_apropos_c__cause__new(initial_cause(), nil, global_environment());
  pause_gc();
  
  f2__apropos__reinitialize_globalvars();
  
  f2__primcfunk__init(apropos);
  
  resume_gc();
  try_gc();
}

