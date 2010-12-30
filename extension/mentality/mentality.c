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

#include "../../c/funk2.h"
#include "mentality.h"


#define def_ceframe__new__common(name, slot_defs)	\
  f2ptr this = f2__frame__new(cause, nil);				\
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, #name)); \
  slot_defs;								\
  return this;								\

#define def_ceframe__new__arg(slot)					\
  f2__frame__add_var_value(cause, this, new__symbol(cause, #slot), slot)

#define def_ceframe__new__arg1(slot1)		\
  def_ceframe__new__arg(slot1)

#define def_ceframe__new__arg2(slot1, slot2)		\
  def_ceframe__new__arg1(slot1);			\
  def_ceframe__new__arg(slot2)

#define def_ceframe__new__arg3(slot1, slot2, slot3)			\
  def_ceframe__new__arg2(slot1, slot2);				\
  def_ceframe__new__arg(slot3)

#define def_ceframe__new__arg4(slot1, slot2, slot3, slot4)		\
  def_ceframe__new__arg3(slot1, slot2, slot3);				\
  def_ceframe__new__arg(slot4)

#define def_ceframe__new__arg5(slot1, slot2, slot3, slot4, slot5)	\
  def_ceframe__new__arg4(slot1, slot2, slot3, slot4);			\
  def_ceframe__new__arg(slot5)

#define def_ceframe__new__arg6(slot1, slot2, slot3, slot4, slot5, slot6) \
  def_ceframe__new__arg5(slot1, slot2, slot3, slot4, slot5);		\
  def_ceframe__new__arg(slot6)

#define def_ceframe__new__arg7(slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_ceframe__new__arg6(slot1, slot2, slot3, slot4, slot5, slot6);	\
  def_ceframe__new__arg(slot7)

#define def_ceframe__new__arg8(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_ceframe__new__arg7(slot1, slot2, slot3, slot4, slot5, slot6, slot7); \
  def_ceframe__new__arg(slot8)

#define def_ceframe__new__arg9(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_ceframe__new__arg8(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8); \
  def_ceframe__new__arg(slot9)

#define def_ceframe__new__arg10(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_ceframe__new__arg9(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9); \
  def_ceframe__new__arg(slot10)

#define def_ceframe__new__arg11(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_ceframe__new__arg10(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10); \
  def_ceframe__new__arg(slot11)

#define def_ceframe__new__arg12(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_ceframe__new__arg11(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11); \
  def_ceframe__new__arg(slot12)


#define def_ceframe0__new(name)					\
  f2ptr raw__##name##__new(f2ptr cause) {				\
    def_ceframe__new__common(name, ); }

#define def_ceframe1__new(name, slot1)					\
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1) {			\
    def_ceframe__new__common(name, def_ceframe__new__arg1(slot1)); }

#define def_ceframe2__new(name, slot1, slot2)				\
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2) {	\
    def_ceframe__new__common(name, def_ceframe__new__arg2(slot1, slot2)); }

#define def_ceframe3__new(name, slot1, slot2, slot3)			\
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3) { \
    def_ceframe__new__common(name, def_ceframe__new__arg3(slot1, slot2, slot3)); }

#define def_ceframe4__new(name, slot1, slot2, slot3, slot4)		\
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4) { \
    def_ceframe__new__common(name, def_ceframe__new__arg4(slot1, slot2, slot3, slot4)); }

#define def_ceframe5__new(name, slot1, slot2, slot3, slot4, slot5)	\
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5) { \
    def_ceframe__new__common(name, def_ceframe__new__arg5(slot1, slot2, slot3, slot4, slot5)); }

#define def_ceframe6__new(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6) { \
    def_ceframe__new__common(name, def_ceframe__new__arg6(slot1, slot2, slot3, slot4, slot5, slot6)); }

#define def_ceframe7__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7) { \
    def_ceframe__new__common(name, def_ceframe__new__arg7(slot1, slot2, slot3, slot4, slot5, slot6, slot7)); }

#define def_ceframe8__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8) { \
    def_ceframe__new__common(name, def_ceframe__new__arg8(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8)); }

#define def_ceframe9__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9) { \
    def_ceframe__new__common(name, def_ceframe__new__arg9(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9)); }

#define def_ceframe10__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10) { \
    def_ceframe__new__common(name, def_ceframe__new__arg10(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10)); }

#define def_ceframe11__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10, f2ptr slot11) { \
    def_ceframe__new__common(name, def_ceframe__new__arg11(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11)); }

#define def_ceframe12__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  f2ptr raw__##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10, f2ptr slot11, f2ptr slot12) { \
    def_ceframe__new__common(name, def_ceframe__new__arg12(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12)); }


#define def_ceframe__is_type(name)			       \
  boolean_t raw__##name##__is_type(f2ptr cause, f2ptr thing) {	\
    if (! raw__frame__is_type(cause, thing)) {			\
      return boolean__false;					\
    }								 \
    f2ptr this_type_name_symbol = new__symbol(cause, #name);	\
    f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil); \
    if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {	\
      return boolean__true;						\
    }									\
    f2ptr thing_type = f2__lookup_type(cause, thing_type_name);		\
    if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) { \
      return boolean__true;						\
    }									\
    return boolean__false;						\
  }									\
									\
  f2ptr f2__##name##__is_type(f2ptr cause, f2ptr thing) {		\
    return f2bool__new(raw__##name##__is_type(cause, thing));		\
  }									\
  export_cefunk1(name##__is_type, thing, 0, "Returns whether or not thing is of type " #name ".");

#define def_ceframe__type(name)			\
  f2ptr raw__##name##__type(f2ptr cause, f2ptr this) {	\
    return f2__object__type(cause, this);		\
  }							\
  							\
  f2ptr f2__##name##__type(f2ptr cause, f2ptr this) {			\
    if (! raw__##name##__is_type(cause, this)) {			\
      return f2larva__new(cause, 1, nil);				\
    }									\
    return raw__##name##__type(cause, this);				\
  }									\
  export_cefunk1(name##__type, thing, 0, "Returns the specific type of object that this " #name " is.");



#define def_ceframe__slot_funk(name, slot)				\
  f2ptr raw__##name##__##slot(f2ptr cause, f2ptr this) {		\
    return f2__frame__lookup_var_value(cause, this, new__symbol(cause, #slot), nil); \
  }									\
  									\
  f2ptr f2__##name##__##slot(f2ptr cause, f2ptr this) {			\
    if (! raw__##name##__is_type(cause, this)) {			\
      return f2larva__new(cause, 1, nil);				\
    }									\
    return raw__##name##__##slot(cause, this);				\
  }									\
  export_cefunk1(name##__##slot, thing, 0, "Returns the " #slot " of the " #name "."); \
  									\
  									\
  f2ptr raw__##name##__##slot##__set(f2ptr cause, f2ptr this, f2ptr value) { \
    return f2__frame__add_var_value(cause, this, new__symbol(cause, #slot), value); \
  }									\
  									\
  f2ptr f2__##name##__##slot##__set(f2ptr cause, f2ptr this, f2ptr value) { \
    if (! raw__##name##__is_type(cause, this)) {			\
      return f2larva__new(cause, 1, nil);				\
    }									\
    return raw__##name##__##slot##__set(cause, this, value);		\
  }									\
  export_cefunk2(name##__##slot##__set, thing, value, 0, "Sets the " #slot " of the " #name ".");


#define def_ceframe__slot_funk1(name, slot1)	\
  def_ceframe__slot_funk(name, slot1)

#define def_ceframe__slot_funk2(name, slot1, slot2)	\
  def_ceframe__slot_funk1(name, slot1)			\
  def_ceframe__slot_funk(name, slot2)

#define def_ceframe__slot_funk3(name, slot1, slot2, slot3)		\
  def_ceframe__slot_funk2(name, slot1, slot2)				\
  def_ceframe__slot_funk(name, slot3)

#define def_ceframe__slot_funk4(name, slot1, slot2, slot3, slot4)	\
  def_ceframe__slot_funk3(name, slot1, slot2, slot3)			\
  def_ceframe__slot_funk(name, slot4)

#define def_ceframe__slot_funk5(name, slot1, slot2, slot3, slot4, slot5) \
  def_ceframe__slot_funk4(name, slot1, slot2, slot3, slot4)		\
  def_ceframe__slot_funk(name, slot5)

#define def_ceframe__slot_funk6(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_ceframe__slot_funk6(name, slot1, slot2, slot3, slot4, slot5)	\
  def_ceframe__slot_funk(name, slot6)

#define def_ceframe__slot_funk7(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_ceframe__slot_funk7(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_ceframe__slot_funk(name, slot7)

#define def_ceframe__slot_funk8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_ceframe__slot_funk8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_ceframe__slot_funk(name, slot8)

#define def_ceframe__slot_funk9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_ceframe__slot_funk9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_ceframe__slot_funk(name, slot9)

#define def_ceframe__slot_funk10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_ceframe__slot_funk10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_ceframe__slot_funk(name, slot10)

#define def_ceframe__slot_funk11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_ceframe__slot_funk11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_ceframe__slot_funk(name, slot11)

#define def_ceframe__slot_funk12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_ceframe__slot_funk12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_ceframe__slot_funk(name, slot12)



#define def_ceframe__primobject_type__new__common(extension_name, name, slot_defs) \
  f2ptr f2__##name##_type__new(f2ptr cause) {				\
    f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame"))); \
    {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, #extension_name), new__symbol(cause, #name "__new")));} \
    {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, #extension_name), new__symbol(cause, #name "__is_type")));} \
    {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, #extension_name), new__symbol(cause, #name "__type")));} \
    slot_defs;								\
    return this;							\
  }

#define def_ceframe__primobject_type__new__slot(extension_name, name, slot) \
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, #slot), f2__core_extension_funk__new(cause, new__symbol(cause, #extension_name), new__symbol(cause, #name "__" #slot)));} \
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, #slot), f2__core_extension_funk__new(cause, new__symbol(cause, #extension_name), new__symbol(cause, #name "__" #slot "__set")));}

#define def_ceframe__primobject_type__new__slot1(extension_name, name, slot1)	\
  def_ceframe__primobject_type__new__slot(extension_name, name, slot1)

#define def_ceframe__primobject_type__new__slot2(extension_name, name, slot1, slot2)	\
  def_ceframe__primobject_type__new__slot1(extension_name, name, slot1)			\
  def_ceframe__primobject_type__new__slot(extension_name, name, slot2)

#define def_ceframe__primobject_type__new__slot3(extension_name, name, slot1, slot2, slot3) \
  def_ceframe__primobject_type__new__slot2(extension_name, name, slot1, slot2)		\
  def_ceframe__primobject_type__new__slot(extension_name, name, slot3)

#define def_ceframe__primobject_type__new__slot4(extension_name, name, slot1, slot2, slot3, slot4) \
  def_ceframe__primobject_type__new__slot3(extension_name, name, slot1, slot2, slot3)	\
  def_ceframe__primobject_type__new__slot(extension_name, name, slot4)

#define def_ceframe__primobject_type__new__slot5(extension_name, name, slot1, slot2, slot3, slot4, slot5) \
  def_ceframe__primobject_type__new__slot4(extension_name, name, slot1, slot2, slot3, slot4) \
  def_ceframe__primobject_type__new__slot(extension_name, name, slot5)

#define def_ceframe__primobject_type__new__slot6(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_ceframe__primobject_type__new__slot5(extension_name, name, slot1, slot2, slot3, slot4, slot5) \
  def_ceframe__primobject_type__new__slot(extension_name, name, slot6)

#define def_ceframe__primobject_type__new__slot7(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_ceframe__primobject_type__new__slot6(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_ceframe__primobject_type__new__slot(extension_name, name, slot7)

#define def_ceframe__primobject_type__new__slot8(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_ceframe__primobject_type__new__slot7(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_ceframe__primobject_type__new__slot(extension_name, name, slot8)

#define def_ceframe__primobject_type__new__slot9(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_ceframe__primobject_type__new__slot8(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_ceframe__primobject_type__new__slot(extension_name, name, slot9)

#define def_ceframe__primobject_type__new__slot10(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_ceframe__primobject_type__new__slot9(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_ceframe__primobject_type__new__slot(extension_name, name, slot10)

#define def_ceframe__primobject_type__new__slot11(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_ceframe__primobject_type__new__slot10(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_ceframe__primobject_type__new__slot(extension_name, name, slot11)

#define def_ceframe__primobject_type__new__slot12(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_ceframe__primobject_type__new__slot11(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_ceframe__primobject_type__new__slot(extension_name, name, slot12)


#define def_ceframe0__primobject_type__new(extension_name, name)	\
  def_ceframe__primobject_type__new__common(extension_name, name, )

#define def_ceframe1__primobject_type__new(extension_name, name, slot1)			\
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot1(extension_name, name, slot1))

#define def_ceframe2__primobject_type__new(extension_name, name, slot1, slot2)		\
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot2(extension_name, name, slot1, slot2))

#define def_ceframe3__primobject_type__new(extension_name, name, slot1, slot2, slot3)	\
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot3(extension_name, name, slot1, slot2, slot3))

#define def_ceframe4__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot4(extension_name, name, slot1, slot2, slot3, slot4))

#define def_ceframe5__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot5(extension_name, name, slot1, slot2, slot3, slot4, slot5))

#define def_ceframe6__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot6(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6))

#define def_ceframe7__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot7(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7))

#define def_ceframe8__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot8(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8))

#define def_ceframe9__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot9(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9))

#define def_ceframe10__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot10(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10))

#define def_ceframe11__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot11(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11))

#define def_ceframe12__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot12(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12))



#define def_ceframe0(extension_name, name)			\
  def_ceframe0__new(name);					\
  def_ceframe__is_type(name);					\
  def_ceframe__type(name);					\
  def_ceframe0__primobject_type__new(extension_name, name)

#define def_ceframe1(extension_name, name, slot1)			\
  def_ceframe1__new(name, slot1);					\
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk1(name, slot1)					\
  def_ceframe1__primobject_type__new(extension_name, name, slot1)

#define def_ceframe2(extension_name, name, slot1, slot2)		\
  def_ceframe2__new(name, slot1, slot2);				\
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk2(name, slot1, slot2)				\
  def_ceframe2__primobject_type__new(extension_name, name, slot1, slot2)

#define def_ceframe3(extension_name, name, slot1, slot2, slot3)		\
  def_ceframe3__new(name, slot1, slot2, slot3);				\
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk3(name, slot1, slot2, slot3)			\
  def_ceframe3__primobject_type__new(extension_name, name, slot1, slot2, slot3)

#define def_ceframe4(extension_name, name, slot1, slot2, slot3, slot4)	\
  def_ceframe4__new(name, slot1, slot2, slot3, slot4);			\
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk4(name, slot1, slot2, slot3, slot4)		\
  def_ceframe4__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4)

#define def_ceframe5(extension_name, name, slot1, slot2, slot3, slot4, slot5) \
  def_ceframe5__new(name, slot1, slot2, slot3, slot4, slot5);		\
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk5(name, slot1, slot2, slot3, slot4, slot5)	\
  def_ceframe5__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5)

#define def_ceframe6(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_ceframe6__new(name, slot1, slot2, slot3, slot4, slot5, slot6);	\
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk6(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_ceframe6__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6)

#define def_ceframe7(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_ceframe7__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7); \
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk7(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_ceframe7__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7)

#define def_ceframe8(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_ceframe8__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8); \
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_ceframe8__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8)

#define def_ceframe9(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_ceframe9__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9); \
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_ceframe9__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9)

#define def_ceframe10(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_ceframe10__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10); \
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_ceframe10__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10)

#define def_ceframe11(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_ceframe11__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11); \
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_ceframe11__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11)

#define def_ceframe12(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot122) \
  def_ceframe12__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12); \
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_ceframe12__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12)


// mentality_project

def_ceframe2(mentality, mentality_project, width, height);

f2ptr f2__mentality_project__new(f2ptr cause) {
  return raw__mentality_project__new(cause, nil, nil);
}
export_cefunk0(mentality_project__new, 0, "Returns a new mentality_project object.");


// mentality

def_ceframe12(mentality, mentality,
	      main_window,
	      menu_bar_vbox,
	      menu_bar,
	      file_menu_item,
	      file_menu,
	      file_new_project_menu_item,
	      file_open_project_menu_item,
	      file_close_project_menu_item,
	      file_save_project_menu_item,
	      file_exit_menu_item,
	      current_project);

f2ptr f2__mentality__new(f2ptr cause) {
  f2ptr main_window                  = f2__gtk__window__new(cause);
  f2ptr menu_bar_vbox                = f2__gtk__vbox__new(cause, f2integer__new(cause, 0));
  f2ptr menu_bar                     = f2__gtk__menu_bar__new(cause);
  f2ptr file_menu_item               = f2__gtk__menu_item__new(cause, new__string(cause, "File"));
  f2ptr file_menu                    = f2__gtk__menu__new(cause);
  f2ptr file_new_project_menu_item   = f2__gtk__menu_item__new(cause, new__string(cause, "New Project..."));
  f2ptr file_open_project_menu_item  = f2__gtk__menu_item__new(cause, new__string(cause, "Open Project..."));
  f2ptr file_close_project_menu_item = f2__gtk__menu_item__new(cause, new__string(cause, "Close Project..."));
  f2ptr file_save_project_menu_item  = f2__gtk__menu_item__new(cause, new__string(cause, "Save Project..."));
  f2ptr file_exit_menu_item          = f2__gtk__menu_item__new(cause, new__string(cause, "Exit"));
  
  // main_window
  f2__gtk__window__set_title(cause, main_window, new__string(cause, "Mentality"));
  f2__gtk__window__set_default_size(cause, main_window, f2integer__new(cause, 800), f2integer__new(cause, 600));
  f2__gtk__widget__connect_hide_on_delete(cause, main_window);
  
  // menu_bar_vbox
  f2__gtk__container__add(cause, main_window, menu_bar_vbox);
  
  // menu_bar
  f2__gtk__box__pack_start(cause, menu_bar_vbox, menu_bar, nil, nil, f2integer__new(cause, 0));
  
  // file_menu_item
  f2__gtk__menu_bar__append(cause, menu_bar, file_menu_item);
  
  // file_menu
  f2__gtk__menu_item__set_submenu(cause, file_menu_item, file_menu);
  
  // file_new_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_new_project_menu_item);
  
  // file_open_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_open_project_menu_item);
  
  // file_close_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_close_project_menu_item);
  
  // file_save_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_save_project_menu_item);
  
  // file_exit_menu_item
  f2__gtk__menu__append(cause, file_menu, file_exit_menu_item);
  
  
  f2__gtk__widget__show_all(cause, main_window);
  
  f2ptr current_project = nil;
  return raw__mentality__new(cause,
			     main_window,
			     menu_bar_vbox,
			     menu_bar,
			     file_menu_item,
			     file_menu,
			     file_new_project_menu_item,
			     file_open_project_menu_item,
			     file_close_project_menu_item,
			     file_save_project_menu_item,
			     file_exit_menu_item,
			     current_project);
}
export_cefunk0(mentality__new, 0, "Returns a new mentality object.");


// **

f2ptr f2__mentality__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(mentality__core_extension_ping, 0, "");

f2ptr f2__mentality__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "mentality_project"), f2__mentality_project_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "mentality"),         f2__mentality_type__new(cause));
  status("mentality initialized.");
  return nil;
}
export_cefunk0(mentality__core_extension_initialize, 0, "");

f2ptr f2__mentality__core_extension_destroy(f2ptr cause) {
  status("mentality destroyed.");
  return nil;
}
export_cefunk0(mentality__core_extension_destroy, 0, "");


