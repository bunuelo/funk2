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

#ifndef F2__FRAME_OBJECTS__H
#define F2__FRAME_OBJECTS__H

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

#define def_frame_object__slot_global_vars__1_slot(name, slot_1) \
  def_frame_object__slot__global_vars(name, slot_1)

#define def_frame_object__slot_global_vars__2_slot(name, slot_1, slot_2) \
  def_frame_object__slot__global_vars(name, slot_1); \
  def_frame_object__slot__global_vars(name, slot_2)

#define def_frame_object__slot_global_vars__3_slot(name, slot_1, slot_2, slot_3) \
  def_frame_object__slot__global_vars(name, slot_1); \
  def_frame_object__slot__global_vars(name, slot_2); \
  def_frame_object__slot__global_vars(name, slot_3)

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
    f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),  new__symbol(cause, #name)); \
    slot_body; \
    return this; \
  } \
  def_pcfunk0(frame_object__funk__pcfunkvar(name, new), return f2__frame_object__funk__funkvar(name, new)(this_cause))

#define def_f2__frame__object__new__1_slot(name, slot_1) \
  def_f2__frame__object__new__slot_body(name, \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), nil))

#define def_f2__frame__object__new__2_slot(name, slot_1, slot_2) \
  def_f2__frame__object__new__slot_body(name, \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), nil); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_2), nil))

#define def_f2__frame__object__new__3_slot(name, slot_1, slot_2, slot_3) \
  def_f2__frame__object__new__slot_body(name, \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), nil); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_2), nil); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_3), nil))

#define def_f2__frame__object__new__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_f2__frame__object__new__slot_body(name, \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), nil); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_2), nil); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_3), nil); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_4), nil))

#define def_frame_object__funk__slot(name, slot_name) \
  f2ptr f2__frame_object__funk__funkvar(name, slot_name)(f2ptr cause, f2ptr this) {return f2__frame__lookup_var_value(cause, this, new__symbol(cause, #slot_name), f2larva__new(cause, 325));} \
  def_pcfunk1(frame_object__funk__pcfunkvar(name, slot_name), this, return f2__frame_object__funk__funkvar(name, slot_name)(this_cause, this)); \
   \
  f2ptr f2__frame_object__funk__funkvar(name, slot_name##__set)(f2ptr cause, f2ptr this, f2ptr value) {return f2__frame__var_value__set(cause, this, new__symbol(cause, #slot_name), value, f2larva__new(cause, 325));} \
  def_pcfunk2(frame_object__funk__pcfunkvar(name, slot_name##__set), this, value, return f2__frame_object__funk__funkvar(name, slot_name##__set)(this_cause, this, value))

#define def_f2frame_object__primobject_type__new__slot_body(name, slot_body) \
  f2ptr f2frame_object__primobject_type__new__funkvar(name)(f2ptr cause) { \
    f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("frame"), (u8*)"frame"), nil)); \
    {char* slot_name = "is_type";  f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, frame_object__slot__funk__var(name, is_type));} \
    {char* slot_name = "type";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), frame_object__slot__funk__var(name, type), nil, nil);} \
    {char* slot_name = "new";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, frame_object__slot__funk__var(name, new));} \
    slot_body; \
    return this; \
  }

#define f2frame_object__primobject_type__new__slot(name, slot_name) \
  {char* slot_name = #slot_name; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), frame_object__slot__funk__var(name, slot_name), frame_object__slot__funk__var(name, slot_name##__set), nil);}

#define def_f2frame_object__primobject_type__new__1_slot(name, slot_1) \
  def_f2frame_object__primobject_type__new__slot_body(name, \
						      f2frame_object__primobject_type__new__slot(name, slot_1))

#define def_f2frame_object__primobject_type__new__2_slot(name, slot_1, slot_2) \
  def_f2frame_object__primobject_type__new__slot_body(name, \
						      f2frame_object__primobject_type__new__slot(name, slot_1); \
						      f2frame_object__primobject_type__new__slot(name, slot_2))

#define def_f2frame_object__primobject_type__new__3_slot(name, slot_1, slot_2, slot_3) \
  def_f2frame_object__primobject_type__new__slot_body(name, \
						      f2frame_object__primobject_type__new__slot(name, slot_1); \
						      f2frame_object__primobject_type__new__slot(name, slot_2); \
						      f2frame_object__primobject_type__new__slot(name, slot_3))

#define def_f2frame_object__primobject_type__new__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_f2frame_object__primobject_type__new__slot_body(name, \
	  					      f2frame_object__primobject_type__new__slot(name, slot_1); \
						      f2frame_object__primobject_type__new__slot(name, slot_2); \
						      f2frame_object__primobject_type__new__slot(name, slot_3); \
						      f2frame_object__primobject_type__new__slot(name, slot_4))

#define def_frame_object__global__sans_slots(name) \
  def_frame_object__shared_global_vars(name); \
   \
  boolean_t raw__frame_object__funk__funkvar(name, is_type)(f2ptr cause, f2ptr thing) {return (raw__frame__is_type(cause, thing) && raw__eq(cause, new__symbol(cause, #name), f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil)));} \
   \
  f2ptr f2__frame_object__funk__funkvar(name, is_type)(f2ptr cause, f2ptr thing) {return f2bool__new(raw__frame_object__funk__funkvar(name, is_type)(cause, thing));} \
  def_pcfunk1(frame_object__funk__pcfunkvar(name, is_type), thing, return f2__frame_object__funk__funkvar(name, is_type)(this_cause, thing)); \
   \
  f2ptr f2__frame_object__funk__funkvar(name, type)(f2ptr cause, f2ptr this) {return new__symbol(cause, #name);} \
  def_pcfunk1(frame_object__funk__pcfunkvar(name, type), this, return f2__frame_object__funk__funkvar(name, type)(this_cause, this))

#define def_frame_object__global__1_slot(name, slot_1) \
  def_frame_object__global__sans_slots(name); \
  def_frame_object__slot_global_vars__1_slot(name, slot_1); \
  def_f2__frame__object__new__1_slot(name, slot_1); \
   \
  def_frame_object__funk__slot(name, slot_1); \
   \
  def_f2frame_object__primobject_type__new__1_slot(name, slot_1)

#define def_frame_object__global__2_slot(name, slot_1, slot_2) \
  def_frame_object__global__sans_slots(name); \
  def_frame_object__slot_global_vars__2_slot(name, slot_1, slot_2); \
  def_f2__frame__object__new__2_slot(name, slot_1, slot_2); \
   \
  def_frame_object__funk__slot(name, slot_1); \
  def_frame_object__funk__slot(name, slot_2); \
   \
  def_f2frame_object__primobject_type__new__2_slot(name, slot_1, slot_2)

#define def_frame_object__global__3_slot(name, slot_1, slot_2, slot_3) \
  def_frame_object__global__sans_slots(name); \
  def_frame_object__slot_global_vars__3_slot(name, slot_1, slot_2, slot_3); \
  def_f2__frame__object__new__3_slot(name, slot_1, slot_2, slot_3); \
   \
  def_frame_object__funk__slot(name, slot_1); \
  def_frame_object__funk__slot(name, slot_2); \
  def_frame_object__funk__slot(name, slot_3); \
   \
  def_f2frame_object__primobject_type__new__3_slot(name, slot_1, slot_2, slot_3)

#define def_frame_object__global__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_frame_object__global__sans_slots(name); \
  def_frame_object__slot_global_vars__4_slot(name, slot_1, slot_2, slot_3, slot_4); \
  def_f2__frame__object__new__4_slot(name, slot_1, slot_2, slot_3, slot_4); \
   \
  def_frame_object__funk__slot(name, slot_1); \
  def_frame_object__funk__slot(name, slot_2); \
  def_frame_object__funk__slot(name, slot_3); \
  def_frame_object__funk__slot(name, slot_4); \
   \
  def_f2frame_object__primobject_type__new__4_slot(name, slot_1, slot_2, slot_3, slot_4)

#define init_frame_object__funk(name, funk_name) \
  {char* symbol_str = #funk_name; frame_object__slot__symbol__var(name, funk_name) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);} \
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(name##__##funk_name, this, cfunk, 0, "frame_object funktion (defined in " __FILE__ ")"); frame_object__slot__funk__var(name, funk_name) = never_gc(cfunk);}

#define init_frame_object__sans_slots(name) \
  init_frame_object__funk(name, is_type); \
  init_frame_object__funk(name, type); \
  init_frame_object__funk(name, new)

#define init_frame_object__slot(name, slot_name) \
  init_frame_object__funk(name, slot_name); \
  init_frame_object__funk(name, slot_name##__set)

#define init_frame_object__1_slot(name, slot_1) \
  init_frame_object__sans_slots(name); \
  init_frame_object__slot(name, slot_1);

#define init_frame_object__2_slot(name, slot_1, slot_2) \
  init_frame_object__sans_slots(name); \
  init_frame_object__slot(name, slot_1); \
  init_frame_object__slot(name, slot_2);

#define init_frame_object__3_slot(name, slot_1, slot_2, slot_3) \
  init_frame_object__sans_slots(name); \
  init_frame_object__slot(name, slot_1); \
  init_frame_object__slot(name, slot_2); \
  init_frame_object__slot(name, slot_3);

#define init_frame_object__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  init_frame_object__sans_slots(name); \
  init_frame_object__slot(name, slot_1); \
  init_frame_object__slot(name, slot_2); \
  init_frame_object__slot(name, slot_3); \
  init_frame_object__slot(name, slot_4);


f2ptr f2physical_object__primobject_type__new(f2ptr cause);
f2ptr f2omega__primobject_type__new(f2ptr cause);

// **

void f2__frame_objects__reinitialize_globalvars();
void f2__frame_objects__initialize();

#endif // F2__FRAME_OBJECTS__H


