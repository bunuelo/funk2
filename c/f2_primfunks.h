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

#ifndef F2__PRIMCFUNKS__H
#define F2__PRIMCFUNKS__H

#include "f2_redblacktree.h"
#include "f2_processor_mutex.h"

#define def_pcfunk__funkvar(name)            pcfunk__##name
#define def_pcfunk__prototype__declare(name) f2ptr def_pcfunk__funkvar(name) (f2ptr simple_cause, f2ptr simple_fiber, f2ptr simple_env, f2ptr simple_args)

#define def_pcfunk__symbolvar(name)          __symbol__##name
#define def_pcfunk__symbolvar_string(name)   "primfunk:" #name
#define def_pcfunk__symbolvar__define(name)  f2ptr def_pcfunk__symbolvar(name) = nil
#define def_pcfunk__symbolvar__init(name)    def_pcfunk__symbolvar(name) = new__symbol(initial_cause(), def_pcfunk__symbolvar_string(name));
#define def_pcfunk__symbolvar__init__defragment__fix_pointers(name) {	\
    if(def_pcfunk__symbolvar(name) != nil) {				\
      def_pcfunk__symbolvar(name) = funk2_defragmenter__memory_pool__lookup_new_f2ptr(&(__funk2.defragmenter), def_pcfunk__symbolvar(name)); \
    }									\
  }
#define def_pcfunk__this_symbol__define(name)	    \
  f2ptr this_symbol = def_pcfunk__symbolvar(name);  \
  this_symbol = this_symbol;

#define def_pcfunk__documentation_variable(name)                     __documentation__##name
#define def_pcfunk__documentation_variable__define(name, doc_string) u8* def_pcfunk__documentation_variable(name) = (u8*)""
#define def_pcfunk__documentation_variable__init(name, doc_string)   {def_pcfunk__documentation_variable(name) = (u8*)(doc_string);}

#define def_pcfunk__is_funktional_variable(name)                     __is_funktional__##name
#define def_pcfunk__is_funktional_variable__define(name)             f2ptr def_pcfunk__is_funktional_variable(name) = nil
#define def_pcfunk__is_funktional_variable__init(name, doc_string)   def_pcfunk__is_funktional_variable(name) = f2string__new(initial_cause(), strlen(doc_string), (u8*)doc_string);
#define def_pcfunk__is_funktional_variable__init__defragment__fix_pointers(name) { \
    if(def_pcfunk__is_funktional_variable(name) != nil) {		\
      def_pcfunk__is_funktional_variable(name) = funk2_defragmenter__memory_pool__lookup_new_f2ptr(&(__funk2.defragmenter), def_pcfunk__is_funktional_variable(name)); \
    }									\
  }

#define def_pcfunk__has_side_effects_variable(name)                     __has_side_effects__##name
#define def_pcfunk__has_side_effects_variable__define(name)             f2ptr def_pcfunk__has_side_effects_variable(name) = nil
#define def_pcfunk__has_side_effects_variable__init(name, doc_string)   def_pcfunk__has_side_effects_variable(name) = f2string__new(initial_cause(), strlen(doc_string), (u8*)doc_string);
#define def_pcfunk__has_side_effects_variable__init__defragment__fix_pointers(name) { \
    if(def_pcfunk__has_side_effects_variable(name) != nil) {		\
      def_pcfunk__has_side_effects_variable(name) = funk2_defragmenter__memory_pool__lookup_new_f2ptr(&(__funk2.defragmenter), def_pcfunk__has_side_effects_variable(name)); \
    }									\
  }


#define PCFUNK__PROPOGATE_THIS_CAUSE
#ifdef  PCFUNK__PROPOGATE_THIS_CAUSE
#  define def_pcfunk__this_cause__define(name) \
     f2ptr this_cause = simple_cause; \
     this_cause = this_cause;
#else
#  define def_pcfunk__this_cause__define(name) \//
     f2ptr this_cause = nil; \//
     this_cause = this_cause;
#endif // PCFUNK__CREATE_THIS_CAUSE


#define def_pcfunk__defargs(def_name, correct_arg_num, defargs, doc_string, def_body) \
  def_pcfunk__symbolvar__define(def_name);				\
  def_pcfunk__documentation_variable__define(def_name, doc_string);	\
  def_pcfunk__is_funktional_variable__define(def_name);			\
  def_pcfunk__has_side_effects_variable__define(def_name);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    f2ptr simple_args__iter = simple_args;				\
    defargs;								\
    if (simple_args__iter != nil) {					\
      return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, correct_arg_num, simple_args); \
    }									\
    def_body;								\
  }

#define def_pcfunk__argument(correct_arg_num, var)			\
  if (! raw__cons__is_type(this_cause, simple_args__iter)) {		\
    return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, correct_arg_num, simple_args); \
  }									\
  f2ptr var         = f2cons__car(simple_args__iter, this_cause);	\
  simple_args__iter = f2cons__cdr(simple_args__iter, this_cause)

#define def_pcfunk__argument__1_slot(correct_arg_num, var1) \
  def_pcfunk__argument(correct_arg_num, var1)

#define def_pcfunk__argument__2_slot(correct_arg_num, var1, var2)	\
  def_pcfunk__argument__1_slot(correct_arg_num, var1);			\
  def_pcfunk__argument(correct_arg_num, var2)

#define def_pcfunk__argument__3_slot(correct_arg_num, var1, var2, var3)	\
  def_pcfunk__argument__2_slot(correct_arg_num, var1, var2);		\
  def_pcfunk__argument(correct_arg_num, var3)

#define def_pcfunk__argument__4_slot(correct_arg_num, var1, var2, var3, var4) \
  def_pcfunk__argument__3_slot(correct_arg_num, var1, var2, var3);	\
  def_pcfunk__argument(correct_arg_num, var4)

#define def_pcfunk__argument__5_slot(correct_arg_num, var1, var2, var3, var4, var5) \
  def_pcfunk__argument__4_slot(correct_arg_num, var1, var2, var3, var4); \
  def_pcfunk__argument(correct_arg_num, var5)

#define def_pcfunk__argument__6_slot(correct_arg_num, var1, var2, var3, var4, var5, var6) \
  def_pcfunk__argument__5_slot(correct_arg_num, var1, var2, var3, var4, var5); \
  def_pcfunk__argument(correct_arg_num, var6)

#define def_pcfunk__argument__7_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7) \
  def_pcfunk__argument__6_slot(correct_arg_num, var1, var2, var3, var4, var5, var6); \
  def_pcfunk__argument(correct_arg_num, var7)

#define def_pcfunk__argument__8_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8) \
  def_pcfunk__argument__7_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7); \
  def_pcfunk__argument(correct_arg_num, var8)

#define def_pcfunk__argument__9_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9) \
  def_pcfunk__argument__8_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8); \
  def_pcfunk__argument(correct_arg_num, var9)

#define def_pcfunk__argument__10_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10) \
  def_pcfunk__argument__9_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9); \
  def_pcfunk__argument(correct_arg_num, var10)

#define def_pcfunk__argument__11_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11) \
  def_pcfunk__argument__10_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10); \
  def_pcfunk__argument(correct_arg_num, var11)

#define def_pcfunk__argument__12_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12) \
  def_pcfunk__argument__11_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11); \
  def_pcfunk__argument(correct_arg_num, var12)

#define def_pcfunk__argument__13_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13) \
  def_pcfunk__argument__12_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12); \
  def_pcfunk__argument(correct_arg_num, var13)

#define def_pcfunk__argument__14_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14) \
  def_pcfunk__argument__13_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13); \
  def_pcfunk__argument(correct_arg_num, var14)

#define def_pcfunk__argument__15_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15) \
  def_pcfunk__argument__14_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14); \
  def_pcfunk__argument(correct_arg_num, var15)

#define def_pcfunk__argument__16_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16) \
  def_pcfunk__argument__15_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15); \
  def_pcfunk__argument(correct_arg_num, var16)

#define def_pcfunk__argument__17_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17) \
  def_pcfunk__argument__16_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16); \
  def_pcfunk__argument(correct_arg_num, var17)

#define def_pcfunk__argument__18_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18) \
  def_pcfunk__argument__17_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17); \
  def_pcfunk__argument(correct_arg_num, var18)

#define def_pcfunk__argument__19_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19) \
  def_pcfunk__argument__18_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18); \
  def_pcfunk__argument(correct_arg_num, var19)

#define def_pcfunk__argument__20_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20) \
  def_pcfunk__argument__19_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19); \
  def_pcfunk__argument(correct_arg_num, var20)

#define def_pcfunk__argument__21_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21) \
  def_pcfunk__argument__20_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20); \
  def_pcfunk__argument(correct_arg_num, var21)

#define def_pcfunk__argument__22_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22) \
  def_pcfunk__argument__21_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21); \
  def_pcfunk__argument(correct_arg_num, var22)

#define def_pcfunk__argument__23_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23) \
  def_pcfunk__argument__22_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22); \
  def_pcfunk__argument(correct_arg_num, var23)

#define def_pcfunk__argument__24_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24) \
  def_pcfunk__argument__23_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23); \
  def_pcfunk__argument(correct_arg_num, var24)

#define def_pcfunk__argument__25_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25) \
  def_pcfunk__argument__24_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24); \
  def_pcfunk__argument(correct_arg_num, var25)

#define def_pcfunk__argument__26_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25, var26) \
  def_pcfunk__argument__25_slot(correct_arg_num, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25); \
  def_pcfunk__argument(correct_arg_num, var26)



#define def_pcfunk0(def_name, doc_string, def_body)	\
  def_pcfunk__defargs(def_name, 0, , doc_string, def_body)

#define def_pcfunk0_and_rest(def_name, and_rest, doc_string, def_body)	\
  def_pcfunk__defargs(def_name, 0,					\
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string, \
		      def_body)

#define def_pcfunk1(def_name, var1, doc_string, def_body)				\
  def_pcfunk__defargs(def_name, 1,					\
		      def_pcfunk__argument__1_slot(1, var1),		\
		      doc_string,					\
		      def_body)

#define def_pcfunk1_and_rest(def_name, var1, and_rest, doc_string, def_body)	\
  def_pcfunk__defargs(def_name, 1,				\
		      def_pcfunk__argument__1_slot(1, var1);		\
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk2(def_name, var1, var2, doc_string, def_body)		\
  def_pcfunk__defargs(def_name, 2,					\
		      def_pcfunk__argument__2_slot(2, var1, var2),	\
		      doc_string,					\
		      def_body)

#define def_pcfunk2_and_rest(def_name, var1, var2, and_rest, doc_string, def_body)	\
  def_pcfunk__defargs(def_name, 2,					\
		      def_pcfunk__argument__2_slot(2, var1, var2);	\
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk3(def_name, var1, var2, var3, doc_string, def_body)		\
  def_pcfunk__defargs(def_name, 3,					\
		      def_pcfunk__argument__3_slot(3, var1, var2, var3), \
		      doc_string,					\
		      def_body)

#define def_pcfunk3_and_rest(def_name, var1, var2, var3, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 3,					\
		      def_pcfunk__argument__3_slot(3, var1, var2, var3); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk4(def_name, var1, var2, var3, var4, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 4,					\
		      def_pcfunk__argument__4_slot(4, var1, var2, var3, var4), \
		      doc_string,					\
		      def_body)

#define def_pcfunk4_and_rest(def_name, var1, var2, var3, var4, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 4,					\
		      def_pcfunk__argument__4_slot(4, var1, var2, var3, var4); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk5(def_name, var1, var2, var3, var4, var5, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 5,					\
		      def_pcfunk__argument__5_slot(5, var1, var2, var3, var4, var5), \
		      doc_string,					\
		      def_body)

#define def_pcfunk5_and_rest(def_name, var1, var2, var3, var4, var5, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 5,					\
		      def_pcfunk__argument__5_slot(5, var1, var2, var3, var4, var5); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk6(def_name, var1, var2, var3, var4, var5, var6, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 6,					\
		      def_pcfunk__argument__6_slot(6, var1, var2, var3, var4, var5, var6), \
		      doc_string,					\
		      def_body)

#define def_pcfunk6_and_rest(def_name, var1, var2, var3, var4, var5, var6, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 6,					\
		      def_pcfunk__argument__6_slot(6, var1, var2, var3, var4, var5, var6); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk7(def_name, var1, var2, var3, var4, var5, var6, var7, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 7,					\
		      def_pcfunk__argument__7_slot(7, var1, var2, var3, var4, var5, var6, var7), \
		      doc_string,					\
		      def_body)

#define def_pcfunk7_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 7,					\
		      def_pcfunk__argument__7_slot(7, var1, var2, var3, var4, var5, var6, var7); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk8(def_name, var1, var2, var3, var4, var5, var6, var7, var8, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 8,					\
		      def_pcfunk__argument__8_slot(8, var1, var2, var3, var4, var5, var6, var7, var8), \
		      doc_string,					\
		      def_body)

#define def_pcfunk8_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 8,					\
		      def_pcfunk__argument__8_slot(8, var1, var2, var3, var4, var5, var6, var7, var8); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk9(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 9,					\
		      def_pcfunk__argument__9_slot(9, var1, var2, var3, var4, var5, var6, var7, var8, var9), \
		      doc_string,					\
		      def_body)

#define def_pcfunk9_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 9,					\
		      def_pcfunk__argument__9_slot(9, var1, var2, var3, var4, var5, var6, var7, var8, var9); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk10(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 10,					\
		      def_pcfunk__argument__10_slot(10, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10), \
		      doc_string,					\
		      def_body)

#define def_pcfunk10_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 10,					\
		      def_pcfunk__argument__10_slot(10, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk11(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 11,					\
		      def_pcfunk__argument__11_slot(11, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11), \
		      doc_string,					\
		      def_body)

#define def_pcfunk11_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 11,					\
		      def_pcfunk__argument__11_slot(11, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk12(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 12,					\
		      def_pcfunk__argument__12_slot(12, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12), \
		      doc_string,					\
		      def_body)

#define def_pcfunk12_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 12,					\
		      def_pcfunk__argument__12_slot(12, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk13(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 13,					\
		      def_pcfunk__argument__13_slot(13, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13), \
		      doc_string,					\
		      def_body)

#define def_pcfunk13_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 13,					\
		      def_pcfunk__argument__13_slot(13, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk14(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 14,					\
		      def_pcfunk__argument__14_slot(14, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14), \
		      doc_string,					\
		      def_body)

#define def_pcfunk14_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 14,					\
		      def_pcfunk__argument__14_slot(14, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk15(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 15,					\
		      def_pcfunk__argument__15_slot(15, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15), \
		      doc_string,					\
		      def_body)

#define def_pcfunk15_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 15,					\
		      def_pcfunk__argument__15_slot(15, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk16(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 16,					\
		      def_pcfunk__argument__16_slot(16, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16), \
		      doc_string,					\
		      def_body)

#define def_pcfunk16_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 16,					\
		      def_pcfunk__argument__16_slot(16, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk17(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 17,					\
		      def_pcfunk__argument__17_slot(17, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17), \
		      doc_string,					\
		      def_body)

#define def_pcfunk17_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 17,					\
		      def_pcfunk__argument__17_slot(17, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk18(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 18,					\
		      def_pcfunk__argument__18_slot(18, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18), \
		      doc_string,					\
		      def_body)

#define def_pcfunk18_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 18,					\
		      def_pcfunk__argument__18_slot(18, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk19(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 19,					\
		      def_pcfunk__argument__19_slot(19, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19), \
		      doc_string,					\
		      def_body)

#define def_pcfunk19_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 19,					\
		      def_pcfunk__argument__19_slot(19, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk20(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 20,					\
		      def_pcfunk__argument__20_slot(20, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20), \
		      doc_string,					\
		      def_body)

#define def_pcfunk20_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 20,					\
		      def_pcfunk__argument__20_slot(20, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk21(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 21,					\
		      def_pcfunk__argument__21_slot(21, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21), \
		      doc_string,					\
		      def_body)

#define def_pcfunk21_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 21,					\
		      def_pcfunk__argument__21_slot(21, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk22(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 22,					\
		      def_pcfunk__argument__22_slot(22, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22), \
		      doc_string,					\
		      def_body)

#define def_pcfunk22_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 22,					\
		      def_pcfunk__argument__22_slot(22, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk23(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 23,					\
		      def_pcfunk__argument__23_slot(23, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23), \
		      doc_string,					\
		      def_body)

#define def_pcfunk23_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 23,					\
		      def_pcfunk__argument__23_slot(23, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk24(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 24,					\
		      def_pcfunk__argument__24_slot(24, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24), \
		      doc_string,					\
		      def_body)

#define def_pcfunk24_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 24,					\
		      def_pcfunk__argument__24_slot(24, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk25(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 25,					\
		      def_pcfunk__argument__25_slot(25, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25), \
		      doc_string,					\
		      def_body)

#define def_pcfunk25_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 25,					\
		      def_pcfunk__argument__25_slot(25, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)

#define def_pcfunk26(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25, var26, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 26,					\
		      def_pcfunk__argument__26_slot(26, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25, var26), \
		      doc_string,					\
		      def_body)

#define def_pcfunk26_and_rest(def_name, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25, var26, and_rest, doc_string, def_body) \
  def_pcfunk__defargs(def_name, 26,					\
		      def_pcfunk__argument__26_slot(26, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22, var23, var24, var25, var26); \
		      f2ptr and_rest = simple_args__iter; simple_args__iter = nil, \
		      doc_string,					\
		      def_body)


#define def_pcfunk__metrovar(name)  pcmetro__##name
#define def_pmetro_simple(name) f2ptr def_pcfunk__metrovar(name) (f2ptr simple_cause, f2ptr simple_fiber, f2ptr simple_env, f2ptr simple_args)

#define def_pcfunk__all_variables__define(def_name, doc_string)		\
  def_pcfunk__symbolvar__define(def_name);				\
  def_pcfunk__documentation_variable__define(def_name, doc_string);	\
  def_pcfunk__is_funktional_variable__define(def_name);			\
  def_pcfunk__has_side_effects_variable__define(def_name);

#define def_pmetro0(def_name, doc_string, def_body)			\
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(simple_args) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 0, simple_args);} \
    def_body;								\
  }

#define def_pmetro0_and_rest(def_name, def_var0, doc_string, def_body)	\
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    f2ptr def_var0 = simple_args;					\
    def_body;								\
  }

#define def_pmetro1(def_name, def_var0, doc_string, def_body)		\
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 1) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 1, simple_args);} \
    f2ptr def_var0 = f2cons__car(simple_args, this_cause);		\
    def_body;								\
  }

#define def_pmetro1_and_rest(def_name, def_var0, def_var1, doc_string, def_body) \
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 1) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 1, simple_args);} \
    f2ptr simple_args__iter = simple_args; f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    f2ptr def_var1 = f2cons__cdr(simple_args__iter, this_cause);	\
    def_body;								\
  }

#define def_pmetro2(def_name, def_var0, def_var1, doc_string, def_body)	\
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 2) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 2, simple_args);} \
    f2ptr simple_args__iter = simple_args;                          f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    def_body;								\
  }

#define def_pmetro2_and_rest(def_name, def_var0, def_var1, def_var2, doc_string, def_body) \
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 2) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 2, simple_args);} \
    f2ptr simple_args__iter = simple_args;                          f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    f2ptr def_var2 = f2cons__cdr(simple_args__iter, this_cause);	\
    def_body;								\
  }

#define def_pmetro3(def_name, def_var0, def_var1, def_var2, doc_string, def_body) \
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 3) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 3, simple_args);} \
    f2ptr simple_args__iter = simple_args;                          f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    def_body;								\
  }

#define def_pmetro3_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, doc_string, def_body) \
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 3) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 3, simple_args);} \
    f2ptr simple_args__iter = simple_args;                          f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    f2ptr def_var3 = f2cons__cdr(simple_args__iter, this_cause);	\
    def_body;								\
  }

#define def_pmetro4(def_name, def_var0, def_var1, def_var2, def_var3, doc_string, def_body) \
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 4) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 4, simple_args);} \
    f2ptr simple_args__iter = simple_args;                          f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
    def_body;								\
  }

#define def_pmetro4_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, doc_string, def_body) \
  def_pcfunk__all_variable__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 4) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 4, simple_args);} \
    f2ptr simple_args__iter = simple_args;                          f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
    f2ptr def_var4 = f2cons__cdr(simple_args__iter, this_cause);	\
    def_body;								\
  }

#define def_pmetro5(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, doc_string, def_body) \
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 5) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 5, simple_args);} \
    f2ptr simple_args__iter = simple_args;                          f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
    def_body;								\
  }

#define def_pmetro5_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, doc_string, def_body) \
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 5) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 5, simple_args);} \
    f2ptr simple_args__iter = simple_args;                          f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
    f2ptr def_var5 = f2cons__cdr(simple_args__iter, this_cause);	\
    def_body;								\
  }

#define def_pmetro6(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, doc_string, def_body) \
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 6) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 6, simple_args);} \
    f2ptr simple_args__iter = simple_args;                          f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
    def_body;								\
  }

#define def_pmetro6_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_var6, doc_string, def_body) \
  def_pcfunk__all_variables__define(def_name, doc_string);		\
  def_pcfunk__prototype__declare(def_name) {				\
    def_pcfunk__this_cause__define(def_name);				\
    def_pcfunk__this_symbol__define(def_name);				\
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 6) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 6, simple_args);} \
    f2ptr simple_args__iter = simple_args;                          f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
    simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
    f2ptr def_var6 = f2cons__cdr(simple_args__iter, this_cause);	\
    def_body;								\
  }


#define f2__primcfunk__init__defragment__fix_pointers(def_name)		\
  def_pcfunk__symbolvar__init__defragment__fix_pointers(def_name);	\
  def_pcfunk__is_funktional_variable__init__defragment__fix_pointers(def_name); \
  def_pcfunk__has_side_effects_variable__init__defragment__fix_pointers(def_name);


#define f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, cfunk_args_code) \
  f2ptr c_cfunk_var = nil;						\
  { \
    f2ptr c_cfunk_args = cfunk_args_code; \
    c_cfunk_var        = f2cfunk__new(initial_cause(), new__symbol(initial_cause(), def_pcfunk__symbolvar_string(name)), c_cfunk_args, f2pointer__new(initial_cause(), raw_executable__to__relative_ptr(def_pcfunk__funkvar(name))), global_environment(), def_pcfunk__is_funktional_variable(name), new__string(initial_cause(), (char*)def_pcfunk__documentation_variable(name))); \
    never_gc(c_cfunk_var); \
    def_pcfunk__symbolvar__init(name); \
    never_gc(def_pcfunk__symbolvar(name)); \
    environment__add_funkvar_value(initial_cause(), global_environment(), def_pcfunk__symbolvar(name), c_cfunk_var); \
  }

#define f2__primcfunk__init__with_c_cfunk_var__0_arg(name, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, nil)

#define f2__primcfunk__init__with_c_cfunk_var__0_arg_and_rest(name, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list2__new(initial_cause(), \
											 new__symbol(initial_cause(), ":rest"), \
											 new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__1_arg(name, arg0, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list1__new(initial_cause(), \
													new__symbol(initial_cause(), #arg0)))

#define f2__primcfunk__init__with_c_cfunk_var__1_arg_and_rest(name, arg0, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list3__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), ":rest"), \
											 new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__2_arg(name, arg0, arg1, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list2__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1)))

#define f2__primcfunk__init__with_c_cfunk_var__2_arg_and_rest(name, arg0, arg1, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list4__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), ":rest"), \
											 new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__3_arg(name, arg0, arg1, arg2, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list3__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2)))

#define f2__primcfunk__init__with_c_cfunk_var__3_arg_and_rest(name, arg0, arg1, arg2, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list5__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), ":rest"), \
											 new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__4_arg(name, arg0, arg1, arg2, arg3, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list4__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3)))

#define f2__primcfunk__init__with_c_cfunk_var__4_arg_and_rest(name, arg0, arg1, arg2, arg3, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list6__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3), \
											 new__symbol(initial_cause(), ":rest"), \
											 new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__5_arg(name, arg0, arg1, arg2, arg3, arg4, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list5__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3), \
											 new__symbol(initial_cause(), #arg4)))

#define f2__primcfunk__init__with_c_cfunk_var__5_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list7__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3), \
											 new__symbol(initial_cause(), #arg4), \
											 new__symbol(initial_cause(), ":rest"), \
											 new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__6_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list6__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3), \
											 new__symbol(initial_cause(), #arg4), \
											 new__symbol(initial_cause(), #arg5)))

#define f2__primcfunk__init__with_c_cfunk_var__6_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list7__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3), \
											 new__symbol(initial_cause(), #arg4), \
											 new__symbol(initial_cause(), #arg5), \
											 new__symbol(initial_cause(), ":rest"), \
											 new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__7_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list7__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3), \
											 new__symbol(initial_cause(), #arg4), \
											 new__symbol(initial_cause(), #arg5), \
											 new__symbol(initial_cause(), #arg6)))

#define f2__primcfunk__init__with_c_cfunk_var__7_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list8__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3), \
											 new__symbol(initial_cause(), #arg4), \
											 new__symbol(initial_cause(), #arg5), \
											 new__symbol(initial_cause(), #arg6), \
											 new__symbol(initial_cause(), ":rest"), \
											 new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__8_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list8__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3), \
											 new__symbol(initial_cause(), #arg4), \
											 new__symbol(initial_cause(), #arg5), \
											 new__symbol(initial_cause(), #arg6), \
											 new__symbol(initial_cause(), #arg7)))

#define f2__primcfunk__init__with_c_cfunk_var__8_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list9__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3), \
											 new__symbol(initial_cause(), #arg4), \
											 new__symbol(initial_cause(), #arg5), \
											 new__symbol(initial_cause(), #arg6), \
											 new__symbol(initial_cause(), #arg7), \
											 new__symbol(initial_cause(), ":rest"), \
											 new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__9_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list9__new(initial_cause(), \
											 new__symbol(initial_cause(), #arg0), \
											 new__symbol(initial_cause(), #arg1), \
											 new__symbol(initial_cause(), #arg2), \
											 new__symbol(initial_cause(), #arg3), \
											 new__symbol(initial_cause(), #arg4), \
											 new__symbol(initial_cause(), #arg5), \
											 new__symbol(initial_cause(), #arg6), \
											 new__symbol(initial_cause(), #arg7), \
											 new__symbol(initial_cause(), #arg8)))

#define f2__primcfunk__init__with_c_cfunk_var__9_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list10__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__10_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list10__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9)))

#define f2__primcfunk__init__with_c_cfunk_var__10_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list11__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__11_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list11__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10)))

#define f2__primcfunk__init__with_c_cfunk_var__11_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list12__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__12_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list12__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11)))

#define f2__primcfunk__init__with_c_cfunk_var__12_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list13__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__13_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list13__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12)))

#define f2__primcfunk__init__with_c_cfunk_var__13_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list14__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__14_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list14__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13)))

#define f2__primcfunk__init__with_c_cfunk_var__14_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list15__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__15_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list15__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), #arg14)))

#define f2__primcfunk__init__with_c_cfunk_var__15_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list16__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), #arg14), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__16_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list16__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), #arg14), \
											  new__symbol(initial_cause(), #arg15)))

#define f2__primcfunk__init__with_c_cfunk_var__16_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list17__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), #arg14), \
											  new__symbol(initial_cause(), #arg15), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__17_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list17__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), #arg14), \
											  new__symbol(initial_cause(), #arg15), \
											  new__symbol(initial_cause(), #arg16)))

#define f2__primcfunk__init__with_c_cfunk_var__17_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list18__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), #arg14), \
											  new__symbol(initial_cause(), #arg15), \
											  new__symbol(initial_cause(), #arg16), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__18_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list18__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), #arg14), \
											  new__symbol(initial_cause(), #arg15), \
											  new__symbol(initial_cause(), #arg16), \
											  new__symbol(initial_cause(), #arg17)))

#define f2__primcfunk__init__with_c_cfunk_var__18_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list19__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), #arg14), \
											  new__symbol(initial_cause(), #arg15), \
											  new__symbol(initial_cause(), #arg16), \
											  new__symbol(initial_cause(), #arg17), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__19_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list19__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), #arg14), \
											  new__symbol(initial_cause(), #arg15), \
											  new__symbol(initial_cause(), #arg16), \
											  new__symbol(initial_cause(), #arg17), \
											  new__symbol(initial_cause(), #arg18)))

#define f2__primcfunk__init__with_c_cfunk_var__19_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, and_rest, c_cfunk_var) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, f2list20__new(initial_cause(), \
											  new__symbol(initial_cause(), #arg0), \
											  new__symbol(initial_cause(), #arg1), \
											  new__symbol(initial_cause(), #arg2), \
											  new__symbol(initial_cause(), #arg3), \
											  new__symbol(initial_cause(), #arg4), \
											  new__symbol(initial_cause(), #arg5), \
											  new__symbol(initial_cause(), #arg6), \
											  new__symbol(initial_cause(), #arg7), \
											  new__symbol(initial_cause(), #arg8), \
											  new__symbol(initial_cause(), #arg9), \
											  new__symbol(initial_cause(), #arg10), \
											  new__symbol(initial_cause(), #arg11), \
											  new__symbol(initial_cause(), #arg12), \
											  new__symbol(initial_cause(), #arg13), \
											  new__symbol(initial_cause(), #arg14), \
											  new__symbol(initial_cause(), #arg15), \
											  new__symbol(initial_cause(), #arg16), \
											  new__symbol(initial_cause(), #arg17), \
											  new__symbol(initial_cause(), #arg18), \
											  new__symbol(initial_cause(), ":rest"), \
											  new__symbol(initial_cause(), #and_rest)))


#define f2__primcfunk__init__with_c_cfunk_var(name, c_cfunk_var) f2__primcfunk__init__with_c_cfunk_var__0_arg(name, c_cfunk_var);

#define f2__primcfunk__init__0(          name)                                                                              {f2__primcfunk__init__with_c_cfunk_var__0_arg(          name,                                                                              temp_c_cfunk_var);}
#define f2__primcfunk__init__0_and_rest( name, and_rest)                                                                    {f2__primcfunk__init__with_c_cfunk_var__0_arg_and_rest( name, and_rest,                                                                    temp_c_cfunk_var);}
#define f2__primcfunk__init__1(          name, arg0)                                                                        {f2__primcfunk__init__with_c_cfunk_var__1_arg(          name, arg0,                                                                        temp_c_cfunk_var);}
#define f2__primcfunk__init__1_and_rest( name, arg0, and_rest)                                                              {f2__primcfunk__init__with_c_cfunk_var__1_arg_and_rest( name, arg0, and_rest,                                                              temp_c_cfunk_var);}
#define f2__primcfunk__init__2(          name, arg0, arg1)                                                                  {f2__primcfunk__init__with_c_cfunk_var__2_arg(          name, arg0, arg1,                                                                  temp_c_cfunk_var);}
#define f2__primcfunk__init__2_and_rest( name, arg0, arg1, and_rest)                                                        {f2__primcfunk__init__with_c_cfunk_var__2_arg_and_rest( name, arg0, arg1, and_rest,                                                        temp_c_cfunk_var);}
#define f2__primcfunk__init__3(          name, arg0, arg1, arg2)                                                            {f2__primcfunk__init__with_c_cfunk_var__3_arg(          name, arg0, arg1, arg2,                                                            temp_c_cfunk_var);}
#define f2__primcfunk__init__3_and_rest( name, arg0, arg1, arg2, and_rest)                                                  {f2__primcfunk__init__with_c_cfunk_var__3_arg_and_rest( name, arg0, arg1, arg2, and_rest,                                                  temp_c_cfunk_var);}
#define f2__primcfunk__init__4(          name, arg0, arg1, arg2, arg3)                                                      {f2__primcfunk__init__with_c_cfunk_var__4_arg(          name, arg0, arg1, arg2, arg3,                                                      temp_c_cfunk_var);}
#define f2__primcfunk__init__4_and_rest( name, arg0, arg1, arg2, arg3, and_rest)                                            {f2__primcfunk__init__with_c_cfunk_var__4_arg_and_rest( name, arg0, arg1, arg2, arg3, and_rest,                                            temp_c_cfunk_var);}
#define f2__primcfunk__init__5(          name, arg0, arg1, arg2, arg3, arg4)                                                {f2__primcfunk__init__with_c_cfunk_var__5_arg(          name, arg0, arg1, arg2, arg3, arg4,                                                temp_c_cfunk_var);}
#define f2__primcfunk__init__5_and_rest( name, arg0, arg1, arg2, arg3, arg4, and_rest)                                      {f2__primcfunk__init__with_c_cfunk_var__5_arg_and_rest( name, arg0, arg1, arg2, arg3, arg4, and_rest,                                      temp_c_cfunk_var);}
#define f2__primcfunk__init__6(          name, arg0, arg1, arg2, arg3, arg4, arg5)                                          {f2__primcfunk__init__with_c_cfunk_var__6_arg(          name, arg0, arg1, arg2, arg3, arg4, arg5,                                          temp_c_cfunk_var);}
#define f2__primcfunk__init__6_and_rest( name, arg0, arg1, arg2, arg3, arg4, arg5, and_rest)                                {f2__primcfunk__init__with_c_cfunk_var__6_arg_and_rest( name, arg0, arg1, arg2, arg3, arg4, arg5, and_rest,                                temp_c_cfunk_var);}
#define f2__primcfunk__init__7(          name, arg0, arg1, arg2, arg3, arg4, arg5, arg6)                                    {f2__primcfunk__init__with_c_cfunk_var__7_arg(          name, arg0, arg1, arg2, arg3, arg4, arg5, arg6,                                    temp_c_cfunk_var);}
#define f2__primcfunk__init__7_and_rest( name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, and_rest)                          {f2__primcfunk__init__with_c_cfunk_var__7_arg_and_rest( name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, and_rest,                          temp_c_cfunk_var);}
#define f2__primcfunk__init__8(          name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)                              {f2__primcfunk__init__with_c_cfunk_var__8_arg(          name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,                              temp_c_cfunk_var);}
#define f2__primcfunk__init__8_and_rest( name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest)                    {f2__primcfunk__init__with_c_cfunk_var__8_arg_and_rest( name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest,                    temp_c_cfunk_var);}
#define f2__primcfunk__init__9(          name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)                        {f2__primcfunk__init__with_c_cfunk_var__9_arg(          name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8,                        temp_c_cfunk_var);}
#define f2__primcfunk__init__9_and_rest( name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest)              {f2__primcfunk__init__with_c_cfunk_var__9_arg_and_rest( name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, and_rest,              temp_c_cfunk_var);}
#define f2__primcfunk__init__10(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)                  {f2__primcfunk__init__with_c_cfunk_var__10_arg(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9,                  temp_c_cfunk_var);}
#define f2__primcfunk__init__10_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest)        {f2__primcfunk__init__with_c_cfunk_var__10_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, and_rest,        temp_c_cfunk_var);}
#define f2__primcfunk__init__11(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)           {f2__primcfunk__init__with_c_cfunk_var__11_arg(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10,           temp_c_cfunk_var);}
#define f2__primcfunk__init__11_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest) {f2__primcfunk__init__with_c_cfunk_var__11_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, and_rest, temp_c_cfunk_var);}

#define f2__primcfunk__init__12(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) { \
    f2__primcfunk__init__with_c_cfunk_var__12_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, temp_c_cfunk_var); }
#define f2__primcfunk__init__12_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest) { \
    f2__primcfunk__init__with_c_cfunk_var__12_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, and_rest, temp_c_cfunk_var); }

#define f2__primcfunk__init__13(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) { \
    f2__primcfunk__init__with_c_cfunk_var__13_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, temp_c_cfunk_var); }
#define f2__primcfunk__init__13_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest) { \
    f2__primcfunk__init__with_c_cfunk_var__13_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, and_rest, temp_c_cfunk_var); }

#define f2__primcfunk__init__14(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13) { \
    f2__primcfunk__init__with_c_cfunk_var__14_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, temp_c_cfunk_var); }
#define f2__primcfunk__init__14_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, and_rest) { \
    f2__primcfunk__init__with_c_cfunk_var__14_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, and_rest, temp_c_cfunk_var); }

#define f2__primcfunk__init__15(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) { \
    f2__primcfunk__init__with_c_cfunk_var__15_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, temp_c_cfunk_var); }
#define f2__primcfunk__init__15_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, and_rest) { \
    f2__primcfunk__init__with_c_cfunk_var__15_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, and_rest, temp_c_cfunk_var); }

#define f2__primcfunk__init__16(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15) { \
    f2__primcfunk__init__with_c_cfunk_var__16_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, temp_c_cfunk_var); }
#define f2__primcfunk__init__16_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, and_rest) { \
    f2__primcfunk__init__with_c_cfunk_var__16_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, and_rest, temp_c_cfunk_var); }

#define f2__primcfunk__init__17(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16) { \
    f2__primcfunk__init__with_c_cfunk_var__17_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, temp_c_cfunk_var); }
#define f2__primcfunk__init__17_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, and_rest) { \
    f2__primcfunk__init__with_c_cfunk_var__17_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, and_rest, temp_c_cfunk_var); }

#define f2__primcfunk__init__18(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17) { \
    f2__primcfunk__init__with_c_cfunk_var__18_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, temp_c_cfunk_var); }
#define f2__primcfunk__init__18_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, and_rest) { \
    f2__primcfunk__init__with_c_cfunk_var__18_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, and_rest, temp_c_cfunk_var); }

#define f2__primcfunk__init__19(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18) { \
    f2__primcfunk__init__with_c_cfunk_var__19_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, temp_c_cfunk_var); }
#define f2__primcfunk__init__19_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, and_rest) { \
    f2__primcfunk__init__with_c_cfunk_var__19_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, and_rest, temp_c_cfunk_var); }


#define f2__primcfunk__init(name) f2__primcfunk__init__0(name)

#define f2__primmetro__init(name) { \
  def_pcfunk__symbolvar__init(name); \
  environment__add_funkvar_value(initial_cause(), global_environment(), def_pcfunk__symbolvar(name), raw__metrocfunk__new(initial_cause(), new__symbol(initial_cause(), def_pcfunk__symbolvar_string(name)), f2pointer__new(initial_cause(), raw_executable__to__relative_ptr(def_pcfunk__metrovar(name))), global_environment(), nil)); \
}

#include "f2_memory.h"
#include "f2_ptypes.h"
#include "f2_primobject__environment.h"
#include "f2_primobject__tensor.h"
#include "f2_primobjects.h"
#include "f2_compile.h"
#include "f2_time.h"
#include "f2_gmodule.h"
#include "f2_compile_x86.h"


/////// BEGIN EXTERN DEFS

f2ptr f2__argument_type_check_failure__larva__new(f2ptr cause, f2ptr value);
f2ptr f2__argument_number_check_failure__larva__new(f2ptr cause, f2ptr funk_symbol, int min_arg_num, f2ptr args);

u64  raw__simple_length(f2ptr cause, f2ptr seq);
f2ptr f2__simple_length(f2ptr cause, f2ptr seq);
f2ptr f2__integer__greater_than(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__less_than(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__equal_sign(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__not_equal_sign(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__bitshift_left(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__bitshift_right(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__bit_and(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__bit_or(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__bit_xor(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__bit_not(f2ptr cause, f2ptr x);
f2ptr f2__integer__add(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__subtract(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__multiply(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__add_double(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__subtract_double(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__divide_by_integer(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__integer__divide_by_double(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__pointer__greater_than(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__pointer__less_than(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__pointer__equal_sign(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__pointer__not_equal_sign(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__pointer__add_integer(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__pointer__subtract(f2ptr cause, f2ptr x, f2ptr y);

// nil

boolean_t raw__null(f2ptr x);
f2ptr      f2__null(f2ptr cause, f2ptr x);

// logic

boolean_t raw__not(f2ptr x);
f2ptr      f2__not(f2ptr cause, f2ptr x);
f2ptr      f2__and(f2ptr cause, f2ptr x0, f2ptr x1);
f2ptr      f2__or (f2ptr cause, f2ptr x0, f2ptr x1);

// math

f2ptr f2__add               (f2ptr cause, f2ptr x0, f2ptr x1);
f2ptr f2__negative          (f2ptr cause, f2ptr x);
f2ptr f2__subtract          (f2ptr cause, f2ptr x0, f2ptr x1);
f2ptr f2__multiply          (f2ptr cause, f2ptr x0, f2ptr x1);
f2ptr f2__inverse           (f2ptr cause, f2ptr x);
f2ptr f2__divide            (f2ptr cause, f2ptr x0, f2ptr x1);
f2ptr f2__modulo            (f2ptr cause, f2ptr x0, f2ptr x1);
f2ptr f2__increment         (f2ptr cause, f2ptr x);
f2ptr f2__decrement         (f2ptr cause, f2ptr x);
f2ptr f2__numerically_equals(f2ptr cause, f2ptr x0, f2ptr x1);
f2ptr f2__less_than         (f2ptr cause, f2ptr x0, f2ptr x1);
f2ptr f2__greater_than      (f2ptr cause, f2ptr x0, f2ptr x1);


// s64

boolean_t s64__add_overflows(s64 this, s64 that);

// u64

u64 u64__sqrt   (u64 this);
u64 u64__bit_num(u64 this);

// system

f2ptr raw__system__memorypool__total_global_memory(f2ptr cause, s64   index);
f2ptr f2__system__memorypool__total_global_memory( f2ptr cause, f2ptr index);
f2ptr raw__system__memorypool__total_free_memory(  f2ptr cause, s64   index);
f2ptr f2__system__memorypool__total_free_memory(   f2ptr cause, f2ptr index);


// funk2 pointer (f2ptr)

f2ptr f2__pointer(f2ptr cause, f2ptr x);
f2ptr f2__deref_pointer(f2ptr cause, f2ptr x);

// memblock

f2ptr f2__memblock__set_init_render_xyz(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__memblock__set_init_render_on(f2ptr cause, f2ptr render_on);
f2ptr f2__memblock__set_init_render_noise(f2ptr cause, f2ptr render_noise);

// ptype

f2ptr f2__ptype__raw(f2ptr cause, f2ptr x);
f2ptr f2__ptype__cause(f2ptr cause, f2ptr x);
f2ptr f2__ptype__cause__set(f2ptr cause, f2ptr x, f2ptr value);

// integer

f2ptr f2__integer__to_double(f2ptr cause, f2ptr x);
f2ptr f2__integer__to_float(f2ptr cause, f2ptr x);

// double

f2ptr f2__double__to_integer(f2ptr cause, f2ptr x);
f2ptr f2__double__to_float(f2ptr cause, f2ptr x);
f2ptr f2__double__add_double(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__double__subtract_double(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__double__multiply_by_double(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__double__divide_by_double(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__double__add_integer(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__double__subtract_integer(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__double__multiply_by_integer(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__double__divide_by_integer(f2ptr cause, f2ptr x, f2ptr y);

// float

f2ptr f2__float__to_integer(f2ptr cause, f2ptr x);
f2ptr f2__float__to_double(f2ptr cause, f2ptr x);

// pointer


// cmutex

void  raw__cmutex__lock_both(f2ptr cause, f2ptr this, f2ptr that);
f2ptr  f2__cmutex__lock_both(f2ptr cause, f2ptr this, f2ptr that);

// char


// string

f2ptr     new__string      (f2ptr cause, char*              str);
f2ptr     new__funk2_string(f2ptr cause, funk2_character_t* str);

f2ptr      f2__string__length(f2ptr cause, f2ptr x);
f2ptr      f2__string__elt(f2ptr cause, f2ptr x, f2ptr y);
boolean_t raw__string__eq(f2ptr cause, f2ptr x, f2ptr y);
f2ptr      f2__string__eq(f2ptr cause, f2ptr x, f2ptr y);
f2ptr      f2__string__new_raw_c_string(f2ptr cause, f2ptr x);

// symbol

f2ptr new__symbol(f2ptr cause, char* str);

// larva

// chunk

f2ptr f2__chunk__new_compiled_from_funk(f2ptr cause, f2ptr x);

// number interface (integer, double, float)

boolean_t raw__number__is_type(f2ptr cause, f2ptr exp);
double    raw__number__to_double(f2ptr cause, f2ptr this);

// time

f2ptr f2__time(f2ptr cause);


// scheduler_eq

boolean_t raw__scheduler_eq(f2ptr cause, f2ptr x, f2ptr y);
u64 raw__scheduler_eq_hash_value(f2ptr cause, f2ptr x);

// primobject ptypehash

u64 raw__eq_hash_value(f2ptr cause, f2ptr exp);
boolean_t raw__equals(f2ptr cause, f2ptr x, f2ptr y);

// primobject thought_process


// primobject fiber

f2ptr f2__force_funk_apply(f2ptr cause, f2ptr fiber, f2ptr funkable, f2ptr args);
f2ptr f2__parallel_funk_apply(f2ptr cause, f2ptr fiber, f2ptr funkable, f2ptr args);
void f2fiber__force_funk(f2ptr fiber, f2ptr cause, f2ptr cfunkable, f2ptr args);
void f2fiber__funk(f2ptr fiber, f2ptr cause, f2ptr cfunkable, f2ptr args);
f2ptr f2__fiber__new_unscheduled(f2ptr cause, f2ptr execution_cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr args);
f2ptr f2__fiber_parallel(f2ptr cause, f2ptr execution_cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr args);
f2ptr f2__fiber_serial(f2ptr cause, f2ptr execution_cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr args);

// cons

boolean_t raw__conslist__is_type(f2ptr cause, f2ptr this);
f2ptr      f2__conslist__is_type(f2ptr cause, f2ptr this);
f2ptr     raw__conslist__as__array(f2ptr cause, f2ptr this);
f2ptr      f2__conslist__as__array(f2ptr cause, f2ptr this);

f2ptr raw__firstn(f2ptr cause, f2ptr this, s64 n);
f2ptr f2__firstn(f2ptr cause, f2ptr this, f2ptr n);
f2ptr raw__restn(f2ptr cause, f2ptr this, s64 n);
f2ptr f2__restn(f2ptr cause, f2ptr this, f2ptr n);

f2ptr f2__conslistlist__append(f2ptr cause, f2ptr these);

// sequence (array, list, doublelist, etc.)

f2ptr raw__elt(f2ptr cause, f2ptr this, int raw_index);
f2ptr  f2__elt(f2ptr cause, f2ptr this, f2ptr index);
f2ptr  f2__reverse(f2ptr cause, f2ptr this);

// deprecated (use raw__elt or f2__elt instead)
f2ptr raw__seq_elt(f2ptr this, f2ptr index, f2ptr cause);


// interface funkable (includes types: funk, metro, cfunk, metrocfunk)

boolean_t raw__funkable__is_type(f2ptr cause, f2ptr exp);
f2ptr     raw__funkable__env(f2ptr cause, f2ptr funkable);
f2ptr      f2__funkable__env(f2ptr cause, f2ptr this);
f2ptr      f2__funkable__name(f2ptr cause, f2ptr this);
f2ptr      f2__funkable__args(f2ptr cause, f2ptr this);

f2ptr f2__first(f2ptr cause, f2ptr exp);
f2ptr f2__first__set(f2ptr cause, f2ptr exp, f2ptr value);
f2ptr f2__next(f2ptr cause, f2ptr exp);
f2ptr f2__next__set(f2ptr cause, f2ptr exp, f2ptr value);
f2ptr f2__prev(f2ptr cause, f2ptr exp);
f2ptr f2__prev__set(f2ptr cause, f2ptr exp, f2ptr value);

f2ptr      f2__format(f2ptr cause, f2ptr fiber, f2ptr fptr, f2ptr exp);
f2ptr      f2__format__html(f2ptr cause, f2ptr fiber, f2ptr fptr, f2ptr exp);
f2ptr      f2__list(f2ptr cause, f2ptr seq);
void      raw__exit(int value);
f2ptr      f2__quit(f2ptr cause, f2ptr value);
f2ptr      f2__seq_elt__set(f2ptr this, f2ptr index, f2ptr cause, f2ptr value);
boolean_t raw__eq(f2ptr cause, f2ptr x, f2ptr y);
f2ptr      f2__eq(f2ptr cause, f2ptr x, f2ptr y);
f2ptr      f2__fopen(f2ptr cause, f2ptr filename, f2ptr mode);
f2ptr      f2__fclose(f2ptr cause, f2ptr fptr);
f2ptr      f2__compile(f2ptr cause, f2ptr fiber, f2ptr exp, f2ptr protect_environment);
f2ptr      f2__identity(f2ptr cause, f2ptr exp);
f2ptr      f2__make_funk(f2ptr cause, f2ptr fiber, f2ptr name, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr bytecodes, f2ptr is_funktional, f2ptr documentation);
f2ptr      f2__make_metro(f2ptr cause, f2ptr fiber, f2ptr name, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr bytecodes, f2ptr is_funktional, f2ptr documentationg);
f2ptr      f2__cfunk__apply(f2ptr cause, f2ptr cfunk, f2ptr fiber, f2ptr args);
f2ptr      f2__metrocfunk__apply(f2ptr cause, f2ptr metrocfunk, f2ptr fiber, f2ptr args);
u64       raw__random(u64 max_value);
f2ptr      f2__random(f2ptr cause, f2ptr max_value);
f2ptr      f2__array(f2ptr cause, f2ptr and_rest);
f2ptr      f2__chunk_copy(f2ptr cause, f2ptr init);
f2ptr      f2__chunk__read_8bit(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr      f2__chunk__write_8bit_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value);
f2ptr      f2__chunk__read_8bit_signed(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr      f2__chunk__read_16bit(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr      f2__chunk__write_16bit_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value);
f2ptr      f2__chunk__read_16bit_signed(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr      f2__chunk__read_32bit(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr      f2__chunk__write_32bit_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value);
f2ptr      f2__chunk__read_32bit_signed(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr      f2__demetropolize_full(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr exp);
f2ptr      f2__exps_demetropolize_full(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr exp);
f2ptr      f2__lookup_funkvar(f2ptr cause, f2ptr env, f2ptr funkvar, f2ptr undefined_value);
f2ptr      f2__wrong_argument_number_error__set(f2ptr cause, f2ptr error_bcs);
f2ptr      f2__jump_to_chunk(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr exp, f2ptr args);
f2ptr      f2__coerce_to_int(f2ptr cause, f2ptr exp);
f2ptr      f2__memory_image__save(f2ptr cause, f2ptr filename);
f2ptr      f2__memory_image__load(f2ptr cause, f2ptr filename);
f2ptr      f2__string__read(f2ptr cause, f2ptr this);

// **

void f2__primcfunks__reinitialize_globalvars();
void f2__primcfunks__initialize();

#endif // F2__PRIMCFUNKS__H
