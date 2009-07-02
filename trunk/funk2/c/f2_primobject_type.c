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

f2ptr f2__primobject_type__new(f2ptr cause) {
  return frame__new_empty(cause);
}

void f2__primobject_type__add_slot(f2ptr cause, f2ptr this, f2ptr name, f2ptr get_funk, f2ptr set_funk, f2ptr execute_funk) {
  if (get_funk)     {frame__add_type_var_value(cause, this, f2symbol__new(cause, strlen("get_funk"),     (u8*)"get_funk"),     name, get_funk);}
  if (set_funk)     {frame__add_type_var_value(cause, this, f2symbol__new(cause, strlen("set_funk"),     (u8*)"set_funk"),     name, set_funk);}
  if (execute_funk) {frame__add_type_var_value(cause, this, f2symbol__new(cause, strlen("execute_funk"), (u8*)"execute_funk"), name, execute_funk);}
}

f2ptr f2__primobject_type__lookup_slot_get_funk(f2ptr cause, f2ptr this, f2ptr slot_name) {return frame__lookup_type_var_value(cause, this, f2symbol__new(cause, strlen("get_funk"), (u8*)"get_funk"), slot_name, nil);}
def_pcfunk2(primobject_type__lookup_slot_get_funk, this, slot_name, return f2__primobject_type__lookup_slot_get_funk(this_cause, this, slot_name));

f2ptr f2__primobject_type__lookup_slot_set_funk(f2ptr cause, f2ptr this, f2ptr slot_name) {return frame__lookup_type_var_value(cause, this, f2symbol__new(cause, strlen("set_funk"), (u8*)"set_funk"), slot_name, nil);}
def_pcfunk2(primobject_type__lookup_slot_set_funk, this, slot_name, return f2__primobject_type__lookup_slot_set_funk(this_cause, this, slot_name));

f2ptr f2__primobject_type__lookup_slot_execute_funk(f2ptr cause, f2ptr this, f2ptr slot_name) {return frame__lookup_type_var_value(cause, this, f2symbol__new(cause, strlen("execute_funk"), (u8*)"execute_funk"), slot_name, nil);}
def_pcfunk2(primobject_type__lookup_slot_execute_funk, this, slot_name, return f2__primobject_type__lookup_slot_execute_funk(this_cause, this, slot_name));

void f2__primobject_type__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_string_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__primobject_type__initialize() {
  //f2ptr cause = initial_cause(); //f2_string_c__cause__new(initial_cause(), nil, global_environment());
  pause_gc();
  
  f2__string__reinitialize_globalvars();
  
  f2__primcfunk__init__2(primobject_type__lookup_slot_get_funk, this, slot_name, "lookup a primobject_type slot get_funk");
  f2__primcfunk__init__2(primobject_type__lookup_slot_set_funk, this, slot_name, "lookup a primobject_type slot set_funk");
  f2__primcfunk__init__2(primobject_type__lookup_slot_execute_funk, this, slot_name, "lookup a primobject_type slot execute_funk");
  
  resume_gc();
  try_gc();
}


