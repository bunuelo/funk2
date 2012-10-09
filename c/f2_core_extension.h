// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#ifndef F2__CORE_EXTENSION__TYPES__H
#define F2__CORE_EXTENSION__TYPES__H

// core_extension

typedef struct funk2_object_type__core_extension__slot_s funk2_object_type__core_extension__slot_t;
struct funk2_object_type__core_extension__slot_s {
  f2ptr initialize__symbol;
  f2ptr initialize__funk;
  f2ptr destroy__symbol;
  f2ptr destroy__funk;
  f2ptr assure_initialized__symbol;
  f2ptr assure_initialized__funk;
  f2ptr assure_destroyed__symbol;
  f2ptr assure_destroyed__funk;
  f2ptr changed_on_disk__symbol;
  f2ptr changed_on_disk__funk;
};

// core_extension_handler

typedef struct funk2_object_type__core_extension_handler__slot_s funk2_object_type__core_extension_handler__slot_t;
struct funk2_object_type__core_extension_handler__slot_s {
  f2ptr add_new_core_extension__symbol;
  f2ptr add_new_core_extension__funk;
  f2ptr lookup_core_extension__symbol;
  f2ptr lookup_core_extension__funk;
  f2ptr unload_changed__symbol;
  f2ptr unload_changed__funk;
  f2ptr reset_to_boot_state__symbol;
  f2ptr reset_to_boot_state__funk;
};

#endif // F2__CORE_EXTENSION__TYPES__H

#ifndef F2__CORE_EXTENSION__H
#define F2__CORE_EXTENSION__H

#include "f2_primfunks.h"

// def_header_ceframe

#define def_header_ceframe__new0(name)		\
  f2ptr f2##name##__new(f2ptr cause);

#define def_header_ceframe__new1(name, slot1)		\
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1);

#define def_header_ceframe__new2(name, slot1, slot2)		\
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2);

#define def_header_ceframe__new3(name, slot1, slot2, slot3)		\
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3);

#define def_header_ceframe__new4(name, slot1, slot2, slot3, slot4)		\
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4);

#define def_header_ceframe__new5(name, slot1, slot2, slot3, slot4, slot5)	\
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5);

#define def_header_ceframe__new6(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6);

#define def_header_ceframe__new7(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7);

#define def_header_ceframe__new8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8);

#define def_header_ceframe__new9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9);

#define def_header_ceframe__new10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10);

#define def_header_ceframe__new11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10, f2ptr slot11);

#define def_header_ceframe__new12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10, f2ptr slot11, f2ptr slot12);

#define def_header_ceframe__new13(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10, f2ptr slot11, f2ptr slot12, f2ptr slot13);

#define def_header_ceframe__new14(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10, f2ptr slot11, f2ptr slot12, f2ptr slot13, f2ptr slot14);



#define def_header_ceframe__common(name)				\
  boolean_t raw__##name##__is_type(f2ptr cause, f2ptr thing);		\
  f2ptr      f2__##name##__is_type(f2ptr cause, f2ptr thing);		\
  f2ptr     raw__##name##__type   (f2ptr cause, f2ptr this);		\
  f2ptr      f2__##name##__type   (f2ptr cause, f2ptr this);		\
  									\
  f2ptr f2__##name##_type__new(f2ptr cause);


#define def_header_ceframe__slot(name, slot)				\
  f2ptr raw__##name##__##slot       (f2ptr cause, f2ptr this);		\
  f2ptr  f2__##name##__##slot       (f2ptr cause, f2ptr this);		\
  f2ptr raw__##name##__##slot##__set(f2ptr cause, f2ptr this, f2ptr slot); \
  f2ptr  f2__##name##__##slot##__set(f2ptr cause, f2ptr this, f2ptr slot);


#define def_header_ceframe__slot0(name)

#define def_header_ceframe__slot1(name, slot1)	\
  def_header_ceframe__slot0(name)		\
  def_header_ceframe__slot(name, slot1)

#define def_header_ceframe__slot2(name, slot1, slot2)		\
  def_header_ceframe__slot1(name, slot1)			\
  def_header_ceframe__slot(name, slot2)

#define def_header_ceframe__slot3(name, slot1, slot2, slot3)	\
  def_header_ceframe__slot2(name, slot1, slot2)			\
  def_header_ceframe__slot(name, slot3)

#define def_header_ceframe__slot4(name, slot1, slot2, slot3, slot4)	\
  def_header_ceframe__slot3(name, slot1, slot2, slot3)			\
  def_header_ceframe__slot(name, slot4)

#define def_header_ceframe__slot5(name, slot1, slot2, slot3, slot4, slot5) \
  def_header_ceframe__slot4(name, slot1, slot2, slot3, slot4)		\
  def_header_ceframe__slot(name, slot5)

#define def_header_ceframe__slot6(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_header_ceframe__slot5(name, slot1, slot2, slot3, slot4, slot5)	\
  def_header_ceframe__slot(name, slot6)

#define def_header_ceframe__slot7(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_header_ceframe__slot6(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_header_ceframe__slot(name, slot7)

#define def_header_ceframe__slot8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_header_ceframe__slot7(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_header_ceframe__slot(name, slot8)

#define def_header_ceframe__slot9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_header_ceframe__slot8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_header_ceframe__slot(name, slot9)

#define def_header_ceframe__slot10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_header_ceframe__slot9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_header_ceframe__slot(name, slot10)

#define def_header_ceframe__slot11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_header_ceframe__slot10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_header_ceframe__slot(name, slot11)

#define def_header_ceframe__slot12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_header_ceframe__slot11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_header_ceframe__slot(name, slot12)

#define def_header_ceframe__slot13(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_header_ceframe__slot12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_header_ceframe__slot(name, slot13)

#define def_header_ceframe__slot14(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  def_header_ceframe__slot13(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_header_ceframe__slot(name, slot14)


#define def_header_ceframe0(name)		\
  def_header_ceframe__new0(name)		\
  def_header_ceframe__common(name)		\
  def_header_ceframe__slot0(name)

#define def_header_ceframe1(name, slot1)	\
  def_header_ceframe__new1(name, slot1)		\
  def_header_ceframe__common(name)		\
  def_header_ceframe__slot1(name, slot1)

#define def_header_ceframe2(name, slot1, slot2)	\
  def_header_ceframe__new2(name, slot1, slot2)	\
  def_header_ceframe__common(name)		\
  def_header_ceframe__slot2(name, slot1, slot2)

#define def_header_ceframe3(name, slot1, slot2, slot3)	\
  def_header_ceframe__new3(name, slot1, slot2, slot3)	\
  def_header_ceframe__common(name)			\
  def_header_ceframe__slot3(name, slot1, slot2, slot3)

#define def_header_ceframe4(name, slot1, slot2, slot3, slot4)		\
  def_header_ceframe__new4(name, slot1, slot2, slot3, slot4)		\
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot4(name, slot1, slot2, slot3, slot4)

#define def_header_ceframe5(name, slot1, slot2, slot3, slot4, slot5)	\
  def_header_ceframe__new5(name, slot1, slot2, slot3, slot4, slot5)	\
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot5(name, slot1, slot2, slot3, slot4, slot5)

#define def_header_ceframe6(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_header_ceframe__new6(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot6(name, slot1, slot2, slot3, slot4, slot5, slot6)

#define def_header_ceframe7(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_header_ceframe__new7(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot7(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7)

#define def_header_ceframe8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_header_ceframe__new8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8)

#define def_header_ceframe9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_header_ceframe__new9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9)

#define def_header_ceframe10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_header_ceframe__new10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10)

#define def_header_ceframe11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_header_ceframe__new11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11)

#define def_header_ceframe12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_header_ceframe__new12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12)

#define def_header_ceframe13(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_header_ceframe__new13(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot13(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13)

#define def_header_ceframe14(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  def_header_ceframe__new14(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  def_header_ceframe__common(name)					\
  def_header_ceframe__slot14(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14)






// def_ceframe

#define def_ceframe__new__common(name, slot_defs)			\
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

#define def_ceframe__new__arg13(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_ceframe__new__arg12(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12); \
  def_ceframe__new__arg(slot13)

#define def_ceframe__new__arg14(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  def_ceframe__new__arg13(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13); \
  def_ceframe__new__arg(slot14)


#define def_ceframe0__new(name)					\
  f2ptr f2##name##__new(f2ptr cause) {				\
    def_ceframe__new__common(name, ); }

#define def_ceframe1__new(name, slot1)					\
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1) {			\
    def_ceframe__new__common(name, def_ceframe__new__arg1(slot1)); }

#define def_ceframe2__new(name, slot1, slot2)				\
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2) {	\
    def_ceframe__new__common(name, def_ceframe__new__arg2(slot1, slot2)); }

#define def_ceframe3__new(name, slot1, slot2, slot3)			\
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3) { \
    def_ceframe__new__common(name, def_ceframe__new__arg3(slot1, slot2, slot3)); }

#define def_ceframe4__new(name, slot1, slot2, slot3, slot4)		\
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4) { \
    def_ceframe__new__common(name, def_ceframe__new__arg4(slot1, slot2, slot3, slot4)); }

#define def_ceframe5__new(name, slot1, slot2, slot3, slot4, slot5)	\
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5) { \
    def_ceframe__new__common(name, def_ceframe__new__arg5(slot1, slot2, slot3, slot4, slot5)); }

#define def_ceframe6__new(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6) { \
    def_ceframe__new__common(name, def_ceframe__new__arg6(slot1, slot2, slot3, slot4, slot5, slot6)); }

#define def_ceframe7__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7) { \
    def_ceframe__new__common(name, def_ceframe__new__arg7(slot1, slot2, slot3, slot4, slot5, slot6, slot7)); }

#define def_ceframe8__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8) { \
    def_ceframe__new__common(name, def_ceframe__new__arg8(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8)); }

#define def_ceframe9__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9) { \
    def_ceframe__new__common(name, def_ceframe__new__arg9(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9)); }

#define def_ceframe10__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10) { \
    def_ceframe__new__common(name, def_ceframe__new__arg10(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10)); }

#define def_ceframe11__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10, f2ptr slot11) { \
    def_ceframe__new__common(name, def_ceframe__new__arg11(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11)); }

#define def_ceframe12__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10, f2ptr slot11, f2ptr slot12) { \
    def_ceframe__new__common(name, def_ceframe__new__arg12(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12)); }

#define def_ceframe13__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10, f2ptr slot11, f2ptr slot12, f2ptr slot13) { \
    def_ceframe__new__common(name, def_ceframe__new__arg13(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13)); }

#define def_ceframe14__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot1, f2ptr slot2, f2ptr slot3, f2ptr slot4, f2ptr slot5, f2ptr slot6, f2ptr slot7, f2ptr slot8, f2ptr slot9, f2ptr slot10, f2ptr slot11, f2ptr slot12, f2ptr slot13, f2ptr slot14) { \
    def_ceframe__new__common(name, def_ceframe__new__arg14(slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14)); }


#define core_extension__primobject_type__add_funk(core_extension_name, object_type, funk_type, funk_name, seaside_funk_name) { \
    f2__primobject_type__add_slot_type(cause, this,			\
				       new__symbol(cause, funk_type),	\
				       new__symbol(cause, funk_name),	\
				       f2__core_extension_funk__new(cause, \
								    new__symbol(cause, core_extension_name), \
								    new__symbol(cause, object_type "__" seaside_funk_name))); \
  }


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
    assert_argument_type(name, this);					\
    return raw__##name##__type(cause, this);				\
  }									\
  export_cefunk1(name##__type, thing, 0, "Returns the specific type of object that this " #name " is.");



#define def_ceframe__slot_funk(name, slot)				\
  f2ptr raw__##name##__##slot(f2ptr cause, f2ptr this) {		\
    return f2__frame__lookup_var_value(cause, this, new__symbol(cause, #slot), nil); \
  }									\
  									\
  f2ptr f2__##name##__##slot(f2ptr cause, f2ptr this) {			\
    assert_argument_type(name, this);					\
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
    assert_argument_type(name, this);					\
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
  def_ceframe__slot_funk5(name, slot1, slot2, slot3, slot4, slot5)	\
  def_ceframe__slot_funk(name, slot6)

#define def_ceframe__slot_funk7(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_ceframe__slot_funk6(name, slot1, slot2, slot3, slot4, slot5, slot6) \
  def_ceframe__slot_funk(name, slot7)

#define def_ceframe__slot_funk8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_ceframe__slot_funk7(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7) \
  def_ceframe__slot_funk(name, slot8)

#define def_ceframe__slot_funk9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_ceframe__slot_funk8(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8) \
  def_ceframe__slot_funk(name, slot9)

#define def_ceframe__slot_funk10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_ceframe__slot_funk9(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9) \
  def_ceframe__slot_funk(name, slot10)

#define def_ceframe__slot_funk11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_ceframe__slot_funk10(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10) \
  def_ceframe__slot_funk(name, slot11)

#define def_ceframe__slot_funk12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_ceframe__slot_funk11(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11) \
  def_ceframe__slot_funk(name, slot12)

#define def_ceframe__slot_funk13(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_ceframe__slot_funk12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_ceframe__slot_funk(name, slot13)

#define def_ceframe__slot_funk14(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  def_ceframe__slot_funk13(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_ceframe__slot_funk(name, slot14)



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

#define def_ceframe__primobject_type__new__slot13(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_ceframe__primobject_type__new__slot12(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_ceframe__primobject_type__new__slot(extension_name, name, slot13)

#define def_ceframe__primobject_type__new__slot14(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  def_ceframe__primobject_type__new__slot13(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_ceframe__primobject_type__new__slot(extension_name, name, slot14)


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

#define def_ceframe13__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot13(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13))

#define def_ceframe14__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  def_ceframe__primobject_type__new__common(extension_name, name, def_ceframe__primobject_type__new__slot14(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14))



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

#define def_ceframe12(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_ceframe12__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12); \
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk12(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12) \
  def_ceframe12__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12)

#define def_ceframe13(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_ceframe13__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13); \
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk13(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13) \
  def_ceframe13__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13)

#define def_ceframe14(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  def_ceframe14__new(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14); \
  def_ceframe__is_type(name);						\
  def_ceframe__type(name);						\
  def_ceframe__slot_funk14(name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14) \
  def_ceframe14__primobject_type__new(extension_name, name, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8, slot9, slot10, slot11, slot12, slot13, slot14)



// --

#define core_extension__ping(this_core_extension_name, core_extension_name) {	\
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, #core_extension_name), new__symbol(cause, #core_extension_name "__core_extension__ping")), nil); \
    if (raw__larva__is_type(cause, result)) {				\
      status(#this_core_extension_name ": failed to ping " #core_extension_name "."); \
      return result;							\
    }									\
  }



// core_extension

declare_frame_object_4_slot(core_extension,
			    name,
			    filename,
			    initialized_time_stamp_cmutex,
			    initialized_time_stamp);

f2ptr raw__core_extension__new(               f2ptr cause, f2ptr name, f2ptr filename);
f2ptr  f2__core_extension__new(               f2ptr cause, f2ptr name, f2ptr filename);
f2ptr raw__core_extension__initialize(        f2ptr cause, f2ptr this);
f2ptr  f2__core_extension__initialize(        f2ptr cause, f2ptr this);
f2ptr raw__core_extension__destroy(           f2ptr cause, f2ptr this);
f2ptr  f2__core_extension__destroy(           f2ptr cause, f2ptr this);
f2ptr raw__core_extension__assure_initialized(f2ptr cause, f2ptr this);
f2ptr  f2__core_extension__assure_initialized(f2ptr cause, f2ptr this);

f2ptr f2core_extension__primobject_type__new_aux(f2ptr cause);


// core_extension_handler

declare_frame_object_1_slot(core_extension_handler, core_extension_name_hash);

f2ptr raw__core_extension_handler__new(                   f2ptr cause);
f2ptr  f2__core_extension_handler__new(                   f2ptr cause);
f2ptr raw__core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr this, f2ptr name, f2ptr filename);
f2ptr  f2__core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr this, f2ptr name, f2ptr filename);
f2ptr raw__core_extension_handler__lookup_core_extension( f2ptr cause, f2ptr this, f2ptr name);
f2ptr  f2__core_extension_handler__lookup_core_extension( f2ptr cause, f2ptr this, f2ptr name);

f2ptr f2core_extension_handler__primobject_type__new_aux(f2ptr cause);


// global_core_extension_handler

f2ptr f2__global_core_extension_handler__reset_to_boot_state   (f2ptr cause);
f2ptr f2__global_core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr name, f2ptr filename);
f2ptr f2__global_core_extension_handler__lookup_core_extension (f2ptr cause, f2ptr name);

// **

void f2__core_extension__initialize_module();


#endif // F2__CORE_EXTENSION__H

