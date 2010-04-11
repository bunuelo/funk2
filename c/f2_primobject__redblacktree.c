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

// redblacktree

def_primobject_1_slot(redblacktree, head);

f2ptr raw__redblacktree__new(f2ptr cause, f2ptr head) {
  return f2redblacktree__new(cause, head);
}

f2ptr f2__redblacktree__new(f2ptr cause) {
  return raw__redblacktree__new(cause, nil);
}
def_pcfunk0(redblacktree__new, return f2__redblacktree__new(this_cause));

// **

void f2__primobject__redblacktree__reinitialize_globalvars() {
  __redblacktree__symbol = f2symbol__new(initial_cause(), strlen("redblacktree"), (u8*)"redblacktree");
}

void f2__primobject__redblacktree__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject__redblacktree", "", &f2__primobject__redblacktree__reinitialize_globalvars);
  
  f2__primobject__redblacktree__reinitialize_globalvars();
  
  initialize_primobject_1_slot(redblacktree, head);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(redblacktree__new, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.new__funk = never_gc(cfunk);}
  
}

