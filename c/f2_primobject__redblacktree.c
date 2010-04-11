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

// redblacktree_node

def_primobject_5_slot(redblacktree_node, parent, left, right, color, key);

f2ptr raw__redblacktree_node__new(f2ptr cause, f2ptr parent, f2ptr left, f2ptr right, f2ptr color, f2ptr key) {
  return f2redblacktree_node__new(cause, parent, left, right, color, key);
}

f2ptr f2__redblacktree_node__new(f2ptr cause, f2ptr parent, f2ptr left, f2ptr right, f2ptr color, f2ptr key) {
  return raw__redblacktree_node__new(cause, parent, left, right, color, key);
}
def_pcfunk5(redblacktree_node__new, parent, left, right, color, key, return f2__redblacktree_node__new(this_cause, parent, left, right, color, key));

// **

void f2__primobject__redblacktree__reinitialize_globalvars() {
  __redblacktree__symbol      = f2symbol__new(initial_cause(), strlen("redblacktree"),      (u8*)"redblacktree");
  __redblacktree_node__symbol = f2symbol__new(initial_cause(), strlen("redblacktree_node"), (u8*)"redblacktree_node");
}

void f2__primobject__redblacktree__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject__redblacktree", "", &f2__primobject__redblacktree__reinitialize_globalvars);
  
  f2__primobject__redblacktree__reinitialize_globalvars();
  
  // redblacktree

  initialize_primobject_1_slot(redblacktree, head);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(redblacktree__new, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.new__funk = never_gc(cfunk);}
  
  // redblacktree_node
  
  initialize_primobject_5_slot(redblacktree_node, parent, left, right, color, key);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(redblacktree_node__new, parent, left, right, color, key, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.new__funk = never_gc(cfunk);}
  
}

