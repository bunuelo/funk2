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

#ifndef F2__CORE_EXTENSION__TYPES__H
#define F2__CORE_EXTENSION__TYPES__H

// core_extension_funk

typedef struct funk2_object_type__core_extension_funk__slot_s funk2_object_type__core_extension_funk__slot_t;
struct funk2_object_type__core_extension_funk__slot_s {
  f2ptr pointer__symbol;
  f2ptr pointer__funk;
  f2ptr cfunk__symbol;
  f2ptr cfunk__funk;
  f2ptr apply__symbol;
  f2ptr apply__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
};

#endif // F2__CORE_EXTENSION__TYPES__H

#ifndef F2__CORE_EXTENSION__H
#define F2__CORE_EXTENSION__H

#include "f2_primfunks.h"


#define def_cefunk_define_args(name, define_correct_arg_num, define_args, body) \
  def_pcfunk__prototype__declare(core_extension_funk__##name) {		\
    f2ptr cause            = simple_cause;				\
    u64   correct_arg_num  = define_correct_arg_num;			\
    f2ptr simple_args_iter = simple_args;				\
    									\
    define_args;							\
    									\
    if (simple_args_iter != nil) {return f2__argument_number_check_failure__larva__new(cause, new__symbol(cause, #name), correct_arg_num, simple_args);} \
    {body;}								\
  }


#define def_cefunk_define_arg_iter(name, arg_name)			\
  if (simple_args_iter == nil) {return f2__argument_number_check_failure__larva__new(cause, new__symbol(cause, #name), correct_arg_num, simple_args);} \
  if (! raw__cons__is_type(cause, simple_args_iter)) {return f2larva__new(cause, 1, nil);} \
  f2ptr arg_name = f2cons__car(simple_args_iter, cause);		\
  simple_args_iter = f2cons__cdr(simple_args_iter, cause)


#define def_cefunk_define_arg0_iter(name)

#define def_cefunk_define_arg1_iter(name, arg1) \
  def_cefunk_define_arg0_iter(name);		\
  def_cefunk_define_arg_iter(name, arg1)

#define def_cefunk_define_arg2_iter(name, arg1, arg2)	\
  def_cefunk_define_arg1_iter(name, arg1);		\
  def_cefunk_define_arg_iter(name, arg2)

#define def_cefunk_define_arg3_iter(name, arg1, arg2, arg3)	\
  def_cefunk_define_arg2_iter(name, arg1, arg2);		\
  def_cefunk_define_arg_iter(name, arg3)

#define def_cefunk_define_arg4_iter(name, arg1, arg2, arg3, arg4)	\
  def_cefunk_define_arg3_iter(name, arg1, arg2, arg3);			\
  def_cefunk_define_arg_iter(name, arg4)


#define def_cefunk0(name, body)						\
  def_cefunk_define_args(name, 0, def_cefunk_define_arg0_iter(name), body);

#define def_cefunk1(name, arg1, body)					\
  def_cefunk_define_args(name, 1, def_cefunk_define_arg1_iter(name, arg1), body);

#define def_cefunk2(name, arg1, arg2, body)				\
  def_cefunk_define_args(name, 2, def_cefunk_define_arg2_iter(name, arg1, arg2), body);

#define def_cefunk3(name, arg1, arg2, arg3, body)			\
  def_cefunk_define_args(name, 3, def_cefunk_define_arg3_iter(name, arg1, arg2, arg3), body);

#define def_cefunk4(name, arg1, arg2, arg3, arg4, body)			\
  def_cefunk_define_args(name, 4, def_cefunk_define_arg4_iter(name, arg1, arg2, arg3, arg4), body);


#define export_cefunk0(name) def_cefunk0(name, \
					 return f2__##name(cause));

#define export_cefunk1(name) def_cefunk1(name, arg1, \
					 return f2__##name(cause, arg1));

#define export_cefunk2(name) def_cefunk2(name, arg1, arg2, \
					 return f2__##name(cause, arg1, arg2));

#define export_cefunk3(name) def_cefunk3(name, arg1, arg2, arg3, \
					 return f2__##name(cause, arg1, arg2, arg3));

#define export_cefunk4(name) def_cefunk4(name, arg1, arg2, arg3, arg4,	\
					 return f2__##name(cause, arg1, arg2, arg3, arg4));


declare_frame_object_6_slot(core_extension_funk, filename, name, args, env, is_funktional, documentation);

f2ptr f2core_extension_funk__primobject_type__new_aux(f2ptr cause);


// **

void f2__core_extension__initialize();

#endif // F2__CORE_EXTENSION__H

