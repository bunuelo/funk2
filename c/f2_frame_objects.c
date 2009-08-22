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
//#define def_pcfunk__this_symbol__define(name) 
//   f2ptr this_symbol = def_pcfunk__symbolvar(name); 
//   this_symbol = this_symbol;

#define raw__frame_object__is_type__funkvar(name) raw__##name##__is_type
#define  f2__frame_object__is_type__funkvar(name)  f2__##name##__is_type
#define  f2__frame_object__type__funkvar(name)     f2__##name##__type
#define  f2__frame_object__new__funkvar(name)      f2__##name##__new

f2ptr __frame_object__physical_object__is_type__symbol;
f2ptr __frame_object__physical_object__is_type__funk;
f2ptr __frame_object__physical_object__type__symbol;
f2ptr __frame_object__physical_object__type__funk;
f2ptr __frame_object__physical_object__new__symbol;
f2ptr __frame_object__physical_object__new__funk;
f2ptr __frame_object__physical_object__position__symbol;
f2ptr __frame_object__physical_object__position__funk;
f2ptr __frame_object__physical_object__position__set__symbol;
f2ptr __frame_object__physical_object__position__set__funk;
f2ptr __frame_object__physical_object__velocity__symbol;
f2ptr __frame_object__physical_object__velocity__funk;
f2ptr __frame_object__physical_object__velocity__set__symbol;
f2ptr __frame_object__physical_object__velocity__set__funk;
f2ptr __frame_object__physical_object__mass__symbol;
f2ptr __frame_object__physical_object__mass__funk;
f2ptr __frame_object__physical_object__mass__set__symbol;
f2ptr __frame_object__physical_object__mass__set__funk;
f2ptr __frame_object__physical_object__shape__symbol;
f2ptr __frame_object__physical_object__shape__funk;
f2ptr __frame_object__physical_object__shape__set__symbol;
f2ptr __frame_object__physical_object__shape__set__funk;

boolean_t raw__physical_object__is_type(f2ptr cause, f2ptr thing) {return (raw__frame__is_type(cause, thing) && raw__eq(cause, new__symbol(cause, "physical_object"), f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil)));}

f2ptr f2__physical_object__is_type(f2ptr cause, f2ptr thing) {return f2bool__new(raw__physical_object__is_type(cause, thing));}
def_pcfunk1(physical_object__is_type, thing, return f2__physical_object__is_type(this_cause, thing));

f2ptr f2__physical_object__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "physical_object");}
def_pcfunk1(physical_object__type, this, return f2__physical_object__type(this_cause, this));

f2ptr f2__physical_object__new(f2ptr cause) {
  f2ptr this = f2__frame__new(cause);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "position"), nil);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "mass"),     nil);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "velocity"), nil);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "shape"),    nil);
  return this;
}
def_pcfunk0(physical_object__new, return f2__physical_object__new(this_cause));

f2ptr f2__physical_object__position(f2ptr cause, f2ptr this) {return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "position"), f2larva__new(cause, 325));}
def_pcfunk1(physical_object__position, this, return f2__physical_object__position(this_cause, this));

f2ptr f2__physical_object__position__set(f2ptr cause, f2ptr this, f2ptr value) {return f2__frame__var_value__set(cause, this, new__symbol(cause, "position"), value, f2larva__new(cause, 325));}
def_pcfunk2(physical_object__position__set, this, value, return f2__physical_object__position__set(this_cause, this, value));

f2ptr f2__physical_object__mass(f2ptr cause, f2ptr this) {return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "mass"), f2larva__new(cause, 325));}
def_pcfunk1(physical_object__mass, this, return f2__physical_object__mass(this_cause, this));

f2ptr f2__physical_object__mass__set(f2ptr cause, f2ptr this, f2ptr value) {return f2__frame__var_value__set(cause, this, new__symbol(cause, "mass"), value, f2larva__new(cause, 325));}
def_pcfunk2(physical_object__mass__set, this, value, return f2__physical_object__mass__set(this_cause, this, value));

f2ptr f2__physical_object__velocity(f2ptr cause, f2ptr this) {return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "velocity"), f2larva__new(cause, 325));}
def_pcfunk1(physical_object__velocity, this, return f2__physical_object__velocity(this_cause, this));

f2ptr f2__physical_object__velocity__set(f2ptr cause, f2ptr this, f2ptr value) {return f2__frame__var_value__set(cause, this, new__symbol(cause, "velocity"), value, f2larva__new(cause, 325));}
def_pcfunk2(physical_object__velocity__set, this, value, return f2__physical_object__velocity(this_cause, this, value));

f2ptr f2__physical_object__shape(f2ptr cause, f2ptr this) {return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "shape"), f2larva__new(cause, 325));}
def_pcfunk1(physical_object__shape, this, return f2__physical_object__shape(this_cause, this));

f2ptr f2__physical_object__shape__set(f2ptr cause, f2ptr this, f2ptr value) {return f2__frame__var_value__set(cause, this, new__symbol(cause, "shape"), value, f2larva__new(cause, 325));}
def_pcfunk2(physical_object__shape__set, this, value, return f2__physical_object__shape__set(this_cause, this, value));

f2ptr f2physical_object__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("frame"), (u8*)"frame"), nil));
  {char* slot_name = "is_type";  f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_cons.is_type__funk);}
  {char* slot_name = "type";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cons.type__funk, nil, nil);}
  {char* slot_name = "new";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_cons.new__funk);}
  {char* slot_name = "position"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __frame_object__physical_object__position__funk, __frame_object__physical_object__position__set__funk, nil);}
  {char* slot_name = "mass";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __frame_object__physical_object__mass__funk,     __frame_object__physical_object__mass__set__funk,     nil);}
  {char* slot_name = "velocity"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __frame_object__physical_object__velocity__funk, __frame_object__physical_object__velocity__set__funk, nil);}
  {char* slot_name = "shape";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __frame_object__physical_object__shape__funk,    __frame_object__physical_object__shape__set__funk,    nil);}
  return this;
}



// **

void f2__frame_objects__reinitialize_globalvars() {
}

void f2__frame_objects__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "frame_objects", "", &f2__frame_objects__reinitialize_globalvars);
  
  f2__frame_objects__reinitialize_globalvars();
  
  // physical_object
  
  f2ptr cause = initial_cause();
  
  {char* symbol_str = "is_type"; __frame_object__physical_object__is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "type"; __frame_object__physical_object__type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __frame_object__physical_object__new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(physical_object__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__new__funk = never_gc(cfunk);}
  {char* symbol_str = "position"; __frame_object__physical_object__position__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__position, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__position__funk = never_gc(cfunk);}
  {char* symbol_str = "position-set"; __frame_object__physical_object__position__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(physical_object__position__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__position__set__funk = never_gc(cfunk);}
  {char* symbol_str = "velocity"; __frame_object__physical_object__velocity__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__velocity, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__velocity__funk = never_gc(cfunk);}
  {char* symbol_str = "velocity-set"; __frame_object__physical_object__velocity__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(physical_object__velocity__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__velocity__set__funk = never_gc(cfunk);}
  {char* symbol_str = "mass"; __frame_object__physical_object__mass__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__mass, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__mass__funk = never_gc(cfunk);}
  {char* symbol_str = "mass-set"; __frame_object__physical_object__mass__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(physical_object__mass__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__mass__set__funk = never_gc(cfunk);}
  {char* symbol_str = "shape"; __frame_object__physical_object__shape__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__shape, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__shape__funk = never_gc(cfunk);}
  {char* symbol_str = "shape-set"; __frame_object__physical_object__shape__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(physical_object__shape__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __frame_object__physical_object__shape__set__funk = never_gc(cfunk);}
  
}

