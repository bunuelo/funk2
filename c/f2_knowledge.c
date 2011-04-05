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


// knowledge

def_frame_object__global__1_slot(knowledge, object);

f2ptr f2__knowledge__new(f2ptr cause, f2ptr object) {
  return f2knowledge__new(cause, object);
}
def_pcfunk1(knowledge__new, object, return f2__knowledge__new(this_cause, object));


f2ptr f2knowledge__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2knowledge__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_knowledge.new__funk);}
  return this;
}


// **

void f2__knowledge__reinitialize_globalvars() {
}

void f2__knowledge__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "knowledge", "", &f2__knowledge__reinitialize_globalvars);
  
  f2__knowledge__reinitialize_globalvars();
  
  
  // knowledge
  
  init_frame_object__1_slot(knowledge, object);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_knowledge.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(knowledge__new, object, cfunk, ""); __funk2.globalenv.object_type.primobject.primobject_type_knowledge.new__funk = never_gc(cfunk);}
  
}

