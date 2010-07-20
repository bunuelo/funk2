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

#ifndef F2__PRIMCFUNKS__H
#define F2__PRIMCFUNKS__H

#include "f2_redblacktree.h"
#include "f2_processor_mutex.h"

#define def_pcfunk__funkvar(name)            pcfunk__##name
#define def_pcfunk__prototype__declare(name) f2ptr def_pcfunk__funkvar(name) (f2ptr simple_cause, f2ptr simple_fiber, f2ptr simple_env, f2ptr simple_args)

#define def_pcfunk__symbolvar(name)          __symbol__##name
#define def_pcfunk__symbolvar_string(name)   "primfunk:" #name
#define def_pcfunk__symbolvar__define(name)  f2ptr def_pcfunk__symbolvar(name) = nil
#define def_pcfunk__symbolvar__init(name)    if(!def_pcfunk__symbolvar(name)) {def_pcfunk__symbolvar(name) = f2symbol__new(initial_cause(), strlen(def_pcfunk__symbolvar_string(name)), (u8*)def_pcfunk__symbolvar_string(name));}
#define def_pcfunk__this_symbol__define(name) \
   f2ptr this_symbol = def_pcfunk__symbolvar(name); \
   this_symbol = this_symbol;

#define def_pcfunk__documentationvar(name)                   __documentation__##name
#define def_pcfunk__documentationvar__define(name)           f2ptr def_pcfunk__documentationvar(name) = nil
#define def_pcfunk__documentationvar__init(name, doc_string) if(!def_pcfunk__documentationvar(name)) {def_pcfunk__documentationvar(name) = f2string__new(initial_cause(), strlen(doc_string), (u8*)doc_string);}
#define def_pcfunk__this_documentation__define(name) \
   f2ptr this_documentation = def_pcfunk__documentationvar(name); \
   this_documentation = this_documentation;


//#  define def_pcfunk__this_cause__define(name) 
//     f2ptr this_cause = f2cause__new(simple_cause, simple_fiber, simple_env, def_pcfunk__symbolvar(name), simple_args, nil); 
//     this_cause = this_cause;
//#  define def_pcfunk__this_cause__define(name) 
//     f2ptr this_cause = f2__cause__new(simple_cause, nil); 
//     this_cause = this_cause;

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

#define def_pcfunk0(def_name, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(simple_args) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 0, simple_args);} \
    def_body; \
  }

#define def_pcfunk0_and_rest(def_name, def_var0, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    f2ptr def_var0 = simple_args; \
    def_body; \
  }

#define def_pcfunk1(def_name, def_var0, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 1) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 1, simple_args);} \
    f2ptr def_var0 = f2cons__car(simple_args, this_cause); \
    def_body; \
  }

#define def_pcfunk1_and_rest(def_name, def_var0, def_var1, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 1) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 1, simple_args);} \
    f2ptr simple_args__iter = simple_args; f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
                                           f2ptr def_var1 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk2(def_name, def_var0, def_var1, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 2) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 2, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk2_and_rest(def_name, def_var0, def_var1, def_var2, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 2) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 2, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var2 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk3(def_name, def_var0, def_var1, def_var2, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 3) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 3, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk3_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 3) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 3, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var3 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk4(def_name, def_var0, def_var1, def_var2, def_var3, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 4) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 4, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk4_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 4) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 4, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var4 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk5(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 5) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 5, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk5_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 5) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 5, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var5 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk6(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 6) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 6, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk6_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_var6, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 6) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 6, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var6 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk7(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_var6, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 7) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 7, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var6 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk7_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_var6, def_var7, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 7) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 7, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var6 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var7 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk8(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_var6, def_var7, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 8) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 8, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var6 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var7 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk8_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_var6, def_var7, def_var8, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 8) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 8, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var6 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var7 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var8 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk__metrovar(name)  pcmetro__##name
#define def_pmetro_simple(name) f2ptr def_pcfunk__metrovar(name) (f2ptr simple_cause, f2ptr simple_fiber, f2ptr simple_env, f2ptr simple_args)

#define def_pmetro0(def_name, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(simple_args) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 0, simple_args);} \
    def_body; \
  }

#define def_pmetro0_and_rest(def_name, def_var0, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    f2ptr def_var0 = simple_args; \
    def_body; \
  }

#define def_pmetro1(def_name, def_var0, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 1) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 1, simple_args);} \
    f2ptr def_var0 = f2cons__car(simple_args, this_cause); \
    def_body; \
  }

#define def_pmetro1_and_rest(def_name, def_var0, def_var1, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 1) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 1, simple_args);} \
    f2ptr simple_args__iter = simple_args; f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
                                           f2ptr def_var1 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro2(def_name, def_var0, def_var1, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 2) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 2, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro2_and_rest(def_name, def_var0, def_var1, def_var2, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 2) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 2, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var2 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro3(def_name, def_var0, def_var1, def_var2, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 3) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 3, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro3_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 3) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 3, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var3 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro4(def_name, def_var0, def_var1, def_var2, def_var3, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 4) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 4, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro4_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 4) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 4, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var4 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro5(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 5) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 5, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro5_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 5) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 5, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var5 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro6(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) != 6) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 6, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro6_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_var6, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__documentationvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    def_pcfunk__this_documentation__define(def_name); \
    if(!simple_args || raw__simple_length(this_cause, simple_args) < 6) {return f2__argument_number_check_failure__larva__new(this_cause, this_symbol, 6, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var6 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, cfunk_args_code, doc_string) \
  f2ptr c_cfunk_var = nil; \
  { \
    f2ptr c_cfunk_args = cfunk_args_code; \
    def_pcfunk__documentationvar__init(name, doc_string); \
    c_cfunk_var        = f2cfunk__new(initial_cause(), f2symbol__new(initial_cause(), strlen(def_pcfunk__symbolvar_string(name)), (u8*)def_pcfunk__symbolvar_string(name)), c_cfunk_args, f2pointer__new(initial_cause(), raw_executable__to__relative_ptr(def_pcfunk__funkvar(name))), global_environment(), (is_funktional) ? __funk2.globalenv.true__symbol : nil, def_pcfunk__documentationvar(name)); \
    never_gc(c_cfunk_var); \
    def_pcfunk__symbolvar__init(name); \
    never_gc(def_pcfunk__symbolvar(name)); \
    environment__add_funkvar_value(initial_cause(), global_environment(), def_pcfunk__symbolvar(name), c_cfunk_var); \
  }

#define f2__primcfunk__init__with_c_cfunk_var__0_arg(name, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, nil, doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__0_arg_and_rest(name, and_rest, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list2__new(initial_cause(), f2symbol__new(initial_cause(), strlen(":rest"), (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__1_arg(name, arg0, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list1__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__1_arg_and_rest(name, arg0, and_rest, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list3__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
													                 f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__2_arg(name, arg0, arg1, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list2__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__2_arg_and_rest(name, arg0, arg1, and_rest, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list4__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
													                 f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__3_arg(name, arg0, arg1, arg2, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list3__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2), (u8*)#arg2)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__3_arg_and_rest(name, arg0, arg1, arg2, and_rest, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list5__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2),     (u8*)#arg2) \
													                 f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__4_arg(name, arg0, arg1, arg2, arg3, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list4__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2), (u8*)#arg2), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3), (u8*)#arg3)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__4_arg_and_rest(name, arg0, arg1, arg2, arg3, and_rest, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list6__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2),     (u8*)#arg2) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3),     (u8*)#arg3) \
													                 f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__5_arg(name, arg0, arg1, arg2, arg3, arg4, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list5__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2), (u8*)#arg2), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3), (u8*)#arg3), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4), (u8*)#arg4)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__5_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, and_rest, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list7__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2),     (u8*)#arg2) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3),     (u8*)#arg3) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4),     (u8*)#arg4) \
													                 f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__6_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list6__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2), (u8*)#arg2), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3), (u8*)#arg3), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4), (u8*)#arg4), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg5), (u8*)#arg5)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__6_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, and_rest, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list7__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2),     (u8*)#arg2) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3),     (u8*)#arg3) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4),     (u8*)#arg4) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg5),     (u8*)#arg5) \
													                 f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__7_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list7__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2), (u8*)#arg2), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3), (u8*)#arg3), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4), (u8*)#arg4), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg5), (u8*)#arg5), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg6), (u8*)#arg6)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__7_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, and_rest, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list8__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2),     (u8*)#arg2) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3),     (u8*)#arg3) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4),     (u8*)#arg4) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg5),     (u8*)#arg5) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg6),     (u8*)#arg6) \
													                 f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__8_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list8__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2), (u8*)#arg2), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3), (u8*)#arg3), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4), (u8*)#arg4), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg5), (u8*)#arg5), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg6), (u8*)#arg6), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg7), (u8*)#arg7)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var__8_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest, c_cfunk_var, is_funktional, doc_string) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list9__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2),     (u8*)#arg2) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3),     (u8*)#arg3) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4),     (u8*)#arg4) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg5),     (u8*)#arg5) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg6),     (u8*)#arg6) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg7),     (u8*)#arg7) \
													                 f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)), doc_string)

#define f2__primcfunk__init__with_c_cfunk_var(name, c_cfunk_var, is_funktional, doc_string) f2__primcfunk__init__with_c_cfunk_var__0_arg(name, c_cfunk_var, is_funktional, doc_string);

#define f2__primcfunk__init__0(         name, doc_string)                                                           { f2__primcfunk__init__with_c_cfunk_var__0_arg(         name,                                                           temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__0_and_rest(name, and_rest, doc_string)                                                 { f2__primcfunk__init__with_c_cfunk_var__0_arg_and_rest(name, and_rest,                                                 temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__1(         name, arg0, doc_string)                                                     { f2__primcfunk__init__with_c_cfunk_var__1_arg(         name, arg0,                                                     temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__1_and_rest(name, arg0, and_rest, doc_string)                                           { f2__primcfunk__init__with_c_cfunk_var__1_arg_and_rest(name, arg0, and_rest,                                           temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__2(         name, arg0, arg1, doc_string)                                               { f2__primcfunk__init__with_c_cfunk_var__2_arg(         name, arg0, arg1,                                               temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__2_and_rest(name, arg0, arg1, and_rest, doc_string)                                     { f2__primcfunk__init__with_c_cfunk_var__2_arg_and_rest(name, arg0, arg1, and_rest,                                     temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__3(         name, arg0, arg1, arg2, doc_string)                                         { f2__primcfunk__init__with_c_cfunk_var__3_arg(         name, arg0, arg1, arg2,                                         temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__3_and_rest(name, arg0, arg1, arg2, and_rest, doc_string)                               { f2__primcfunk__init__with_c_cfunk_var__3_arg_and_rest(name, arg0, arg1, arg2, and_rest,                               temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__4(         name, arg0, arg1, arg2, arg3, doc_string)                                   { f2__primcfunk__init__with_c_cfunk_var__4_arg(         name, arg0, arg1, arg2, arg3,                                   temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__4_and_rest(name, arg0, arg1, arg2, arg3, and_rest, doc_string)                         { f2__primcfunk__init__with_c_cfunk_var__4_arg_and_rest(name, arg0, arg1, arg2, arg3, and_rest,                         temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__5(         name, arg0, arg1, arg2, arg3, arg4, doc_string)                             { f2__primcfunk__init__with_c_cfunk_var__5_arg(         name, arg0, arg1, arg2, arg3, arg4,                             temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__5_and_rest(name, arg0, arg1, arg2, arg3, arg4, and_rest, doc_string)                   { f2__primcfunk__init__with_c_cfunk_var__5_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, and_rest,                   temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__6(         name, arg0, arg1, arg2, arg3, arg4, arg5, doc_string)                       { f2__primcfunk__init__with_c_cfunk_var__6_arg(         name, arg0, arg1, arg2, arg3, arg4, arg5,                       temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__6_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, and_rest, doc_string)             { f2__primcfunk__init__with_c_cfunk_var__6_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, and_rest,             temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__7(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, doc_string)                 { f2__primcfunk__init__with_c_cfunk_var__7_arg(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6,                 temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__7_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, and_rest, doc_string)       { f2__primcfunk__init__with_c_cfunk_var__7_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, and_rest,       temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__8(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, doc_string)           { f2__primcfunk__init__with_c_cfunk_var__8_arg(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,           temp_c_cfunk_var, 0, doc_string); }
#define f2__primcfunk__init__8_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest, doc_string) { f2__primcfunk__init__with_c_cfunk_var__8_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest, temp_c_cfunk_var, 0, doc_string); }

#define f2__primcfunk__init(name, doc_string) f2__primcfunk__init__0(name, doc_string)

#define f2__funktional_primcfunk__init__0(         name, doc_string)                                                           { f2__primcfunk__init__with_c_cfunk_var__0_arg(         name,                                                           temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__0_and_rest(name, and_rest, doc_string)                                                 { f2__primcfunk__init__with_c_cfunk_var__0_arg_and_rest(name, and_rest,                                                 temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__1(         name, arg0, doc_string)                                                     { f2__primcfunk__init__with_c_cfunk_var__1_arg(         name, arg0,                                                     temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__1_and_rest(name, arg0, and_rest, doc_string)                                           { f2__primcfunk__init__with_c_cfunk_var__1_arg_and_rest(name, arg0, and_rest,                                           temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__2(         name, arg0, arg1, doc_string)                                               { f2__primcfunk__init__with_c_cfunk_var__2_arg(         name, arg0, arg1,                                               temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__2_and_rest(name, arg0, arg1, and_rest, doc_string)                                     { f2__primcfunk__init__with_c_cfunk_var__2_arg_and_rest(name, arg0, arg1, and_rest,                                     temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__3(         name, arg0, arg1, arg2, doc_string)                                         { f2__primcfunk__init__with_c_cfunk_var__3_arg(         name, arg0, arg1, arg2,                                         temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__3_and_rest(name, arg0, arg1, arg2, and_rest, doc_string)                               { f2__primcfunk__init__with_c_cfunk_var__3_arg_and_rest(name, arg0, arg1, arg2, and_rest,                               temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__4(         name, arg0, arg1, arg2, arg3, doc_string)                                   { f2__primcfunk__init__with_c_cfunk_var__4_arg(         name, arg0, arg1, arg2, arg3,                                   temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__4_and_rest(name, arg0, arg1, arg2, arg3, and_rest, doc_string)                         { f2__primcfunk__init__with_c_cfunk_var__4_arg_and_rest(name, arg0, arg1, arg2, arg3, and_rest,                         temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__5(         name, arg0, arg1, arg2, arg3, arg4, doc_string)                             { f2__primcfunk__init__with_c_cfunk_var__5_arg(         name, arg0, arg1, arg2, arg3, arg4,                             temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__5_and_rest(name, arg0, arg1, arg2, arg3, arg4, and_rest, doc_string)                   { f2__primcfunk__init__with_c_cfunk_var__5_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, and_rest,                   temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__6(         name, arg0, arg1, arg2, arg3, arg4, arg5, doc_string)                       { f2__primcfunk__init__with_c_cfunk_var__6_arg(         name, arg0, arg1, arg2, arg3, arg4, arg5,                       temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__6_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, and_rest, doc_string)             { f2__primcfunk__init__with_c_cfunk_var__6_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, and_rest,             temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__7(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, doc_string)                 { f2__primcfunk__init__with_c_cfunk_var__7_arg(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6,                 temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__7_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, and_rest, doc_string)       { f2__primcfunk__init__with_c_cfunk_var__7_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, and_rest,       temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__8(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, doc_string)           { f2__primcfunk__init__with_c_cfunk_var__8_arg(         name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,           temp_c_cfunk_var, 1, doc_string); }
#define f2__funktional_primcfunk__init__8_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest, doc_string) { f2__primcfunk__init__with_c_cfunk_var__8_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, and_rest, temp_c_cfunk_var, 1, doc_string); }

#define f2__funktional_primcfunk__init(name, doc_string) f2__funktional_primcfunk__init__0(name, doc_string)

#define f2__primmetro__init(is_funktional, name) { \
  def_pcfunk__symbolvar__init(name); \
  environment__add_funkvar_value(initial_cause(), global_environment(), def_pcfunk__symbolvar(name), f2metrocfunk__new(initial_cause(), f2symbol__new(initial_cause(), strlen(def_pcfunk__symbolvar_string(name)), (u8*)def_pcfunk__symbolvar_string(name)), f2pointer__new(initial_cause(), raw_executable__to__relative_ptr(def_pcfunk__metrovar(name))), global_environment(), nil)); \
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
boolean_t raw__not(f2ptr x);
f2ptr     f2__not(f2ptr cause, f2ptr x);

// s64

boolean_t s64__add_overflows(s64 this, s64 that);

// u64

u64 u64__sqrt(u64 this);

// funk2 pointer (f2ptr)

f2ptr f2__pointer(f2ptr cause, f2ptr x);
f2ptr f2__deref_pointer(f2ptr cause, f2ptr x);

// memblock

f2ptr f2__memblock__set_init_render_xyz(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__memblock__set_init_render_on(f2ptr cause, f2ptr render_on);
f2ptr f2__memblock__set_init_render_noise(f2ptr cause, f2ptr render_noise);
f2ptr f2__memblock__creation_nanoseconds_since_1970(f2ptr cause, f2ptr x);

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


// gfunkptr

f2ptr f2__gfunkptr__new_from_pointer(f2ptr cause, f2ptr x);

// mutex

void  raw__mutex__lock_both(f2ptr cause, f2ptr this, f2ptr that);
f2ptr  f2__mutex__lock_both(f2ptr cause, f2ptr this, f2ptr that);

// char


// string

f2ptr     new__string(f2ptr cause, char* str);
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

// cause

boolean_t raw__cause__allocate_traced_arrays(f2ptr cause, f2ptr this);
f2ptr      f2__cause__define_type_var(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);

// time

f2ptr f2__time(f2ptr cause);

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

f2ptr f2__conslistlist__append(f2ptr cause, f2ptr these);

// sequence (array, list, doublelist, etc.)

f2ptr raw__elt(f2ptr cause, f2ptr this, int raw_index);
f2ptr  f2__elt(f2ptr cause, f2ptr this, f2ptr index);
f2ptr  f2__reverse(f2ptr cause, f2ptr this);

// deprecated (use raw__elt or f2__elt instead)
f2ptr raw__seq_elt(f2ptr this, f2ptr index, f2ptr cause);


// interface funkable (includes types: funk, metro, cfunk, metrocfunk)

boolean_t raw__funkable__is_type(f2ptr cause, f2ptr exp);
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
f2ptr      f2__array__new(f2ptr cause, u64 length);
f2ptr      f2__array__new_1d(f2ptr cause, f2ptr length, f2ptr and_rest);
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
