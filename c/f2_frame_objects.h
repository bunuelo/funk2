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
  def_frame_object__symbol_funk__global_vars(name, type)

#define def_frame_object__slot_global_vars__0_slot(name)

#define def_frame_object__slot_global_vars__1_slot(name, slot_1) \
  def_frame_object__slot_global_vars__0_slot(name);		 \
  def_frame_object__slot__global_vars(name, slot_1)

#define def_frame_object__slot_global_vars__2_slot(name, slot_1, slot_2) \
  def_frame_object__slot_global_vars__1_slot(name, slot_1);		\
  def_frame_object__slot__global_vars(name, slot_2)

#define def_frame_object__slot_global_vars__3_slot(name, slot_1, slot_2, slot_3) \
  def_frame_object__slot_global_vars__2_slot(name, slot_1, slot_2);	\
  def_frame_object__slot__global_vars(name, slot_3)

#define def_frame_object__slot_global_vars__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_frame_object__slot_global_vars__3_slot(name, slot_1, slot_2, slot_3); \
  def_frame_object__slot__global_vars(name, slot_4)

#define def_frame_object__slot_global_vars__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_frame_object__slot_global_vars__4_slot(name, slot_1, slot_2, slot_3, slot_4); \
  def_frame_object__slot__global_vars(name, slot_5)

#define def_frame_object__slot_global_vars__6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_frame_object__slot_global_vars__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  def_frame_object__slot__global_vars(name, slot_6)

#define def_frame_object__slot_global_vars__7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_frame_object__slot_global_vars__6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
  def_frame_object__slot__global_vars(name, slot_7)

#define def_frame_object__slot_global_vars__8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_frame_object__slot_global_vars__7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
  def_frame_object__slot__global_vars(name, slot_8)

#define def_frame_object__slot_global_vars__9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_frame_object__slot_global_vars__8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
  def_frame_object__slot__global_vars(name, slot_9)

#define def_frame_object__slot_global_vars__10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_frame_object__slot_global_vars__9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
  def_frame_object__slot__global_vars(name, slot_10)

#define def_frame_object__slot_global_vars__11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_frame_object__slot_global_vars__10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
  def_frame_object__slot__global_vars(name, slot_11)

#define def_frame_object__slot_global_vars__12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_frame_object__slot_global_vars__11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
  def_frame_object__slot__global_vars(name, slot_12)

#define def_frame_object__slot_global_vars__13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_frame_object__slot_global_vars__12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
  def_frame_object__slot__global_vars(name, slot_13)

#define def_frame_object__slot_global_vars__14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_frame_object__slot_global_vars__13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
  def_frame_object__slot__global_vars(name, slot_14)

#define def_frame_object__slot_global_vars__15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_frame_object__slot_global_vars__14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
  def_frame_object__slot__global_vars(name, slot_15)

#define def_frame_object__slot_global_vars__16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_frame_object__slot_global_vars__15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
  def_frame_object__slot__global_vars(name, slot_16)

#define def_frame_object__slot_global_vars__17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_frame_object__slot_global_vars__16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
  def_frame_object__slot__global_vars(name, slot_17)

#define def_frame_object__slot_global_vars__18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_frame_object__slot_global_vars__17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
  def_frame_object__slot__global_vars(name, slot_18)

#define def_frame_object__slot_global_vars__19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_frame_object__slot_global_vars__18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
  def_frame_object__slot__global_vars(name, slot_19)

#define def_frame_object__slot_global_vars__20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_frame_object__slot_global_vars__19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
  def_frame_object__slot__global_vars(name, slot_20)

#define def_frame_object__slot_global_vars__21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_frame_object__slot_global_vars__20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
  def_frame_object__slot__global_vars(name, slot_21)

#define def_frame_object__slot_global_vars__22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  def_frame_object__slot_global_vars__21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21); \
  def_frame_object__slot__global_vars(name, slot_22)

#define def_frame_object__slot_global_vars__23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  def_frame_object__slot_global_vars__22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22); \
  def_frame_object__slot__global_vars(name, slot_23)

#define def_frame_object__slot_global_vars__24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  def_frame_object__slot_global_vars__23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23); \
  def_frame_object__slot__global_vars(name, slot_24)

#define def_frame_object__slot_global_vars__25_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  def_frame_object__slot_global_vars__24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24); \
  def_frame_object__slot__global_vars(name, slot_25)


#define      frame_object__funk__pcfunkvar(name, funk_name)        name##__##funk_name
#define    f2frame_object__funk__funkvar(name, funk_name)      f2##name##__##funk_name
#define raw__frame_object__funk__funkvar(name, funk_name)   raw__##name##__##funk_name
#define  f2__frame_object__funk__funkvar(name, funk_name)    f2__##name##__##funk_name

#define f2frame_object__primobject_type__new__funkvar(name) f2##name##__primobject_type__new

#define declare_frame_object_0_slot__sans_new(name) \
  f2ptr f2frame_object__primobject_type__new__funkvar(name)(f2ptr cause); \
  boolean_t raw__frame_object__funk__funkvar(name, is_type)(f2ptr cause, f2ptr thing); \
  f2ptr      f2__frame_object__funk__funkvar(name, is_type)(f2ptr cause, f2ptr thing); \
  f2ptr      f2__frame_object__funk__funkvar(name, type)   (f2ptr cause, f2ptr this)


#define declare_frame_object_slot(name, slot) \
  f2ptr raw__frame_object__funk__funkvar(name, slot)(f2ptr cause, f2ptr this); \
  f2ptr raw__frame_object__funk__funkvar(name, slot##__set)(f2ptr cause, f2ptr this, f2ptr value); \
  f2ptr  f2__frame_object__funk__funkvar(name, slot)(f2ptr cause, f2ptr this); \
  f2ptr  f2__frame_object__funk__funkvar(name, slot##__set)(f2ptr cause, f2ptr this, f2ptr value)

#define declare_frame_object_1_slot__sans_new(name, slot_1) \
  declare_frame_object_0_slot__sans_new(name); \
  declare_frame_object_slot(name, slot_1)

//  f2ptr raw__frame_object__funk__funkvar(name, slot_1)(f2ptr cause, f2ptr this); 
//  f2ptr raw__frame_object__funk__funkvar(name, slot_1##__set)(f2ptr cause, f2ptr this, f2ptr value); 
//  f2ptr  f2__frame_object__funk__funkvar(name, slot_1)(f2ptr cause, f2ptr this); 
//  f2ptr  f2__frame_object__funk__funkvar(name, slot_1##__set)(f2ptr cause, f2ptr this, f2ptr value)

#define declare_frame_object_2_slot__sans_new(name, slot_1, slot_2) \
  declare_frame_object_1_slot__sans_new(name, slot_1); \
  declare_frame_object_slot(name, slot_2)
  
#define declare_frame_object_3_slot__sans_new(name, slot_1, slot_2, slot_3) \
  declare_frame_object_2_slot__sans_new(name, slot_1, slot_2); \
  declare_frame_object_slot(name, slot_3)
  
#define declare_frame_object_4_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4) \
  declare_frame_object_3_slot__sans_new(name, slot_1, slot_2, slot_3); \
  declare_frame_object_slot(name, slot_4)
  
#define declare_frame_object_5_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  declare_frame_object_4_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4); \
  declare_frame_object_slot(name, slot_5)
  
#define declare_frame_object_6_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  declare_frame_object_5_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  declare_frame_object_slot(name, slot_6)

#define declare_frame_object_7_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  declare_frame_object_6_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
  declare_frame_object_slot(name, slot_7)

#define declare_frame_object_8_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  declare_frame_object_7_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
  declare_frame_object_slot(name, slot_8)

#define declare_frame_object_9_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  declare_frame_object_8_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
  declare_frame_object_slot(name, slot_9)

#define declare_frame_object_10_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  declare_frame_object_9_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
  declare_frame_object_slot(name, slot_10)

#define declare_frame_object_11_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  declare_frame_object_10_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
  declare_frame_object_slot(name, slot_11)

#define declare_frame_object_12_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  declare_frame_object_11_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
  declare_frame_object_slot(name, slot_12)

#define declare_frame_object_13_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  declare_frame_object_12_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
  declare_frame_object_slot(name, slot_13)

#define declare_frame_object_14_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  declare_frame_object_13_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
  declare_frame_object_slot(name, slot_14)

#define declare_frame_object_15_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  declare_frame_object_14_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
  declare_frame_object_slot(name, slot_15)

#define declare_frame_object_16_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  declare_frame_object_15_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
  declare_frame_object_slot(name, slot_16)

#define declare_frame_object_17_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  declare_frame_object_16_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
  declare_frame_object_slot(name, slot_17)

#define declare_frame_object_18_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  declare_frame_object_17_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
  declare_frame_object_slot(name, slot_18)

#define declare_frame_object_19_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  declare_frame_object_18_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
  declare_frame_object_slot(name, slot_19)

#define declare_frame_object_20_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  declare_frame_object_19_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
  declare_frame_object_slot(name, slot_20)

#define declare_frame_object_21_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  declare_frame_object_20_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
  declare_frame_object_slot(name, slot_21)

#define declare_frame_object_22_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  declare_frame_object_21_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21); \
  declare_frame_object_slot(name, slot_22)

#define declare_frame_object_23_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  declare_frame_object_22_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22); \
  declare_frame_object_slot(name, slot_23)

#define declare_frame_object_24_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  declare_frame_object_23_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23); \
  declare_frame_object_slot(name, slot_24)

#define declare_frame_object_25_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  declare_frame_object_24_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24); \
  declare_frame_object_slot(name, slot_25)


#define declare_frame_object_0_slot(name) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause); \
  declare_frame_object_0_slot__sans_new(name)

#define declare_frame_object_1_slot(name, slot_1) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1); \
  declare_frame_object_1_slot__sans_new(name, slot_1)

#define declare_frame_object_2_slot(name, slot_1, slot_2) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2); \
  declare_frame_object_2_slot__sans_new(name, slot_1, slot_2)

#define declare_frame_object_3_slot(name, slot_1, slot_2, slot_3) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3); \
  declare_frame_object_3_slot__sans_new(name, slot_1, slot_2, slot_3)

#define declare_frame_object_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4); \
  declare_frame_object_4_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4)

#define declare_frame_object_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5); \
  declare_frame_object_5_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5)

#define declare_frame_object_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6); \
  declare_frame_object_6_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6)

#define declare_frame_object_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7); \
  declare_frame_object_7_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7)

#define declare_frame_object_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8); \
  declare_frame_object_8_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8)

#define declare_frame_object_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9); \
  declare_frame_object_9_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9)

#define declare_frame_object_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10); \
  declare_frame_object_10_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10)

#define declare_frame_object_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11); \
  declare_frame_object_11_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11)

#define declare_frame_object_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12); \
  declare_frame_object_12_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12)

#define declare_frame_object_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13); \
  declare_frame_object_13_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13)

#define declare_frame_object_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14); \
  declare_frame_object_14_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14)

#define declare_frame_object_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15); \
  declare_frame_object_15_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15)

#define declare_frame_object_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16); \
  declare_frame_object_16_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16)

#define declare_frame_object_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17); \
  declare_frame_object_17_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17)

#define declare_frame_object_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18); \
  declare_frame_object_18_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18)

#define declare_frame_object_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19); \
  declare_frame_object_19_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19)

#define declare_frame_object_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20); \
  declare_frame_object_20_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20)

#define declare_frame_object_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21); \
  declare_frame_object_21_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21)

#define declare_frame_object_22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21, f2ptr slot_22); \
  declare_frame_object_22_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22)

#define declare_frame_object_23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21, f2ptr slot_22, f2ptr slot_23); \
  declare_frame_object_23_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23)

#define declare_frame_object_24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21, f2ptr slot_22, f2ptr slot_23, f2ptr slot_24); \
  declare_frame_object_24_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24)

#define declare_frame_object_25_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21, f2ptr slot_22, f2ptr slot_23, f2ptr slot_24, f2ptr slot_25); \
  declare_frame_object_25_slot__sans_new(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25)



#define def_f2__frame__object__new__0_slot__body(name)			\
  f2ptr this = f2__frame__new(cause, nil);				\
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),  new__symbol(cause, #name));

#define def_f2__frame__object__new__1_slot__body(name, slot_1)		\
  def_f2__frame__object__new__0_slot__body(name);			\
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_1), slot_1);

#define def_f2__frame__object__new__2_slot__body(name, slot_1, slot_2)	\
  def_f2__frame__object__new__1_slot__body(name, slot_1); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_2), slot_2);

#define def_f2__frame__object__new__3_slot__body(name, slot_1, slot_2, slot_3) \
  def_f2__frame__object__new__2_slot__body(name, slot_1, slot_2);			\
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_3), slot_3);

#define def_f2__frame__object__new__4_slot__body(name, slot_1, slot_2, slot_3, slot_4) \
  def_f2__frame__object__new__3_slot__body(name, slot_1, slot_2, slot_3);		\
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_4), slot_4);

#define def_f2__frame__object__new__5_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_f2__frame__object__new__4_slot__body(name, slot_1, slot_2, slot_3, slot_4);	\
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_5), slot_5);

#define def_f2__frame__object__new__6_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_f2__frame__object__new__5_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_6), slot_6);

#define def_f2__frame__object__new__7_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_f2__frame__object__new__6_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_7), slot_7);

#define def_f2__frame__object__new__8_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_f2__frame__object__new__7_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_8), slot_8);

#define def_f2__frame__object__new__9_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_f2__frame__object__new__8_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_9), slot_9);

#define def_f2__frame__object__new__10_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_f2__frame__object__new__9_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_10), slot_10);

#define def_f2__frame__object__new__11_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_f2__frame__object__new__10_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_11), slot_11);

#define def_f2__frame__object__new__12_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_f2__frame__object__new__11_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_12), slot_12);

#define def_f2__frame__object__new__13_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_f2__frame__object__new__12_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_13), slot_13);

#define def_f2__frame__object__new__14_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_f2__frame__object__new__13_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_14), slot_14);

#define def_f2__frame__object__new__15_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_f2__frame__object__new__14_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_15), slot_15);

#define def_f2__frame__object__new__16_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_f2__frame__object__new__15_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_16), slot_16);

#define def_f2__frame__object__new__17_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_f2__frame__object__new__16_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_17), slot_17);

#define def_f2__frame__object__new__18_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_f2__frame__object__new__17_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_18), slot_18);

#define def_f2__frame__object__new__19_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_f2__frame__object__new__18_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_19), slot_19);

#define def_f2__frame__object__new__20_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_f2__frame__object__new__19_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_20), slot_20);

#define def_f2__frame__object__new__21_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_f2__frame__object__new__20_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_21), slot_21);

#define def_f2__frame__object__new__22_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  def_f2__frame__object__new__21_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_22), slot_22);

#define def_f2__frame__object__new__23_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  def_f2__frame__object__new__22_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_23), slot_23);

#define def_f2__frame__object__new__24_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  def_f2__frame__object__new__23_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_24), slot_24);

#define def_f2__frame__object__new__25_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  def_f2__frame__object__new__24_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24); \
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot_25), slot_25);


#define def_f2__frame__object__new__0_slot__macro(name, body)	  \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause) { \
    body; \
    return this; \
  } \
  def_pcfunk0(frame_object__funk__pcfunkvar(name, create), return f2frame_object__funk__funkvar(name, new)(this_cause))

#define def_f2__frame__object__new__1_slot__macro(name, slot_1, body)	\
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1) { \
    body; \
    return this; \
  } \
  def_pcfunk1(frame_object__funk__pcfunkvar(name, create), slot_1, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1))

#define def_f2__frame__object__new__2_slot__macro(name, slot_1, slot_2, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2) { \
    body; \
    return this; \
  } \
  def_pcfunk2(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2))

#define def_f2__frame__object__new__3_slot__macro(name, slot_1, slot_2, slot_3, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3) { \
    body; \
    return this; \
  } \
  def_pcfunk3(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3))

#define def_f2__frame__object__new__4_slot__macro(name, slot_1, slot_2, slot_3, slot_4, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4) { \
    body; \
    return this; \
  } \
  def_pcfunk4(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4))

#define def_f2__frame__object__new__5_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5) { \
    body; \
    return this; \
  } \
  def_pcfunk5(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5))

#define def_f2__frame__object__new__6_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6) { \
    body; \
    return this; \
  } \
  def_pcfunk6(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6))

#define def_f2__frame__object__new__7_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7) { \
    body; \
    return this; \
  } \
  def_pcfunk7(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7))

#define def_f2__frame__object__new__8_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8) { \
    body; \
    return this; \
  } \
  def_pcfunk8(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8))

#define def_f2__frame__object__new__9_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9) { \
    body; \
    return this; \
  } \
  def_pcfunk9(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9))

#define def_f2__frame__object__new__10_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10) { \
    body; \
    return this; \
  }									\
  def_pcfunk10(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10))
  
#define def_f2__frame__object__new__11_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11) { \
    body; \
    return this; \
  }									\
  def_pcfunk11(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11))
  
#define def_f2__frame__object__new__12_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12) { \
    body; \
    return this; \
  }									\
  def_pcfunk12(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12))
  
#define def_f2__frame__object__new__13_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13) { \
    body; \
    return this; \
  }									\
  def_pcfunk13(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13))
  
#define def_f2__frame__object__new__14_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14) { \
    body; \
    return this; \
  }									\
  def_pcfunk14(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14))
  
#define def_f2__frame__object__new__15_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15) { \
    body; \
    return this; \
  }									\
  def_pcfunk15(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15))
  
#define def_f2__frame__object__new__16_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16) { \
    body; \
    return this; \
  }									\
  def_pcfunk16(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16))
  
#define def_f2__frame__object__new__17_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17) { \
    body; \
    return this; \
  }									\
  def_pcfunk17(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17))
  
#define def_f2__frame__object__new__18_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18) { \
    body; \
    return this; \
  }									\
  def_pcfunk18(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18))
  
#define def_f2__frame__object__new__19_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19) { \
    body; \
    return this; \
  }									\
  def_pcfunk19(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19))
  
#define def_f2__frame__object__new__20_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20) { \
    body; \
    return this; \
  }									\
  def_pcfunk20(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20))
  
#define def_f2__frame__object__new__21_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21) { \
    body; \
    return this; \
  }									\
  def_pcfunk21(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21))
  
#define def_f2__frame__object__new__22_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21, f2ptr slot_22) { \
    body; \
    return this; \
  }									\
  def_pcfunk22(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22,  \
	       return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22))
  
#define def_f2__frame__object__new__23_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21, f2ptr slot_22, f2ptr slot_23) { \
    body; \
    return this; \
  }									\
  def_pcfunk23(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, \
	       return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23))
  
#define def_f2__frame__object__new__24_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21, f2ptr slot_22, f2ptr slot_23, f2ptr slot_24) { \
    body; \
    return this; \
  }									\
  def_pcfunk24(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, \
	       return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24))
  
#define def_f2__frame__object__new__25_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25, body) \
  f2ptr f2frame_object__funk__funkvar(name, new)(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21, f2ptr slot_22, f2ptr slot_23, f2ptr slot_24, f2ptr slot_25) { \
    body; \
    return this; \
  }									\
  def_pcfunk25(frame_object__funk__pcfunkvar(name, create), slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25, \
	       return f2frame_object__funk__funkvar(name, new)(this_cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25))
  

#define def_f2__frame__object__new__0_slot(name)			\
  def_f2__frame__object__new__0_slot__macro(name,			\
					    def_f2__frame__object__new__0_slot__body(name))
  
#define def_f2__frame__object__new__1_slot(name, slot_1)		\
  def_f2__frame__object__new__1_slot__macro(name, slot_1,		\
					    def_f2__frame__object__new__1_slot__body(name, slot_1))
  
#define def_f2__frame__object__new__2_slot(name, slot_1, slot_2)	\
  def_f2__frame__object__new__2_slot__macro(name, slot_1, slot_2,	\
					    def_f2__frame__object__new__2_slot__body(name, slot_1, slot_2))
  
#define def_f2__frame__object__new__3_slot(name, slot_1, slot_2, slot_3) \
  def_f2__frame__object__new__3_slot__macro(name, slot_1, slot_2, slot_3, \
					    def_f2__frame__object__new__3_slot__body(name, slot_1, slot_2, slot_3))
  
#define def_f2__frame__object__new__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_f2__frame__object__new__4_slot__macro(name, slot_1, slot_2, slot_3, slot_4,  \
					    def_f2__frame__object__new__4_slot__body(name, slot_1, slot_2, slot_3, slot_4))
  
#define def_f2__frame__object__new__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_f2__frame__object__new__5_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, \
					    def_f2__frame__object__new__5_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5))
  
#define def_f2__frame__object__new__6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_f2__frame__object__new__6_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, \
					    def_f2__frame__object__new__6_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6))
  
#define def_f2__frame__object__new__7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_f2__frame__object__new__7_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7,  \
					    def_f2__frame__object__new__7_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7))
  
#define def_f2__frame__object__new__8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_f2__frame__object__new__8_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, \
					    def_f2__frame__object__new__8_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8))
  
#define def_f2__frame__object__new__9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_f2__frame__object__new__9_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9,  \
					    def_f2__frame__object__new__9_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9))
  
#define def_f2__frame__object__new__10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_f2__frame__object__new__10_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, \
					     def_f2__frame__object__new__10_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10))
  
#define def_f2__frame__object__new__11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_f2__frame__object__new__11_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, \
					     def_f2__frame__object__new__11_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11))
  
#define def_f2__frame__object__new__12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_f2__frame__object__new__12_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12,  \
					     def_f2__frame__object__new__12_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12))
  
#define def_f2__frame__object__new__13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_f2__frame__object__new__13_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, \
					     def_f2__frame__object__new__13_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13))
  
#define def_f2__frame__object__new__14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_f2__frame__object__new__14_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	\
					     def_f2__frame__object__new__14_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14))
  
#define def_f2__frame__object__new__15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_f2__frame__object__new__15_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15,  \
					     def_f2__frame__object__new__15_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15))
  
#define def_f2__frame__object__new__16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_f2__frame__object__new__16_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15, slot_16, \
					     def_f2__frame__object__new__16_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16))
  
#define def_f2__frame__object__new__17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_f2__frame__object__new__17_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15, slot_16, slot_17, \
					     def_f2__frame__object__new__17_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17))
  
#define def_f2__frame__object__new__18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_f2__frame__object__new__18_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15, slot_16, slot_17, slot_18,  \
					     def_f2__frame__object__new__18_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18))
  
#define def_f2__frame__object__new__19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_f2__frame__object__new__19_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15, slot_16, slot_17, slot_18, slot_19, \
					     def_f2__frame__object__new__19_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19))

#define def_f2__frame__object__new__20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_f2__frame__object__new__20_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15, slot_16, slot_17, slot_18, slot_19, slot_20,  \
					     def_f2__frame__object__new__20_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20))

#define def_f2__frame__object__new__21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_f2__frame__object__new__21_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, \
					     def_f2__frame__object__new__21_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21))

#define def_f2__frame__object__new__22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  def_f2__frame__object__new__22_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22,	\
					     def_f2__frame__object__new__22_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22))

#define def_f2__frame__object__new__23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  def_f2__frame__object__new__23_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, \
					     def_f2__frame__object__new__23_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23))

#define def_f2__frame__object__new__24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  def_f2__frame__object__new__24_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, \
					     def_f2__frame__object__new__24_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24))

#define def_f2__frame__object__new__25_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  def_f2__frame__object__new__25_slot__macro(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14,	slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25, \
					     def_f2__frame__object__new__25_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25))


#define def_frame_object__funk__slot(name, slot_name) \
  f2ptr raw__frame_object__funk__funkvar(name, slot_name)(f2ptr cause, f2ptr this) { \
    f2ptr not_defined_value = __funk2.primobject__frame.type_variable_not_defined__symbol; \
    f2ptr result            = f2__frame__lookup_var_value(cause, this, new__symbol(cause, #slot_name), not_defined_value); \
    if (result == not_defined_value) {					\
      return f2larva__new(cause, 325, nil);				\
    }									\
    return result;							\
  }									\
									\
  f2ptr f2__frame_object__funk__funkvar(name, slot_name)(f2ptr cause, f2ptr this) { \
    if (! raw__frame_object__funk__funkvar(name, is_type)(cause, this)) { \
      return f2larva__new(cause, 1, nil);				\
    }									\
    return raw__frame_object__funk__funkvar(name, slot_name)(cause, this); \
  }									\
  def_pcfunk1(frame_object__funk__pcfunkvar(name, slot_name), this, return f2__frame_object__funk__funkvar(name, slot_name)(this_cause, this)); \
  									\
  f2ptr raw__frame_object__funk__funkvar(name, slot_name##__set)(f2ptr cause, f2ptr this, f2ptr value) { \
    f2ptr not_defined_value = __funk2.primobject__frame.type_variable_not_defined__symbol; \
    f2ptr result            = f2__frame__var_value__set(cause, this, new__symbol(cause, #slot_name), value, not_defined_value); \
    if (result == not_defined_value) {					\
      return f2larva__new(cause, 325, nil);				\
    }									\
    return result;							\
  }									\
  									\
  f2ptr f2__frame_object__funk__funkvar(name, slot_name##__set)(f2ptr cause, f2ptr this, f2ptr value) { \
    if (! raw__frame_object__funk__funkvar(name, is_type)(cause, this)) { \
      return f2larva__new(cause, 1, nil);				\
    }									\
    return raw__frame_object__funk__funkvar(name, slot_name##__set)(cause, this, value); \
  }									\
  def_pcfunk2(frame_object__funk__pcfunkvar(name, slot_name##__set), this, value, return f2__frame_object__funk__funkvar(name, slot_name##__set)(this_cause, this, value))

#define def_f2frame_object__primobject_type__new__slot_body(name, slot_body) \
  f2ptr f2frame_object__primobject_type__new__funkvar(name)(f2ptr cause) { \
    f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("frame"), (u8*)"frame"), nil)); \
    {char* slot_name = "is_type";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), frame_object__slot__funk__var(name, is_type));} \
    {char* slot_name = "type";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), frame_object__slot__funk__var(name, type));} \
    slot_body; \
    return this; \
  }

#define f2frame_object__primobject_type__new__slot(name, slot_name) \
  {char* slot_name = #slot_name; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), frame_object__slot__funk__var(name, slot_name));} \
  {char* slot_name = #slot_name; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name), frame_object__slot__funk__var(name, slot_name##__set));}

#define def_f2frame_object__primobject_type__new__0_slot__slots(name)

#define def_f2frame_object__primobject_type__new__1_slot__slots(name, slot_1) \
  def_f2frame_object__primobject_type__new__0_slot__slots(name) \
  f2frame_object__primobject_type__new__slot(name, slot_1)

#define def_f2frame_object__primobject_type__new__2_slot__slots(name, slot_1, slot_2) \
  def_f2frame_object__primobject_type__new__1_slot__slots(name, slot_1)	\
  f2frame_object__primobject_type__new__slot(name, slot_2)

#define def_f2frame_object__primobject_type__new__3_slot__slots(name, slot_1, slot_2, slot_3) \
  def_f2frame_object__primobject_type__new__2_slot__slots(name, slot_1, slot_2) \
  f2frame_object__primobject_type__new__slot(name, slot_3)

#define def_f2frame_object__primobject_type__new__4_slot__slots(name, slot_1, slot_2, slot_3, slot_4) \
  def_f2frame_object__primobject_type__new__3_slot__slots(name, slot_1, slot_2, slot_3) \
  f2frame_object__primobject_type__new__slot(name, slot_4)

#define def_f2frame_object__primobject_type__new__5_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_f2frame_object__primobject_type__new__4_slot__slots(name, slot_1, slot_2, slot_3, slot_4) \
  f2frame_object__primobject_type__new__slot(name, slot_5)

#define def_f2frame_object__primobject_type__new__6_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_f2frame_object__primobject_type__new__5_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  f2frame_object__primobject_type__new__slot(name, slot_6)

#define def_f2frame_object__primobject_type__new__7_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_f2frame_object__primobject_type__new__6_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  f2frame_object__primobject_type__new__slot(name, slot_7)

#define def_f2frame_object__primobject_type__new__8_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_f2frame_object__primobject_type__new__7_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  f2frame_object__primobject_type__new__slot(name, slot_8)

#define def_f2frame_object__primobject_type__new__9_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_f2frame_object__primobject_type__new__8_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  f2frame_object__primobject_type__new__slot(name, slot_9)

#define def_f2frame_object__primobject_type__new__10_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_f2frame_object__primobject_type__new__9_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  f2frame_object__primobject_type__new__slot(name, slot_10)

#define def_f2frame_object__primobject_type__new__11_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_f2frame_object__primobject_type__new__10_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  f2frame_object__primobject_type__new__slot(name, slot_11)

#define def_f2frame_object__primobject_type__new__12_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_f2frame_object__primobject_type__new__11_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  f2frame_object__primobject_type__new__slot(name, slot_12)

#define def_f2frame_object__primobject_type__new__13_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_f2frame_object__primobject_type__new__12_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  f2frame_object__primobject_type__new__slot(name, slot_13)

#define def_f2frame_object__primobject_type__new__14_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_f2frame_object__primobject_type__new__13_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  f2frame_object__primobject_type__new__slot(name, slot_14)

#define def_f2frame_object__primobject_type__new__15_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_f2frame_object__primobject_type__new__14_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  f2frame_object__primobject_type__new__slot(name, slot_15)

#define def_f2frame_object__primobject_type__new__16_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_f2frame_object__primobject_type__new__15_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  f2frame_object__primobject_type__new__slot(name, slot_16)

#define def_f2frame_object__primobject_type__new__17_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_f2frame_object__primobject_type__new__16_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  f2frame_object__primobject_type__new__slot(name, slot_17)

#define def_f2frame_object__primobject_type__new__18_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_f2frame_object__primobject_type__new__17_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  f2frame_object__primobject_type__new__slot(name, slot_18)

#define def_f2frame_object__primobject_type__new__19_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_f2frame_object__primobject_type__new__18_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  f2frame_object__primobject_type__new__slot(name, slot_19)

#define def_f2frame_object__primobject_type__new__20_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_f2frame_object__primobject_type__new__19_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  f2frame_object__primobject_type__new__slot(name, slot_20)

#define def_f2frame_object__primobject_type__new__21_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_f2frame_object__primobject_type__new__20_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  f2frame_object__primobject_type__new__slot(name, slot_21)

#define def_f2frame_object__primobject_type__new__22_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  def_f2frame_object__primobject_type__new__21_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  f2frame_object__primobject_type__new__slot(name, slot_22)

#define def_f2frame_object__primobject_type__new__23_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  def_f2frame_object__primobject_type__new__22_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  f2frame_object__primobject_type__new__slot(name, slot_23)

#define def_f2frame_object__primobject_type__new__24_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  def_f2frame_object__primobject_type__new__23_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  f2frame_object__primobject_type__new__slot(name, slot_24)

#define def_f2frame_object__primobject_type__new__25_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  def_f2frame_object__primobject_type__new__24_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  f2frame_object__primobject_type__new__slot(name, slot_25)


#define def_f2frame_object__primobject_type__new__0_slot(name) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__0_slot__slots(name))

#define def_f2frame_object__primobject_type__new__1_slot(name, slot_1) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__1_slot__slots(name, slot_1))

#define def_f2frame_object__primobject_type__new__2_slot(name, slot_1, slot_2) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__2_slot__slots(name, slot_1, slot_2))

#define def_f2frame_object__primobject_type__new__3_slot(name, slot_1, slot_2, slot_3) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__3_slot__slots(name, slot_1, slot_2, slot_3))

#define def_f2frame_object__primobject_type__new__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__4_slot__slots(name, slot_1, slot_2, slot_3, slot_4))

#define def_f2frame_object__primobject_type__new__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__5_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5))

#define def_f2frame_object__primobject_type__new__6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__6_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6))

#define def_f2frame_object__primobject_type__new__7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__7_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7))

#define def_f2frame_object__primobject_type__new__8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__8_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8))

#define def_f2frame_object__primobject_type__new__9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__9_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9))

#define def_f2frame_object__primobject_type__new__10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__10_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10))

#define def_f2frame_object__primobject_type__new__11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__11_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11))

#define def_f2frame_object__primobject_type__new__12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__12_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12))

#define def_f2frame_object__primobject_type__new__13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__13_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13))

#define def_f2frame_object__primobject_type__new__14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__14_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14))

#define def_f2frame_object__primobject_type__new__15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__15_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15))

#define def_f2frame_object__primobject_type__new__16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__16_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16))

#define def_f2frame_object__primobject_type__new__17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__17_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17))

#define def_f2frame_object__primobject_type__new__18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__18_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18))

#define def_f2frame_object__primobject_type__new__19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__19_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19))

#define def_f2frame_object__primobject_type__new__20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__20_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20))

#define def_f2frame_object__primobject_type__new__21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__21_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21))

#define def_f2frame_object__primobject_type__new__22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__22_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22))

#define def_f2frame_object__primobject_type__new__23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__23_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23))

#define def_f2frame_object__primobject_type__new__24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__24_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24))

#define def_f2frame_object__primobject_type__new__25_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  def_f2frame_object__primobject_type__new__slot_body(name, def_f2frame_object__primobject_type__new__25_slot__slots(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25))



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
    if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) { \
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


#define def_frame_object__global__0_slot__body(name)

#define def_frame_object__global__1_slot__body(name, slot_1) \
  def_frame_object__global__0_slot__body(name) \
  def_frame_object__funk__slot(name, slot_1);

#define def_frame_object__global__2_slot__body(name, slot_1, slot_2) \
  def_frame_object__global__1_slot__body(name, slot_1)		     \
  def_frame_object__funk__slot(name, slot_2);

#define def_frame_object__global__3_slot__body(name, slot_1, slot_2, slot_3) \
  def_frame_object__global__2_slot__body(name, slot_1, slot_2)		\
  def_frame_object__funk__slot(name, slot_3);

#define def_frame_object__global__4_slot__body(name, slot_1, slot_2, slot_3, slot_4) \
  def_frame_object__global__3_slot__body(name, slot_1, slot_2, slot_3)	\
  def_frame_object__funk__slot(name, slot_4);

#define def_frame_object__global__5_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_frame_object__global__4_slot__body(name, slot_1, slot_2, slot_3, slot_4) \
  def_frame_object__funk__slot(name, slot_5);

#define def_frame_object__global__6_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_frame_object__global__5_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_frame_object__funk__slot(name, slot_6);

#define def_frame_object__global__7_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_frame_object__global__6_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_frame_object__funk__slot(name, slot_7);

#define def_frame_object__global__8_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_frame_object__global__7_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_frame_object__funk__slot(name, slot_8);

#define def_frame_object__global__9_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_frame_object__global__8_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_frame_object__funk__slot(name, slot_9);

#define def_frame_object__global__10_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_frame_object__global__9_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_frame_object__funk__slot(name, slot_10);

#define def_frame_object__global__11_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_frame_object__global__10_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_frame_object__funk__slot(name, slot_11);

#define def_frame_object__global__12_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_frame_object__global__11_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_frame_object__funk__slot(name, slot_12);

#define def_frame_object__global__13_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_frame_object__global__12_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_frame_object__funk__slot(name, slot_13);

#define def_frame_object__global__14_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_frame_object__global__13_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_frame_object__funk__slot(name, slot_14);

#define def_frame_object__global__15_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_frame_object__global__14_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_frame_object__funk__slot(name, slot_15);

#define def_frame_object__global__16_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_frame_object__global__15_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_frame_object__funk__slot(name, slot_16);

#define def_frame_object__global__17_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_frame_object__global__16_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_frame_object__funk__slot(name, slot_17);

#define def_frame_object__global__18_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_frame_object__global__17_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_frame_object__funk__slot(name, slot_18);

#define def_frame_object__global__19_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_frame_object__global__18_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_frame_object__funk__slot(name, slot_19);

#define def_frame_object__global__20_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_frame_object__global__19_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_frame_object__funk__slot(name, slot_20);

#define def_frame_object__global__21_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_frame_object__global__20_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_frame_object__funk__slot(name, slot_21);

#define def_frame_object__global__22_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  def_frame_object__global__21_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_frame_object__funk__slot(name, slot_22);

#define def_frame_object__global__23_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  def_frame_object__global__22_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  def_frame_object__funk__slot(name, slot_23);

#define def_frame_object__global__24_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  def_frame_object__global__23_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  def_frame_object__funk__slot(name, slot_24);

#define def_frame_object__global__25_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  def_frame_object__global__24_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  def_frame_object__funk__slot(name, slot_25);


#define def_frame_object__global__0_slot(name)	\
  def_frame_object__global__sans_slots(name);	    \
  def_frame_object__slot_global_vars__0_slot(name); \
  def_f2__frame__object__new__0_slot(name);	    \
  def_frame_object__global__0_slot__body(name)			\
  def_f2frame_object__primobject_type__new__0_slot(name)
  
#define def_frame_object__global__1_slot(name, slot_1)	\
  def_frame_object__global__sans_slots(name);		    \
  def_frame_object__slot_global_vars__1_slot(name, slot_1); \
  def_f2__frame__object__new__1_slot(name, slot_1);			\
  def_frame_object__global__1_slot__body(name, slot_1)			\
  def_f2frame_object__primobject_type__new__1_slot(name, slot_1)
  
#define def_frame_object__global__2_slot(name, slot_1, slot_2)	\
  def_frame_object__global__sans_slots(name);			    \
  def_frame_object__slot_global_vars__2_slot(name, slot_1, slot_2);	\
  def_f2__frame__object__new__2_slot(name, slot_1, slot_2);		\
  def_frame_object__global__2_slot__body(name, slot_1, slot_2)		\
  def_f2frame_object__primobject_type__new__2_slot(name, slot_1, slot_2)

#define def_frame_object__global__3_slot(name, slot_1, slot_2, slot_3)	\
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__3_slot(name, slot_1, slot_2, slot_3); \
  def_f2__frame__object__new__3_slot(name, slot_1, slot_2, slot_3);	\
  def_frame_object__global__3_slot__body(name, slot_1, slot_2, slot_3)	\
  def_f2frame_object__primobject_type__new__3_slot(name, slot_1, slot_2, slot_3)
  
#define def_frame_object__global__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_frame_object__global__sans_slots(name); \
  def_frame_object__slot_global_vars__4_slot(name, slot_1, slot_2, slot_3, slot_4); \
  def_f2__frame__object__new__4_slot(name, slot_1, slot_2, slot_3, slot_4); \
  def_frame_object__global__4_slot__body(name, slot_1, slot_2, slot_3, slot_4) \
  def_f2frame_object__primobject_type__new__4_slot(name, slot_1, slot_2, slot_3, slot_4)

#define def_frame_object__global__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  def_f2__frame__object__new__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  def_frame_object__global__5_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_f2frame_object__primobject_type__new__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5)
  
#define def_frame_object__global__6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
  def_f2__frame__object__new__6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
  def_frame_object__global__6_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_f2frame_object__primobject_type__new__6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6)
  
#define def_frame_object__global__7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
  def_f2__frame__object__new__7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
  def_frame_object__global__7_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_f2frame_object__primobject_type__new__7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7)
  
#define def_frame_object__global__8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
  def_f2__frame__object__new__8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
  def_frame_object__global__8_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_f2frame_object__primobject_type__new__8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8)
  
#define def_frame_object__global__9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
  def_f2__frame__object__new__9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
  def_frame_object__global__9_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_f2frame_object__primobject_type__new__9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9)
  
#define def_frame_object__global__10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
  def_f2__frame__object__new__10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
  def_frame_object__global__10_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_f2frame_object__primobject_type__new__10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10)
  
#define def_frame_object__global__11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
  def_f2__frame__object__new__11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
  def_frame_object__global__11_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_f2frame_object__primobject_type__new__11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11)
  
#define def_frame_object__global__12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
  def_f2__frame__object__new__12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
  def_frame_object__global__12_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_f2frame_object__primobject_type__new__12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12)
  
#define def_frame_object__global__13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
  def_f2__frame__object__new__13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
  def_frame_object__global__13_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_f2frame_object__primobject_type__new__13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13)
  
#define def_frame_object__global__14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
  def_f2__frame__object__new__14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
  def_frame_object__global__14_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_f2frame_object__primobject_type__new__14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14)
  
#define def_frame_object__global__15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
  def_f2__frame__object__new__15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
  def_frame_object__global__15_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_f2frame_object__primobject_type__new__15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15)
  
#define def_frame_object__global__16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
  def_f2__frame__object__new__16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
  def_frame_object__global__16_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_f2frame_object__primobject_type__new__16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16)
  
#define def_frame_object__global__17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
  def_f2__frame__object__new__17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
  def_frame_object__global__17_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_f2frame_object__primobject_type__new__17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17)
  
#define def_frame_object__global__18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
  def_f2__frame__object__new__18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
  def_frame_object__global__18_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_f2frame_object__primobject_type__new__18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18)
  
#define def_frame_object__global__19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
  def_f2__frame__object__new__19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
  def_frame_object__global__19_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_f2frame_object__primobject_type__new__19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19)
  
#define def_frame_object__global__20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
  def_f2__frame__object__new__20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
  def_frame_object__global__20_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_f2frame_object__primobject_type__new__20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20)
  
#define def_frame_object__global__21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21); \
  def_f2__frame__object__new__21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21); \
  def_frame_object__global__21_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_f2frame_object__primobject_type__new__21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21)
  
#define def_frame_object__global__22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22); \
  def_f2__frame__object__new__22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22); \
  def_frame_object__global__22_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  def_f2frame_object__primobject_type__new__22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22)
  
#define def_frame_object__global__23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23); \
  def_f2__frame__object__new__23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23); \
  def_frame_object__global__23_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  def_f2frame_object__primobject_type__new__23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23)
  
#define def_frame_object__global__24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24); \
  def_f2__frame__object__new__24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24); \
  def_frame_object__global__24_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  def_f2frame_object__primobject_type__new__24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24)
  
#define def_frame_object__global__25_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  def_frame_object__global__sans_slots(name);				\
  def_frame_object__slot_global_vars__25_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25); \
  def_f2__frame__object__new__25_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25); \
  def_frame_object__global__25_slot__body(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  def_f2frame_object__primobject_type__new__25_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25)
  

#define init_frame_object__funk(name, funk_name) \
  {char* symbol_str = #funk_name; frame_object__slot__symbol__var(name, funk_name) = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);} \
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(frame_object__funk__pcfunkvar(name, funk_name), this, cfunk, "frame_object funktion (defined in " __FILE__ ")"); frame_object__slot__funk__var(name, funk_name) = never_gc(cfunk);}


#define init_frame_object__sans_slots(name) \
  init_frame_object__funk(name, is_type); \
  init_frame_object__funk(name, type)

//  init_frame_object__funk(name, create)

#define init_frame_object__slot(name, slot_name) \
  init_frame_object__funk(name, slot_name); \
  init_frame_object__funk(name, slot_name##__set)

#define init_frame_object__0_slot(name) \
  init_frame_object__sans_slots(name);

#define init_frame_object__1_slot(name, slot_1) \
  init_frame_object__0_slot(name);		\
  init_frame_object__slot(name, slot_1);

#define init_frame_object__2_slot(name, slot_1, slot_2) \
  init_frame_object__1_slot(name, slot_1) \
  init_frame_object__slot(name, slot_2);

#define init_frame_object__3_slot(name, slot_1, slot_2, slot_3) \
  init_frame_object__2_slot(name, slot_1, slot_2) \
  init_frame_object__slot(name, slot_3);

#define init_frame_object__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  init_frame_object__3_slot(name, slot_1, slot_2, slot_3) \
  init_frame_object__slot(name, slot_4);

#define init_frame_object__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  init_frame_object__4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  init_frame_object__slot(name, slot_5);

#define init_frame_object__6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  init_frame_object__5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5)	\
  init_frame_object__slot(name, slot_6);

#define init_frame_object__7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  init_frame_object__6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  init_frame_object__slot(name, slot_7);

#define init_frame_object__8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  init_frame_object__7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  init_frame_object__slot(name, slot_8);

#define init_frame_object__9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  init_frame_object__8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  init_frame_object__slot(name, slot_9);

#define init_frame_object__10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  init_frame_object__9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  init_frame_object__slot(name, slot_10);

#define init_frame_object__11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  init_frame_object__10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  init_frame_object__slot(name, slot_11);

#define init_frame_object__12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  init_frame_object__11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  init_frame_object__slot(name, slot_12);

#define init_frame_object__13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  init_frame_object__12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  init_frame_object__slot(name, slot_13);

#define init_frame_object__14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  init_frame_object__13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  init_frame_object__slot(name, slot_14);

#define init_frame_object__15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  init_frame_object__14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  init_frame_object__slot(name, slot_15);

#define init_frame_object__16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  init_frame_object__15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  init_frame_object__slot(name, slot_16);

#define init_frame_object__17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  init_frame_object__16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  init_frame_object__slot(name, slot_17);

#define init_frame_object__18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  init_frame_object__17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  init_frame_object__slot(name, slot_18);

#define init_frame_object__19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  init_frame_object__18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  init_frame_object__slot(name, slot_19);

#define init_frame_object__20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  init_frame_object__19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  init_frame_object__slot(name, slot_20);

#define init_frame_object__21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  init_frame_object__20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  init_frame_object__slot(name, slot_21);

#define init_frame_object__22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  init_frame_object__21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  init_frame_object__slot(name, slot_22);

#define init_frame_object__23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  init_frame_object__22_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22) \
  init_frame_object__slot(name, slot_23);

#define init_frame_object__24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  init_frame_object__23_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23) \
  init_frame_object__slot(name, slot_24);

#define init_frame_object__25_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24, slot_25) \
  init_frame_object__24_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, slot_22, slot_23, slot_24) \
  init_frame_object__slot(name, slot_25);


// physical_sim_object

f2ptr f2physical_sim_object__primobject_type__new(f2ptr cause);


// **

void f2__frame_objects__reinitialize_globalvars();
void f2__frame_objects__initialize();

#endif // F2__FRAME_OBJECTS__H


