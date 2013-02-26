// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#ifndef F2__CORE_EXTENSION_FUNK__TYPES__H
#define F2__CORE_EXTENSION_FUNK__TYPES__H

// core_extension_funk

typedef struct funk2_object_type__core_extension_funk__slot_s funk2_object_type__core_extension_funk__slot_t;
struct funk2_object_type__core_extension_funk__slot_s {
  f2ptr pointer__symbol;
  f2ptr pointer__funk;
  f2ptr env__symbol;
  f2ptr env__funk;
  f2ptr cfunk__symbol;
  f2ptr cfunk__funk;
  f2ptr apply_without_initializing__symbol;
  f2ptr apply_without_initializing__funk;
  f2ptr apply__symbol;
  f2ptr apply__funk;
  f2ptr args_pointer__symbol;
  f2ptr args_pointer__funk;
  f2ptr args_cfunk__symbol;
  f2ptr args_cfunk__funk;
  f2ptr args__symbol;
  f2ptr args__funk;
  f2ptr is_funktional_pointer__symbol;
  f2ptr is_funktional_pointer__funk;
  f2ptr is_funktional_cfunk__symbol;
  f2ptr is_funktional_cfunk__funk;
  f2ptr is_funktional__symbol;
  f2ptr is_funktional__funk;
  f2ptr documentation_pointer__symbol;
  f2ptr documentation_pointer__funk;
  f2ptr documentation_cfunk__symbol;
  f2ptr documentation_cfunk__funk;
  f2ptr documentation__symbol;
  f2ptr documentation__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
};

#endif // F2__CORE_EXTENSION_FUNK__TYPES__H

#ifndef F2__CORE_EXTENSION_FUNK__H
#define F2__CORE_EXTENSION_FUNK__H

#include "f2_primfunks.h"


#define def_basic_cefunk_define_args(name, define_correct_arg_num, define_args, body) \
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


#define def_basic_cefunk_define_arg_iter(name, arg_name)		\
  if (simple_args_iter == nil) {return f2__argument_number_check_failure__larva__new(cause, new__symbol(cause, #name), correct_arg_num, simple_args);} \
  if (! raw__cons__is_type(cause, simple_args_iter)) {return f2larva__new(cause, 1, nil);} \
  f2ptr arg_name = f2cons__car(simple_args_iter, cause);		\
  simple_args_iter = f2cons__cdr(simple_args_iter, cause)

#define def_basic_cefunk_define_arg_and_rest(name, arg_name)		\
  if ((simple_args_iter != nil) && (! raw__cons__is_type(cause, simple_args_iter))) {return f2larva__new(cause, 1, nil);} \
  f2ptr arg_name = simple_args_iter;					\
  simple_args_iter = nil


#define def_basic_cefunk_define_arg0_iter(name)

#define def_basic_cefunk_define_arg0_and_rest(name, and_rest)	\
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg1_iter(name, arg1)	\
  def_basic_cefunk_define_arg0_iter(name);		\
  def_basic_cefunk_define_arg_iter(name, arg1)

#define def_basic_cefunk_define_arg1_and_rest(name, arg1, and_rest)	\
  def_basic_cefunk_define_arg1_iter(name, arg1);			\
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg2_iter(name, arg1, arg2)	\
  def_basic_cefunk_define_arg1_iter(name, arg1);		\
  def_basic_cefunk_define_arg_iter(name, arg2)

#define def_basic_cefunk_define_arg2_and_rest(name, arg1, arg2, and_rest) \
  def_basic_cefunk_define_arg2_iter(name, arg1, arg2);			\
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg3_iter(name, arg1, arg2, arg3)	\
  def_basic_cefunk_define_arg2_iter(name, arg1, arg2);			\
  def_basic_cefunk_define_arg_iter(name, arg3)

#define def_basic_cefunk_define_arg3_and_rest(name, arg1, arg2, arg3, and_rest)	\
  def_basic_cefunk_define_arg3_iter(name, arg1, arg2, arg3);		\
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg4_iter(name, arg1, arg2, arg3, arg4)	\
  def_basic_cefunk_define_arg3_iter(name, arg1, arg2, arg3);		\
  def_basic_cefunk_define_arg_iter(name, arg4)

#define def_basic_cefunk_define_arg4_and_rest(name, arg1, arg2, arg3, arg4, and_rest) \
  def_basic_cefunk_define_arg4_iter(name, arg1, arg2, arg3, arg4);	\
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg5_iter(name, arg1, arg2, arg3, arg4, arg5) \
  def_basic_cefunk_define_arg4_iter(name, arg1, arg2, arg3, arg4);	\
  def_basic_cefunk_define_arg_iter(name, arg5)

#define def_basic_cefunk_define_arg5_and_rest(name, arg1, arg2, arg3, arg4, arg5, and_rest) \
  def_basic_cefunk_define_arg5_iter(name, arg1, arg2, arg3, arg4, arg5); \
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg6_iter(name, arg1, arg2, arg3, arg4, arg5, arg6) \
  def_basic_cefunk_define_arg5_iter(name, arg1, arg2, arg3, arg4, arg5); \
  def_basic_cefunk_define_arg_iter(name, arg6)

#define def_basic_cefunk_define_arg6_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, and_rest) \
  def_basic_cefunk_define_arg6_iter(name, arg1, arg2, arg3, arg4, arg5, arg6); \
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg7_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
  def_basic_cefunk_define_arg6_iter(name, arg1, arg2, arg3, arg4, arg5, arg6); \
  def_basic_cefunk_define_arg_iter(name, arg7)

#define def_basic_cefunk_define_arg7_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest) \
  def_basic_cefunk_define_arg7_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg8_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
  def_basic_cefunk_define_arg7_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
  def_basic_cefunk_define_arg_iter(name, arg8)

#define def_basic_cefunk_define_arg8_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest) \
  def_basic_cefunk_define_arg8_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg9_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
  def_basic_cefunk_define_arg8_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
  def_basic_cefunk_define_arg_iter(name, arg9)

#define def_basic_cefunk_define_arg9_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest) \
  def_basic_cefunk_define_arg9_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg10_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) \
  def_basic_cefunk_define_arg9_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
  def_basic_cefunk_define_arg_iter(name, arg10)

#define def_basic_cefunk_define_arg10_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest) \
  def_basic_cefunk_define_arg10_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); \
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg11_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) \
  def_basic_cefunk_define_arg10_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); \
  def_basic_cefunk_define_arg_iter(name, arg11)

#define def_basic_cefunk_define_arg11_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest) \
  def_basic_cefunk_define_arg11_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11); \
  def_basic_cefunk_define_arg_and_rest(name, and_rest)

#define def_basic_cefunk_define_arg12_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) \
  def_basic_cefunk_define_arg11_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11); \
  def_basic_cefunk_define_arg_iter(name, arg12)

#define def_basic_cefunk_define_arg12_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest) \
  def_basic_cefunk_define_arg12_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12); \
  def_basic_cefunk_define_arg_and_rest(name, and_rest)


#define def_basic_cefunk0(name, body)					\
  def_basic_cefunk_define_args(name, 0, def_basic_cefunk_define_arg0_iter(name), body);

#define def_basic_cefunk0_and_rest(name, and_rest, body)		\
  def_basic_cefunk_define_args(name, 0, def_basic_cefunk_define_arg0_and_rest(name, and_rest), body);

#define def_basic_cefunk1(name, arg1, body)				\
  def_basic_cefunk_define_args(name, 1, def_basic_cefunk_define_arg1_iter(name, arg1), body);

#define def_basic_cefunk1_and_rest(name, arg1, and_rest, body)		\
  def_basic_cefunk_define_args(name, 1, def_basic_cefunk_define_arg1_and_rest(name, arg1, and_rest), body);

#define def_basic_cefunk2(name, arg1, arg2, body)			\
  def_basic_cefunk_define_args(name, 2, def_basic_cefunk_define_arg2_iter(name, arg1, arg2), body);

#define def_basic_cefunk2_and_rest(name, arg1, arg2, and_rest, body)	\
  def_basic_cefunk_define_args(name, 2, def_basic_cefunk_define_arg2_and_rest(name, arg1, arg2, and_rest), body);

#define def_basic_cefunk3(name, arg1, arg2, arg3, body)			\
  def_basic_cefunk_define_args(name, 3, def_basic_cefunk_define_arg3_iter(name, arg1, arg2, arg3), body);

#define def_basic_cefunk3_and_rest(name, arg1, arg2, arg3, and_rest, body) \
  def_basic_cefunk_define_args(name, 3, def_basic_cefunk_define_arg3_and_rest(name, arg1, arg2, arg3, and_rest), body);

#define def_basic_cefunk4(name, arg1, arg2, arg3, arg4, body)		\
  def_basic_cefunk_define_args(name, 4, def_basic_cefunk_define_arg4_iter(name, arg1, arg2, arg3, arg4), body);

#define def_basic_cefunk4_and_rest(name, arg1, arg2, arg3, arg4, and_rest, body) \
  def_basic_cefunk_define_args(name, 4, def_basic_cefunk_define_arg4_and_rest(name, arg1, arg2, arg3, arg4, and_rest), body);

#define def_basic_cefunk5(name, arg1, arg2, arg3, arg4, arg5, body)	\
  def_basic_cefunk_define_args(name, 5, def_basic_cefunk_define_arg5_iter(name, arg1, arg2, arg3, arg4, arg5), body);

#define def_basic_cefunk5_and_rest(name, arg1, arg2, arg3, arg4, arg5, and_rest, body) \
  def_basic_cefunk_define_args(name, 5, def_basic_cefunk_define_arg5_and_rest(name, arg1, arg2, arg3, arg4, arg5, and_rest), body);

#define def_basic_cefunk6(name, arg1, arg2, arg3, arg4, arg5, arg6, body) \
  def_basic_cefunk_define_args(name, 6, def_basic_cefunk_define_arg6_iter(name, arg1, arg2, arg3, arg4, arg5, arg6), body);

#define def_basic_cefunk6_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, and_rest, body) \
  def_basic_cefunk_define_args(name, 6, def_basic_cefunk_define_arg6_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, and_rest), body);

#define def_basic_cefunk7(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, body) \
  def_basic_cefunk_define_args(name, 7, def_basic_cefunk_define_arg7_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7), body);

#define def_basic_cefunk7_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest, body) \
  def_basic_cefunk_define_args(name, 7, def_basic_cefunk_define_arg7_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest), body);

#define def_basic_cefunk8(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, body) \
  def_basic_cefunk_define_args(name, 8, def_basic_cefunk_define_arg8_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8), body);

#define def_basic_cefunk8_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest, body) \
  def_basic_cefunk_define_args(name, 8, def_basic_cefunk_define_arg8_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest), body);

#define def_basic_cefunk9(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, body) \
  def_basic_cefunk_define_args(name, 9, def_basic_cefunk_define_arg9_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9), body);

#define def_basic_cefunk9_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest, body) \
  def_basic_cefunk_define_args(name, 9, def_basic_cefunk_define_arg9_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest), body);

#define def_basic_cefunk10(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, body) \
  def_basic_cefunk_define_args(name, 10, def_basic_cefunk_define_arg10_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10), body);

#define def_basic_cefunk10_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest, body) \
  def_basic_cefunk_define_args(name, 10, def_basic_cefunk_define_arg10_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest), body);

#define def_basic_cefunk11(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, body) \
  def_basic_cefunk_define_args(name, 11, def_basic_cefunk_define_arg11_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11), body);

#define def_basic_cefunk11_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest, body) \
  def_basic_cefunk_define_args(name, 11, def_basic_cefunk_define_arg11_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest), body);

#define def_basic_cefunk12(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, body) \
  def_basic_cefunk_define_args(name, 12, def_basic_cefunk_define_arg12_iter(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12), body);

#define def_basic_cefunk12_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest, body) \
  def_basic_cefunk_define_args(name, 12, def_basic_cefunk_define_arg12_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest), body);


#define export_basic_cefunk0(name)           def_basic_cefunk0(name,	\
							       return f2__##name(cause));

#define export_basic_cefunk0_and_rest(name)  def_basic_cefunk0_and_rest(name, and_rest, \
									return f2__##name(cause, and_rest));

#define export_basic_cefunk1(name)           def_basic_cefunk1(name, arg1, \
							       return f2__##name(cause, arg1));

#define export_basic_cefunk1_and_rest(name)  def_basic_cefunk1_and_rest(name, arg1, and_rest, \
									return f2__##name(cause, arg1, and_rest));

#define export_basic_cefunk2(name)           def_basic_cefunk2(name, arg1, arg2, \
							       return f2__##name(cause, arg1, arg2));

#define export_basic_cefunk2_and_rest(name)  def_basic_cefunk2_and_rest(name, arg1, arg2, and_rest, \
									return f2__##name(cause, arg1, arg2, and_rest));

#define export_basic_cefunk3(name)           def_basic_cefunk3(name, arg1, arg2, arg3, \
							       return f2__##name(cause, arg1, arg2, arg3));

#define export_basic_cefunk3_and_rest(name)  def_basic_cefunk3_and_rest(name, arg1, arg2, arg3, and_rest, \
									return f2__##name(cause, arg1, arg2, arg3, and_rest));

#define export_basic_cefunk4(name)           def_basic_cefunk4(name, arg1, arg2, arg3, arg4, \
							       return f2__##name(cause, arg1, arg2, arg3, arg4));

#define export_basic_cefunk4_and_rest(name)  def_basic_cefunk4_and_rest(name, arg1, arg2, arg3, arg4, and_rest, \
									return f2__##name(cause, arg1, arg2, arg3, arg4, and_rest));

#define export_basic_cefunk5(name)           def_basic_cefunk5(name, arg1, arg2, arg3, arg4, arg5, \
							       return f2__##name(cause, arg1, arg2, arg3, arg4, arg5));

#define export_basic_cefunk5_and_rest(name)  def_basic_cefunk5_and_rest(name, arg1, arg2, arg3, arg4, arg5, and_rest, \
									return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, and_rest));

#define export_basic_cefunk6(name)           def_basic_cefunk6(name, arg1, arg2, arg3, arg4, arg5, arg6, \
							       return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6));

#define export_basic_cefunk6_and_rest(name)  def_basic_cefunk6_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, and_rest, \
									return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, and_rest));

#define export_basic_cefunk7(name)           def_basic_cefunk7(name, arg1, arg2, arg3, arg4, arg5, arg6,	arg7, \
							       return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7));

#define export_basic_cefunk7_and_rest(name)  def_basic_cefunk7_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest, \
									return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest));

#define export_basic_cefunk8(name)           def_basic_cefunk8(name, arg1, arg2, arg3, arg4, arg5, arg6,	arg7, arg8, \
							       return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8));

#define export_basic_cefunk8_and_rest(name)  def_basic_cefunk8_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest, \
									return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest));

#define export_basic_cefunk9(name)           def_basic_cefunk9(name, arg1, arg2, arg3, arg4, arg5, arg6,	arg7, arg8, arg9, \
							       return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9));

#define export_basic_cefunk9_and_rest(name)  def_basic_cefunk9_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest, \
									return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest));

#define export_basic_cefunk10(name)          def_basic_cefunk10(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, \
								return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10));

#define export_basic_cefunk10_and_rest(name) def_basic_cefunk10_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest, \
									 return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest));

#define export_basic_cefunk11(name)          def_basic_cefunk11(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, \
								return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11));

#define export_basic_cefunk11_and_rest(name) def_basic_cefunk11_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest, \
									 return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest));

#define export_basic_cefunk12(name)          def_basic_cefunk12(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, \
								return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12));

#define export_basic_cefunk12_and_rest(name) def_basic_cefunk12_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest, \
									 return f2__##name(cause, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest));



#define def_cefunk0__args(name)				\
  f2ptr f2__##name##__args(f2ptr cause) {return nil;}

#define def_cefunk0_and_rest__args(name, and_rest)			\
  f2ptr f2__##name##__args(f2ptr cause) {return f2list2__new(cause, new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk1__args(name, arg1)					\
  f2ptr f2__##name##__args(f2ptr cause) {return f2list1__new(cause, new__symbol(cause, #arg1));}

#define def_cefunk1_and_rest__args(name, arg1, and_rest)		\
  f2ptr f2__##name##__args(f2ptr cause) {return f2list3__new(cause, new__symbol(cause, #arg1), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk2__args(name, arg1, arg2)				\
  f2ptr f2__##name##__args(f2ptr cause) {return f2list2__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2));}

#define def_cefunk2_and_rest__args(name, arg1, arg2, and_rest)		\
  f2ptr f2__##name##__args(f2ptr cause) {return f2list4__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk3__args(name, arg1, arg2, arg3)			\
  f2ptr f2__##name##__args(f2ptr cause) {return f2list3__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3));}

#define def_cefunk3_and_rest__args(name, arg1, arg2, arg3, and_rest)	\
  f2ptr f2__##name##__args(f2ptr cause) {return f2list5__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk4__args(name, arg1, arg2, arg3, arg4)			\
  f2ptr f2__##name##__args(f2ptr cause) {return f2list4__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4));}

#define def_cefunk4_and_rest__args(name, arg1, arg2, arg3, arg4, and_rest) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list5__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk5__args(name, arg1, arg2, arg3, arg4, arg5)		\
  f2ptr f2__##name##__args(f2ptr cause) {return f2list5__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5));}

#define def_cefunk5_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, and_rest) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list7__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk6__args(name, arg1, arg2, arg3, arg4, arg5, arg6)	\
  f2ptr f2__##name##__args(f2ptr cause) {return f2list6__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6));}

#define def_cefunk6_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, and_rest) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list8__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk7__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list7__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7));}

#define def_cefunk7_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list9__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk8__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list8__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, #arg8));}

#define def_cefunk8_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list10__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, #arg8), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk9__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list9__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, #arg8), new__symbol(cause, #arg9));}

#define def_cefunk9_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list11__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, #arg8), new__symbol(cause, #arg9), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk10__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list10__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, #arg8), new__symbol(cause, #arg9), new__symbol(cause, #arg10));}

#define def_cefunk10_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list12__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, #arg8), new__symbol(cause, #arg9), new__symbol(cause, #arg10), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk11__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list11__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, #arg8), new__symbol(cause, #arg9), new__symbol(cause, #arg10), new__symbol(cause, #arg11));}

#define def_cefunk11_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list13__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, #arg8), new__symbol(cause, #arg9), new__symbol(cause, #arg10), new__symbol(cause, #arg11), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}

#define def_cefunk12__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list12__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, #arg8), new__symbol(cause, #arg9), new__symbol(cause, #arg10), new__symbol(cause, #arg11), new__symbol(cause, #arg12));}

#define def_cefunk12_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest) \
  f2ptr f2__##name##__args(f2ptr cause) {return f2list14__new(cause, new__symbol(cause, #arg1), new__symbol(cause, #arg2), new__symbol(cause, #arg3), new__symbol(cause, #arg4), new__symbol(cause, #arg5), new__symbol(cause, #arg6), new__symbol(cause, #arg7), new__symbol(cause, #arg8), new__symbol(cause, #arg9), new__symbol(cause, #arg10), new__symbol(cause, #arg11), new__symbol(cause, #arg12), new__symbol(cause, ":rest"), new__symbol(cause, #and_rest));}


#define def_cefunk__is_funktional(name, is_funktional)			\
  f2ptr f2__##name##__is_funktional(f2ptr cause) {return f2bool__new(is_funktional);}


#define def_cefunk__documentation(name, documentation_string)		\
  f2ptr f2__##name##__documentation(f2ptr cause) {return new__string(cause, documentation_string);}



#define export_cefunk_without_args(name, is_funktional, documentation_string) \
  export_basic_cefunk0(name##__args);				  \
  def_cefunk__is_funktional(name, is_funktional)		  \
  export_basic_cefunk0(name##__is_funktional);			  \
  def_cefunk__documentation(name, documentation_string)		  \
  export_basic_cefunk0(name##__documentation);


#define export_cefunk0(name, is_funktional, documentation_string)	\
  export_basic_cefunk0(name);						\
  def_cefunk0__args(name)						\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk0_and_rest(name, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk0_and_rest(name);						\
  def_cefunk0_and_rest__args(name, and_rest)				\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk1(name, arg1, is_funktional, documentation_string)	\
  export_basic_cefunk1(name);						\
  def_cefunk1__args(name, arg1)						\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk1_and_rest(name, arg1, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk1_and_rest(name);						\
  def_cefunk2__args(name, arg1, arg2)					\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk2(name, arg1, arg2, is_funktional, documentation_string) \
  export_basic_cefunk2(name);						\
  def_cefunk2__args(name, arg1, arg2)					\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk2_and_rest(name, arg1, arg2, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk2_and_rest(name);					\
  def_cefunk2_and_rest__args(name, arg1, arg2, and_rest)		\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk3(name, arg1, arg2, arg3, is_funktional, documentation_string) \
  export_basic_cefunk3(name);						\
  def_cefunk3__args(name, arg1, arg2, arg3)				\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk3_and_rest(name, arg1, arg2, arg3, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk3_and_rest(name);					\
  def_cefunk3_and_rest__args(name, arg1, arg2, arg3, and_rest)		\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk4(name, arg1, arg2, arg3, arg4, is_funktional, documentation_string) \
  export_basic_cefunk4(name);						\
  def_cefunk4__args(name, arg1, arg2, arg3, arg4)			\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk4_and_rest(name, arg1, arg2, arg3, arg4, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk4_and_rest(name);					\
  def_cefunk4_and_rest__args(name, arg1, arg2, arg3, arg4, and_rest)	\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk5(name, arg1, arg2, arg3, arg4, arg5, is_funktional, documentation_string) \
  export_basic_cefunk5(name);						\
  def_cefunk5__args(name, arg1, arg2, arg3, arg4, arg5)			\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk5_and_rest(name, arg1, arg2, arg3, arg4, arg5, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk5_and_rest(name);					\
  def_cefunk5_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, and_rest) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk6(name, arg1, arg2, arg3, arg4, arg5, arg6, is_funktional, documentation_string) \
  export_basic_cefunk6(name);						\
  def_cefunk6__args(name, arg1, arg2, arg3, arg4, arg5, arg6)		\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk6_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk6_and_rest(name);					\
  def_cefunk6_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, and_rest) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk7(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, is_funktional, documentation_string) \
  export_basic_cefunk7(name);						\
  def_cefunk7__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7)	\
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk7_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk7_and_rest(name);					\
  def_cefunk7_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk8(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, is_funktional, documentation_string) \
  export_basic_cefunk8(name);						\
  def_cefunk8__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk8_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk8_and_rest(name);					\
  def_cefunk8_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk9(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, is_funktional, documentation_string) \
  export_basic_cefunk9(name);						\
  def_cefunk9__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk9_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk9_and_rest(name);					\
  def_cefunk9_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk10(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, is_funktional, documentation_string) \
  export_basic_cefunk10(name);						\
  def_cefunk10__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk10_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk10_and_rest(name);					\
  def_cefunk10_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk11(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, is_funktional, documentation_string) \
  export_basic_cefunk11(name);						\
  def_cefunk11__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk11_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk11_and_rest(name);					\
  def_cefunk11_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk12(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, is_funktional, documentation_string) \
  export_basic_cefunk12(name);						\
  def_cefunk12__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) \
  export_cefunk_without_args(name, is_funktional, documentation_string)

#define export_cefunk12_and_rest(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest, is_funktional, documentation_string) \
  export_basic_cefunk12_and_rest(name);					\
  def_cefunk12_and_rest__args(name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest) \
  export_cefunk_without_args(name, is_funktional, documentation_string)


declare_frame_object_8_slot(core_extension_funk,
			    core_extension_name,
			    name,
			    cname,
			    cfunk__cached,
			    cfunk__cached__time_stamp,
			    args_cname,
			    is_funktional_cname,
			    documentation_cname);

f2ptr raw__core_extension_funk__new(                       f2ptr cause, f2ptr filename, f2ptr name);
f2ptr  f2__core_extension_funk__new(                       f2ptr cause, f2ptr filename, f2ptr name);
f2ptr raw__core_extension_funk__pointer(                   f2ptr cause, f2ptr this);
f2ptr  f2__core_extension_funk__pointer(                   f2ptr cause, f2ptr this);
f2ptr raw__core_extension_funk__env(                       f2ptr cause, f2ptr this);
f2ptr  f2__core_extension_funk__env(                       f2ptr cause, f2ptr this);
f2ptr raw__core_extension_funk__cfunk(                     f2ptr cause, f2ptr this);
f2ptr  f2__core_extension_funk__cfunk(                     f2ptr cause, f2ptr this);
f2ptr raw__core_extension_funk__apply_without_initializing(f2ptr cause, f2ptr this, f2ptr args);
f2ptr  f2__core_extension_funk__apply_without_initializing(f2ptr cause, f2ptr this, f2ptr args);
f2ptr raw__core_extension_funk__apply(                     f2ptr cause, f2ptr this, f2ptr args);
f2ptr  f2__core_extension_funk__apply(                     f2ptr cause, f2ptr this, f2ptr args);
f2ptr raw__core_extension_funk__args_pointer(              f2ptr cause, f2ptr this);
f2ptr  f2__core_extension_funk__args_pointer(              f2ptr cause, f2ptr this);
f2ptr raw__core_extension_funk__args_cfunk(                f2ptr cause, f2ptr this);
f2ptr  f2__core_extension_funk__args_cfunk(                f2ptr cause, f2ptr this);
f2ptr raw__core_extension_funk__args(                      f2ptr cause, f2ptr this);
f2ptr  f2__core_extension_funk__args(                      f2ptr cause, f2ptr this);
f2ptr raw__core_extension_funk__is_funktional(             f2ptr cause, f2ptr this);
f2ptr  f2__core_extension_funk__is_funktional(             f2ptr cause, f2ptr this);
f2ptr raw__core_extension_funk__documentation(             f2ptr cause, f2ptr this);
f2ptr  f2__core_extension_funk__documentation(             f2ptr cause, f2ptr this);
f2ptr raw__core_extension_funk__terminal_print_with_frame( f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr  f2__core_extension_funk__terminal_print_with_frame( f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2core_extension_funk__primobject_type__new_aux(f2ptr cause);

#define new__core_extension_funk(cause, core_extension_name, name) f2__core_extension_funk__new(cause, new__symbol(cause, #core_extension_name), new__symbol(cause, #name))

#define core_extension_apply(cause, core_extension_name, name, args) f2__core_extension_funk__apply(cause, new__core_extension_funk(cause, core_extension_name, name), args)

// **

void f2__core_extension_funk__initialize();

#endif // F2__CORE_EXTENSION_FUNK__H

