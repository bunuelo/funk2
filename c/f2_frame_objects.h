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

#define def_frame_object__slot_global_vars__0_slot(name)

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

#define def_frame_object__slot_global_vars__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_frame_object__slot__global_vars(name, slot_1); \
  def_frame_object__slot__global_vars(name, slot_2); \
  def_frame_object__slot__global_vars(name, slot_3); \
  def_frame_object__slot__global_vars(name, slot_4); \
  def_frame_object__slot__global_vars(name, slot_5)


#define      frame_object__funk__pcfunkvar(name, funk_name)        name##__##funk_name
#define raw__frame_object__funk__funkvar(name, funk_name)   raw__##name##__##funk_name
#define  f2__frame_object__funk__funkvar(name, funk_name)    f2__##name##__##funk_name

#define f2frame_object__primobject_type__new__funkvar(name) f2##name##__primobject_type__new

#define declare_frame_object_0_slot__sans_new(name) \
  f2ptr f2frame_object__primobject_type__new__funkvar(name)(f2ptr cause); \
  boolean_t raw__frame_object__funk__funkvar(name, is_type)(f2ptr cause, f2ptr thing); \
  f2ptr      f2__frame_object__funk__funkvar(name, is_type)(f2ptr cause, f2ptr thing); \
  f2ptr      f2__frame_object__funk__funkvar(name, type)   (f2ptr cause, f2ptr this)

#define declare_frame_object_1_slot__sans_new(name, slot_1) \
  declare_frame_object_0_slot__sans_new(name); \
  f2ptr f2__frame_object__funk__funkvar(name, slot_1)(f2ptr cause, f2ptr this)
  
#define declare_frame_object_2_slot__sans_new(name, slot_1, slot_2) \
  declare_frame_object_1_slot__sans_new(name, slot_1); \
  f2ptr f2__frame_object__funk__funkvar(name, slot_2)(f2ptr cause, f2ptr this)
  
#define declare_frame_object_3_slot__sans_new(name, slot_1, slot_2, slot_3) \
  declare_frame_object_2_slot__sans_new(name, slot_1, slot_2); \
  f2ptr f2__frame_object__funk__funkvar(name, slot_3)(f2ptr cause, f2ptr this)
  
#define declare_frame_object_4_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4) \
  declare_frame_object_3_slot__sans_new(name, slot_1, slot_2, slot_3); \
  f2ptr f2__frame_object__funk__funkvar(name, slot_4)(f2ptr cause, f2ptr this)
  
#define declare_frame_object_5_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  declare_frame_object_4_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4); \
  f2ptr f2__frame_object__funk__funkvar(name, slot_5)(f2ptr cause, f2ptr this)
  
#define declare_frame_object_6_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  declare_frame_object_5_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  f2ptr f2__frame_object__funk__funkvar(name, slot_6)(f2ptr cause, f2ptr this)


#define declare_frame_object_0_slot(name) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause); \
  declare_frame_object_0_slot__sans_new(name)

#define declare_frame_object_1_slot(name, slot_1) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1); \
  declare_frame_object_1_slot__sans_new(name, slot_1)

#define declare_frame_object_2_slot(name, slot_1, slot_2) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2); \
  declare_frame_object_2_slot__sans_new(name, slot_1, slot_2)

#define declare_frame_object_3_slot(name, slot_1, slot_2, slot_3) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3); \
  declare_frame_object_3_slot__sans_new(name, slot_1, slot_2, slot_3)

#define declare_frame_object_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4); \
  declare_frame_object_4_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4)

#define declare_frame_object_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5); \
  declare_frame_object_5_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5)

#define declare_frame_object_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6); \
  declare_frame_object_6_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6)



#define def_f2__frame__object__new__0_slot(name) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause) { \
    f2ptr this = f2__frame__new(cause); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),  new__symbol(cause, #name)); \
    return this; \
  } \
  def_pcfunk0(frame_object__funk__pcfunkvar(name, new), return f2__frame_object__funk__funkvar(name, new)(this_cause))

#define def_f2__frame__object__new__1_slot(name, slot_1) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1) { \
    f2ptr this = f2__frame__new(cause); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),  new__symbol(cause, #name)); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), slot_1); \
    return this; \
  } \
  def_pcfunk1(frame_object__funk__pcfunkvar(name, new), slot_1, return f2__frame_object__funk__funkvar(name, new)(this_cause, slot_1))

#define def_f2__frame__object__new__2_slot(name, slot_1, slot_2) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2) { \
    f2ptr this = f2__frame__new(cause); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),  new__symbol(cause, #name)); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), slot_1); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_2), slot_2); \
    return this; \
  } \
  def_pcfunk2(frame_object__funk__pcfunkvar(name, new), slot_1, slot_2, return f2__frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2))

#define def_f2__frame__object__new__3_slot(name, slot_1, slot_2, slot_3) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3) { \
    f2ptr this = f2__frame__new(cause); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),  new__symbol(cause, #name)); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), slot_1); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_2), slot_2); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_3), slot_3); \
    return this; \
  } \
  def_pcfunk3(frame_object__funk__pcfunkvar(name, new), slot_1, slot_2, slot_3, return f2__frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3))

#define def_f2__frame__object__new__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4) { \
    f2ptr this = f2__frame__new(cause); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),  new__symbol(cause, #name)); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), slot_1); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_2), slot_2); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_3), slot_3); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_4), slot_4); \
    return this; \
  } \
  def_pcfunk4(frame_object__funk__pcfunkvar(name, new), slot_1, slot_2, slot_3, slot_4, return f2__frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4))

#define def_f2__frame__object__new__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  f2ptr f2__frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5) { \
    f2ptr this = f2__frame__new(cause); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),  new__symbol(cause, #name)); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), slot_1); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_2), slot_2); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_3), slot_3); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_4), slot_4); \
    f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_5), slot_5); \
    return this; \
  } \
  def_pcfunk5(frame_object__funk__pcfunkvar(name, new), slot_1, slot_2, slot_3, slot_4, slot_5, return f2__frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5))

#define def_frame_object__funk__slot(name, slot_name) \
  f2ptr f2__frame_object__funk__funkvar(name, slot_name)(f2ptr cause, f2ptr this) {return f2__frame__lookup_var_value(cause, this, new__symbol(cause, #slot_name), f2larva__new(cause, 325));} \
  def_pcfunk1(frame_object__funk__pcfunkvar(name, slot_name), this, return f2__frame_object__funk__funkvar(name, slot_name)(this_cause, this)); \
   \
  f2ptr f2__frame_object__funk__funkvar(name, slot_name##__set)(f2ptr cause, f2ptr this, f2ptr value) {return f2__frame__var_value__set(cause, this, new__symbol(cause, #slot_name), value, f2larva__new(cause, 325));} \
  def_pcfunk2(frame_object__funk__pcfunkvar(name, slot_name##__set), this, value, return f2__frame_object__funk__funkvar(name, slot_name##__set)(this_cause, this, value))

#define def_f2frame_object__primobject_type__new__slot_body(name, slot_body) \
  f2ptr f2frame_object__primobject_type__new__funkvar(name)(f2ptr cause) { \
    f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("frame"), (u8*)"frame"), nil)); \
    {char* slot_name = "is_type";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), frame_object__slot__funk__var(name, is_type));} \
    {char* slot_name = "type";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), frame_object__slot__funk__var(name, type));} \
    {char* slot_name = "new";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), frame_object__slot__funk__var(name, new));} \
    slot_body; \
    return this; \
  }

#define f2frame_object__primobject_type__new__slot(name, slot_name) \
  {char* slot_name = #slot_name; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), frame_object__slot__funk__var(name, slot_name));} \
  {char* slot_name = #slot_name; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name), frame_object__slot__funk__var(name, slot_name##__set));}

#define def_f2frame_object__primobject_type__new__0_slot(name) \
  def_f2frame_object__primobject_type__new__slot_body(name, )

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

#define def_f2frame_object__primobject_type__new__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_f2frame_object__primobject_type__new__slot_body(name, \
	  					      f2frame_object__primobject_type__new__slot(name, slot_1); \
						      f2frame_object__primobject_type__new__slot(name, slot_2); \
						      f2frame_object__primobject_type__new__slot(name, slot_3); \
						      f2frame_object__primobject_type__new__slot(name, slot_4); \
						      f2frame_object__primobject_type__new__slot(name, slot_5))

#define def_frame_object__global__sans_slots(name) \
  def_frame_object__shared_global_vars(name); \
   \
  boolean_t raw__frame_object__funk__funkvar(name, is_type)(f2ptr cause, f2ptr thing) { \
    f2ptr this_type_name_symbol = new__symbol(cause, #name); \
    if (! raw__frame__is_type(cause, thing)) { \
      return boolean__false; \
    } \
    f2ptr thing_type_name = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil); \
    if (raw__eq(cause, this_type_name_symbol, thing_type_name)) { \
      return boolean__true; \
    } \
    f2ptr thing_type = f2__lookup_type(cause, thing_type_name); \
    if (raw__primobject_type__is_type_or_has_parent_type(cause, thing_type, this_type_name_symbol)) { \
      return boolean__true; \
    } \
    return boolean__false; \
  } \
   \
  f2ptr f2__frame_object__funk__funkvar(name, is_type)(f2ptr cause, f2ptr thing) {return f2bool__new(raw__frame_object__funk__funkvar(name, is_type)(cause, thing));} \
  def_pcfunk1(frame_object__funk__pcfunkvar(name, is_type), thing, return f2__frame_object__funk__funkvar(name, is_type)(this_cause, thing)); \
   \
  f2ptr f2__frame_object__funk__funkvar(name, type)(f2ptr cause, f2ptr this) {return new__symbol(cause, #name);} \
  def_pcfunk1(frame_object__funk__pcfunkvar(name, type), this, return f2__frame_object__funk__funkvar(name, type)(this_cause, this))

#define def_frame_object__global__0_slot(name) \
  def_frame_object__global__sans_slots(name); \
  def_frame_object__slot_global_vars__0_slot(name); \
  def_f2__frame__object__new__0_slot(name); \
   \
   \
  def_f2frame_object__primobject_type__new__0_slot(name)

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

#define def_frame_object__global__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_frame_object__global__sans_slots(name); \
  def_frame_object__slot_global_vars__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  def_f2__frame__object__new__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
   \
  def_frame_object__funk__slot(name, slot_1); \
  def_frame_object__funk__slot(name, slot_2); \
  def_frame_object__funk__slot(name, slot_3); \
  def_frame_object__funk__slot(name, slot_4); \
  def_frame_object__funk__slot(name, slot_5); \
   \
  def_f2frame_object__primobject_type__new__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5)

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

#define init_frame_object__0_slot(name) \
  init_frame_object__sans_slots(name);

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

#define init_frame_object__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  init_frame_object__sans_slots(name); \
  init_frame_object__slot(name, slot_1); \
  init_frame_object__slot(name, slot_2); \
  init_frame_object__slot(name, slot_3); \
  init_frame_object__slot(name, slot_4); \
  init_frame_object__slot(name, slot_5);


f2ptr f2physical_sim_object__primobject_type__new(f2ptr cause);

// **

void f2__frame_objects__reinitialize_globalvars();
void f2__frame_objects__initialize();

#endif // F2__FRAME_OBJECTS__H


