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

f2ptr new__symbol(f2ptr cause, char* str) {
  return f2symbol__new(cause, strlen(str), (u8*)(str));
}

//#define def_pcfunk__funkvar(name)            pcfunk__##name
//#define def_pcfunk__prototype__declare(name) f2ptr def_pcfunk__funkvar(name) (f2ptr simple_cause, f2ptr simple_fiber, f2ptr simple_env, f2ptr simple_args)

//#define def_pcfunk__symbolvar(name)          __symbol__##name
//#define def_pcfunk__symbolvar_string(name)   "primfunk:" #name
//#define def_pcfunk__symbolvar__define(name)  f2ptr def_pcfunk__symbolvar(name) = nil
//#define def_pcfunk__symbolvar__init(name)    if(!def_pcfunk__symbolvar(name)) {def_pcfunk__symbolvar(name) = f2symbol__new(initial_cause(), strlen(def_pcfunk__symbolvar_string(name)), (u8*)def_pcfunk__symbolvar_string(name));}
//#define def_pcfunk__this_symbol__define(name) \
//   f2ptr this_symbol = def_pcfunk__symbolvar(name); \
//   this_symbol = this_symbol;

#define raw__frame_object__is_type__funkvar(name) raw__##name##__is_type
#define  f2__frame_object__is_type__funkvar(name)  f2__##name##__is_type
#define  f2__frame_object__type__funkvar(name)     f2__##name##__type
#define  f2__frame_object__new__funkvar(name)      f2__##name##__new

boolean_t raw__physical_object__is_type(f2ptr cause, f2ptr thing) {return raw__eq(cause, new__symbol(cause, "physical_object"), f2__frame__lookup_var_value(cause, new__symbol(cause, "type")));}
f2ptr      f2__physical_object__is_type(f2ptr cause, f2ptr thing) {return f2bool__new(raw__physical_object__is_type(cause, thing));}
f2ptr      f2__physical_object__type(   f2ptr cause, f2ptr this)  {return new__symbol(cause, "physical_object");}
f2ptr      f2__physical_object__new(f2ptr cause) {
  f2ptr this = f2__frame__new(cause);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "position"), nil);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "mass"),     nil);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "velocity"), nil);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "shape"),    nil);
  return this;
}

f2ptr f2physical_object__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("frame"), (u8*)"frame"), nil));
  {char* slot_name = "is_type"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_cons.is_type__funk);}
  {char* slot_name = "type";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cons.type__funk, nil, nil);}
  {char* slot_name = "new";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_cons.new__funk);}
  {char* slot_name = "car";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cons.car__funk, __funk2.globalenv.object_type.primobject.primobject_type_cons.car__set__funk, nil);}
  {char* slot_name = "cdr";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cons.cdr__funk, __funk2.globalenv.object_type.primobject.primobject_type_cons.cdr__set__funk, nil);}
  return this;
}



// **

void f2__frame_objects__reinitialize_globalvars() {
}

void f2__frame_objects__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "frame_objects", "", &f2__frame_objects__reinitialize_globalvars);
  
  f2__frame_objects__reinitialize_globalvars();
  
  
}

