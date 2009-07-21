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
  f2ptr this = frame__new_empty(cause);
  frame__add_type_var_value(cause, this, __frame__variable_type__symbol, f2symbol__new(cause, strlen("type"), (u8*)"type"), f2symbol__new(cause, strlen("primobject_type"), (u8*)"primobject_type"));
  return this;
}
def_pcfunk0(primobject_type__new, return f2__primobject_type__new(this_cause));

f2ptr f2__primobject_type__add_slot(f2ptr cause, f2ptr this, f2ptr name, f2ptr get_funk, f2ptr set_funk, f2ptr execute_funk) {
  if ((! raw__frame__is_type(cause, this)) ||
      (! raw__symbol__is_type(cause, name)) ||
      (get_funk     && (! raw__funkable__is_type(cause, get_funk))) ||
      (set_funk     && (! raw__funkable__is_type(cause, set_funk))) ||
      (execute_funk && (! raw__funkable__is_type(cause, execute_funk)))) {
    return f2larva__new(cause, 1);
  }
  if (get_funk)     {frame__add_type_var_value(cause, this, f2symbol__new(cause, strlen("get_funk"),     (u8*)"get_funk"),     name, get_funk);}
  if (set_funk)     {frame__add_type_var_value(cause, this, f2symbol__new(cause, strlen("set_funk"),     (u8*)"set_funk"),     name, set_funk);}
  if (execute_funk) {frame__add_type_var_value(cause, this, f2symbol__new(cause, strlen("execute_funk"), (u8*)"execute_funk"), name, execute_funk);}
  return nil;
}
def_pcfunk5(primobject_type__add_slot, this, name, get_funk, set_funk, execute_funk, return f2__primobject_type__add_slot(this_cause, this, name, get_funk, set_funk, execute_funk));

// lookup slot type

f2ptr f2__primobject_type__lookup_slot_get_funk(f2ptr cause, f2ptr this, f2ptr slot_name) {
  if ((! raw__frame__is_type(cause, this)) ||
      (! raw__symbol__is_type(cause, slot_name))) {
    return f2larva__new(cause, 1);
  }
  return frame__lookup_type_var_value(cause, this, f2symbol__new(cause, strlen("get_funk"), (u8*)"get_funk"), slot_name, nil);
}
def_pcfunk2(primobject_type__lookup_slot_get_funk, this, slot_name, return f2__primobject_type__lookup_slot_get_funk(this_cause, this, slot_name));

f2ptr f2__primobject_type__lookup_slot_set_funk(f2ptr cause, f2ptr this, f2ptr slot_name) {
  if ((! raw__frame__is_type(cause, this)) ||
      (! raw__symbol__is_type(cause, slot_name))) {
    return f2larva__new(cause, 1);
  }
  return frame__lookup_type_var_value(cause, this, f2symbol__new(cause, strlen("set_funk"), (u8*)"set_funk"), slot_name, nil);
}
def_pcfunk2(primobject_type__lookup_slot_set_funk, this, slot_name, return f2__primobject_type__lookup_slot_set_funk(this_cause, this, slot_name));

f2ptr f2__primobject_type__lookup_slot_execute_funk(f2ptr cause, f2ptr this, f2ptr slot_name) {
  if ((! raw__frame__is_type(cause, this)) ||
      (! raw__symbol__is_type(cause, slot_name))) {
    return f2larva__new(cause, 1);
  }
  return frame__lookup_type_var_value(cause, this, f2symbol__new(cause, strlen("execute_funk"), (u8*)"execute_funk"), slot_name, nil);
}
def_pcfunk2(primobject_type__lookup_slot_execute_funk, this, slot_name, return f2__primobject_type__lookup_slot_execute_funk(this_cause, this, slot_name));


// list slot type

f2ptr f2__primobject_type__get_funk__slot_names(f2ptr cause, f2ptr this) {
  if (! raw__frame__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return frame__type_var__slot_names(cause, this, f2symbol__new(cause, strlen("get_funk"), (u8*)"get_funk"));
}
def_pcfunk1(primobject_type__get_funk__slot_names, this, return f2__primobject_type__get_funk__slot_names(this_cause, this, slot_name));

f2ptr f2__primobject_type__set_funk__slot_names(f2ptr cause, f2ptr this) {
  if (! raw__frame__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return frame__type_var__slot_names(cause, this, f2symbol__new(cause, strlen("set_funk"), (u8*)"set_funk"));
}
def_pcfunk1(primobject_type__set_funk__slot_names, this, return f2__primobject_type__set_funk__slot_names(this_cause, this, slot_name));

f2ptr f2__primobject_type__execute_funk__slot_names(f2ptr cause, f2ptr this) {
  if (! raw__frame__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return frame__type_var__slot_names(cause, this, f2symbol__new(cause, strlen("execute_funk"), (u8*)"execute_funk"));
}
def_pcfunk1(primobject_type__execute_funk__slot_names, this, return f2__primobject_type__execute_funk__slot_names(this_cause, this, slot_name));



void f2__primobject_type__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_string_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__primobject_type__initialize() {
  //f2ptr cause = initial_cause(); //f2_string_c__cause__new(initial_cause(), nil, global_environment());
  pause_gc();
  
  f2__string__reinitialize_globalvars();
  
  f2__primcfunk__init__0(primobject_type__new, "create a new Funk2 object type.");
  f2__primcfunk__init__5(primobject_type__add_slot, this, name, get_funk, set_funk, execute_funk, "adds new get, set, and execute slot funktions to add a new slot for an object type.");
  f2__primcfunk__init__2(primobject_type__lookup_slot_get_funk, this, slot_name, "lookup a primobject_type slot get_funk");
  f2__primcfunk__init__2(primobject_type__lookup_slot_set_funk, this, slot_name, "lookup a primobject_type slot set_funk");
  f2__primcfunk__init__2(primobject_type__lookup_slot_execute_funk, this, slot_name, "lookup a primobject_type slot execute_funk");
  f2__primcfunk__init__1(primobject_type__get_funk__slot_names, this, "get a list of get_funk slot names.");
  f2__primcfunk__init__1(primobject_type__set_funk__slot_names, this, "get a list of set_funk slot names.");
  f2__primcfunk__init__1(primobject_type__execute_funk__slot_names, this, "get a list of execute_funk slot names.");
  
  resume_gc();
  try_gc();
}


