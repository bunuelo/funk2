// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

int f2__simple_repl(f2ptr cause, f2ptr fiber) {
  printf("\nfunk2 warning: garbage collection is disabled in this simple_repl.");
  f2ptr repl_funk     = f2funk__new(cause, nil, nil, nil, raw__cons__new(cause, nil, nil), nil, global_environment(), nil, nil, nil, nil);
  f2ptr repl_funk_bcs = f2__compile__funk(cause, fiber, repl_funk);
  while (1) {

    printf ("\nF-In-> "); fflush(stdout);
    f2ptr read_exp = f2__stream__try_read(cause, __funk2.globalenv.stdin_stream);
    
    if (raw__exception__is_type(cause, read_exp)) {
      printf("\nrepl exception: "); f2__write(cause, fiber, read_exp); fflush(stdout);
      break;
    } else {
      repl_funk     = f2funk__new(cause, nil, nil, nil, raw__cons__new(cause, read_exp, nil), read_exp, global_environment(), nil, nil, nil, nil);
      repl_funk_bcs = f2__compile__funk(cause, fiber, repl_funk);
      if(raw__larva__is_type(cause, repl_funk_bcs)) {
	f2__write(cause, fiber, repl_funk_bcs); fflush(stdout);
	return 1;
      }
      
      f2ptr eval_exp = f2__force_funk_apply(cause, fiber, repl_funk, nil);
      printf ("\nF-Out> "); f2__write(cause, fiber, eval_exp); fflush(stdout);
    }
  }
  return 0;
}
def_pcfunk0(simple_repl, 
	    "",
	   return f2integer__new(this_cause, f2__simple_repl(this_cause, simple_fiber)));

// **

void f2__simple_repl__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(simple_repl);
}

void f2__simple_repl__reinitialize_globalvars() {
  f2__primcfunk__init__0(simple_repl);
}

void f2__simple_repl__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "simple_repl", "", &f2__simple_repl__reinitialize_globalvars, &f2__simple_repl__defragment__fix_pointers);
  
  f2__simple_repl__reinitialize_globalvars();
}


