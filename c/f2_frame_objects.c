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

#define frame_object__slot__symbol__var(name, slot_name) __frame_object__##name##__##slot_name##__symbol
#define frame_object__slot__funk__var(name, slot_name)   __frame_object__##name##__##slot_name##__funk

#define def_frame_object__symbol_funk__global_vars(name, funk_name) \
  f2ptr frame_object__slot__symbol__var(name, funk_name); \
  f2ptr frame_object__slot__funk__var(name, funk_name)

#define def_frame_object__slot__global_vars(name, slot_name) \
  def_frame_object__symbol_funk__global_vars(name, slot_name); \
  def_frame_object__symbol_funk__global_vars(name, slot_name##__set);

#define def_frame_object__shared_global_vars(name) \
  def_frame_object__symbol_funk__global_vars(name, is_type); \
  def_frame_object__symbol_funk__global_vars(name, type); \
  def_frame_object__symbol_funk__global_vars(name, new)

#define def_frame_object__slot_global_vars__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_frame_object__slot__global_vars(name, slot_1); \
  def_frame_object__slot__global_vars(name, slot_2); \
  def_frame_object__slot__global_vars(name, slot_3); \
  def_frame_object__slot__global_vars(name, slot_4)


#define      frame_object__funk__pcfunkvar(name, funk_name)        name##__##funk_name
#define raw__frame_object__funk__funkvar(name, funk_name)   raw__##name##__##funk_name
#define  f2__frame_object__funk__funkvar(name, funk_name)    f2__##name##__##funk_name

#define f2frame_object__primobject_type__new__funkvar(name) f2##name##__primobject_type__new

#define def_f2__frame__object__new__slot_body(name, slot_body) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause) { \
    f2ptr this = f2__frame__new(cause); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),  new__symbol(cause, "physical_object")); \
    slot_body; \
    return this; \
  } \
  def_pcfunk0(frame_object__funk__pcfunkvar(physical_object, new), return f2__frame_object__funk__funkvar(name, new)(this_cause))

#define def_f2__frame__object__new__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_f2__frame__object__new__slot_body(name, \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), nil); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_2), nil); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_3), nil); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_4), nil))

def_frame_object__shared_global_vars(physical_object);
def_frame_object__slot_global_vars__4_slot(physical_object, position, velocity, mass, shape);

boolean_t raw__frame_object__funk__funkvar(physical_object, is_type)(f2ptr cause, f2ptr thing) {return (raw__frame__is_type(cause, thing) && raw__eq(cause, new__symbol(cause, "physical_object"), f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil)));}

f2ptr f2__frame_object__funk__funkvar(physical_object, is_type)(f2ptr cause, f2ptr thing) {return f2bool__new(raw__frame_object__funk__funkvar(physical_object, is_type)(cause, thing));}
def_pcfunk1(frame_object__funk__pcfunkvar(physical_object, is_type), thing, return f2__frame_object__funk__funkvar(physical_object, is_type)(this_cause, thing));

f2ptr f2__frame_object__funk__funkvar(physical_object, type)(f2ptr cause, f2ptr this) {return new__symbol(cause, "physical_object");}
def_pcfunk1(frame_object__funk__pcfunkvar(physical_object, type), this, return f2__frame_object__funk__funkvar(physical_object, type)(this_cause, this));

def_f2__frame__object__new__4_slot(physical_object, position, mass, velocity, shape);

#define def_frame_object__funk__slot(name, slot_name) \
  f2ptr f2__frame_object__funk__funkvar(name, slot_name)(f2ptr cause, f2ptr this) {return f2__frame__lookup_var_value(cause, this, new__symbol(cause, #slot_name), f2larva__new(cause, 325));} \
  def_pcfunk1(frame_object__funk__pcfunkvar(physical_object, slot_name), this, return f2__frame_object__funk__funkvar(name, slot_name)(this_cause, this)); \
   \
  f2ptr f2__frame_object__funk__funkvar(name, slot_name##__set)(f2ptr cause, f2ptr this, f2ptr value) {return f2__frame__var_value__set(cause, this, new__symbol(cause, #slot_name), value, f2larva__new(cause, 325));} \
  def_pcfunk2(frame_object__funk__pcfunkvar(name, slot_name##__set), this, value, return f2__frame_object__funk__funkvar(name, slot_name##__set)(this_cause, this, value))

def_frame_object__funk__slot(physical_object, position);
def_frame_object__funk__slot(physical_object, mass);
def_frame_object__funk__slot(physical_object, velocity);
def_frame_object__funk__slot(physical_object, shape);

f2ptr f2frame_object__primobject_type__new__funkvar(physical_object)(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("frame"), (u8*)"frame"), nil));
  {char* slot_name = "is_type";  f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, frame_object__slot__funk__var(physical_object, is_type));}
  {char* slot_name = "type";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), frame_object__slot__funk__var(physical_object, type), nil, nil);}
  {char* slot_name = "new";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, frame_object__slot__funk__var(physical_object, new));}
  {char* slot_name = "position"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), frame_object__slot__funk__var(physical_object, position), frame_object__slot__funk__var(physical_object, position__set), nil);}
  {char* slot_name = "mass";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), frame_object__slot__funk__var(physical_object, mass),     frame_object__slot__funk__var(physical_object, mass__set),     nil);}
  {char* slot_name = "velocity"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), frame_object__slot__funk__var(physical_object, velocity), frame_object__slot__funk__var(physical_object, velocity__set), nil);}
  {char* slot_name = "shape";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), frame_object__slot__funk__var(physical_object, shape),    frame_object__slot__funk__var(physical_object, shape__set),    nil);}
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
  
  {char* symbol_str = "is_type"; frame_object__slot__symbol__var(physical_object, is_type) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, is_type) = never_gc(cfunk);}
  {char* symbol_str = "type"; frame_object__slot__symbol__var(physical_object, type) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, type) = never_gc(cfunk);}
  {char* symbol_str = "new"; frame_object__slot__symbol__var(physical_object, new) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(physical_object__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, new) = never_gc(cfunk);}
  {char* symbol_str = "position"; frame_object__slot__symbol__var(physical_object, position) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__position, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, position) = never_gc(cfunk);}
  {char* symbol_str = "position-set"; frame_object__slot__symbol__var(physical_object, position__set) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(physical_object__position__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, position__set) = never_gc(cfunk);}
  {char* symbol_str = "velocity"; frame_object__slot__symbol__var(physical_object, velocity) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__velocity, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, velocity) = never_gc(cfunk);}
  {char* symbol_str = "velocity-set"; frame_object__slot__symbol__var(physical_object, velocity__set) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(physical_object__velocity__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, velocity__set) = never_gc(cfunk);}
  {char* symbol_str = "mass"; frame_object__slot__symbol__var(physical_object, mass) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__mass, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, mass) = never_gc(cfunk);}
  {char* symbol_str = "mass-set"; frame_object__slot__symbol__var(physical_object, mass__set) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(physical_object__mass__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, mass__set) = never_gc(cfunk);}
  {char* symbol_str = "shape"; frame_object__slot__symbol__var(physical_object, shape) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(physical_object__shape, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, shape) = never_gc(cfunk);}
  {char* symbol_str = "shape-set"; frame_object__slot__symbol__var(physical_object, shape__set) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(physical_object__shape__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); frame_object__slot__funk__var(physical_object, shape__set) = never_gc(cfunk);}

}

