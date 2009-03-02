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

#ifndef F2__PRIMCFUNKS__H
#define F2__PRIMCFUNKS__H

#define def_pcfunk__funkvar(name)            pcfunk__##name
#define def_pcfunk__prototype__declare(name) f2ptr def_pcfunk__funkvar(name) (f2ptr simple_cause, f2ptr simple_thread, f2ptr simple_env, f2ptr simple_args)
#define def_pcfunk__symbolvar(name)          __symbol__##name
#define def_pcfunk__symbolvar_string(name)   "primfunk:" #name
#define def_pcfunk__symbolvar__define(name)  f2ptr def_pcfunk__symbolvar(name) = nil
#define def_pcfunk__symbolvar__init(name)    if(!def_pcfunk__symbolvar(name)) {def_pcfunk__symbolvar(name) = f2symbol__new(initial_cause(), strlen(def_pcfunk__symbolvar_string(name)), (u8*)def_pcfunk__symbolvar_string(name));}
#define def_pcfunk__this_symbol__define(name) \
   f2ptr this_symbol = def_pcfunk__symbolvar(name); \
   this_symbol = this_symbol;


//#  define def_pcfunk__this_cause__define(name) 
//     f2ptr this_cause = f2cause__new(simple_cause, simple_thread, simple_env, def_pcfunk__symbolvar(name), simple_args, nil); 
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
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(simple_args) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 0, simple_args);} \
    def_body; \
  }

#define def_pcfunk0_and_rest(def_name, def_var0, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    f2ptr def_var0 = simple_args; \
    def_body; \
  }

#define def_pcfunk1(def_name, def_var0, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 1) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 1, simple_args);} \
    f2ptr def_var0 = f2cons__car(simple_args, this_cause); \
    def_body; \
  }

#define def_pcfunk1_and_rest(def_name, def_var0, def_var1, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 1) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 1, simple_args);} \
    f2ptr simple_args__iter = simple_args; f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
                                           f2ptr def_var1 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk2(def_name, def_var0, def_var1, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 2) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 2, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk2_and_rest(def_name, def_var0, def_var1, def_var2, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 2) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 2, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var2 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk3(def_name, def_var0, def_var1, def_var2, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 3) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 3, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk3_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 3) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 3, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var3 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk4(def_name, def_var0, def_var1, def_var2, def_var3, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 4) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 4, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk4_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 4) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 4, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var4 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk5(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 5) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 5, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pcfunk5_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 5) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 5, simple_args);} \
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
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 6) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 6, simple_args);} \
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
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 6) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 6, simple_args);} \
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
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 7) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 7, simple_args);} \
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
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 7) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 7, simple_args);} \
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

#define def_pcfunk__metrovar(name)  pcmetro__##name
#define def_pmetro_simple(name) f2ptr def_pcfunk__metrovar(name) (f2ptr simple_cause, f2ptr simple_thread, f2ptr simple_env, f2ptr simple_args)

#define def_pmetro0(def_name, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(simple_args) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 0, simple_args);} \
    def_body; \
  }

#define def_pmetro0_and_rest(def_name, def_var0, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    f2ptr def_var0 = simple_args; \
    def_body; \
  }

#define def_pmetro1(def_name, def_var0, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 1) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 1, simple_args);} \
    f2ptr def_var0 = f2cons__car(simple_args, this_cause); \
    def_body; \
  }

#define def_pmetro1_and_rest(def_name, def_var0, def_var1, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 1) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 1, simple_args);} \
    f2ptr simple_args__iter = simple_args; f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
                                           f2ptr def_var1 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro2(def_name, def_var0, def_var1, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 2) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 2, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro2_and_rest(def_name, def_var0, def_var1, def_var2, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 2) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 2, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var2 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro3(def_name, def_var0, def_var1, def_var2, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 3) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 3, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro3_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 3) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 3, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var3 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro4(def_name, def_var0, def_var1, def_var2, def_var3, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 4) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 4, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro4_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 4) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 4, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var4 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro5(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 5) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 5, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
    def_body; \
  }

#define def_pmetro5_and_rest(def_name, def_var0, def_var1, def_var2, def_var3, def_var4, def_var5, def_body) \
  def_pcfunk__symbolvar__define(def_name); \
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 5) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 5, simple_args);} \
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
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) != 6) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 6, simple_args);} \
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
  def_pcfunk__prototype__declare(def_name) { \
    def_pcfunk__this_cause__define(def_name); \
    def_pcfunk__this_symbol__define(def_name); \
    if(!simple_args || raw__length(this_cause, simple_args) < 6) {return f2__argument_number_check_failure__exception__new(this_cause, this_symbol, 6, simple_args);} \
    f2ptr simple_args__iter = simple_args;                                f2ptr def_var0 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var1 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var2 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var3 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var4 = f2cons__car(simple_args__iter, this_cause); \
          simple_args__iter = f2cons__cdr(simple_args__iter, this_cause); f2ptr def_var5 = f2cons__car(simple_args__iter, this_cause); \
                                                                          f2ptr def_var6 = f2cons__cdr(simple_args__iter, this_cause); \
    def_body; \
  }

#define f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, cfunk_args_code) \
  f2ptr c_cfunk_var  = nil; \
  { \
    f2ptr c_cfunk_args = cfunk_args_code; \\
    c_cfunk_var        = f2cfunk__new(initial_cause(), f2symbol__new(initial_cause(), strlen(def_pcfunk__symbolvar_string(name)), (u8*)def_pcfunk__symbolvar_string(name)), c_cfunk_args, f2pointer__new(initial_cause(), to_ptr(def_pcfunk__funkvar(name))), global_environment(), (is_funktional) ? __funk2.globalenv.true__symbol : nil); \
  } \
  { \
    def_pcfunk__symbolvar__init(name); \
    environment__add_funkvar_value(initial_cause(), global_environment(), def_pcfunk__symbolvar(name), c_cfunk_var); \
  }

#define f2__primcfunk__init__with_c_cfunk_var__0_arg(name, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, nil)

#define f2__primcfunk__init__with_c_cfunk_var__0_arg_and_rest(name, and_rest, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list2__new(initial_cause(), f2symbol__new(initial_cause(), strlen(":rest"), (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__1_arg(name, arg0, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list1__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0)))

#define f2__primcfunk__init__with_c_cfunk_var__1_arg_and_rest(name, arg0, and_rest, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list3__new(initial_cause(), f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
													                 f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__2_arg(name, arg0, arg1, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list2__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1)))

#define f2__primcfunk__init__with_c_cfunk_var__2_arg_and_rest(name, arg0, arg1, and_rest, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list4__new(initial_cause(), f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
													                 f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__3_arg(name, arg0, arg1, arg2, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list3__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2), (u8*)#arg2)))

#define f2__primcfunk__init__with_c_cfunk_var__3_arg_and_rest(name, arg0, arg1, arg2, and_rest, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list5__new(initial_cause(), f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2),     (u8*)#arg2) \
													                 f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__4_arg(name, arg0, arg1, arg2, arg3, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list4__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2), (u8*)#arg2), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3), (u8*)#arg3)))

#define f2__primcfunk__init__with_c_cfunk_var__4_arg_and_rest(name, arg0, arg1, arg2, arg3, and_rest, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list6__new(initial_cause(), f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2),     (u8*)#arg2) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3),     (u8*)#arg3) \
													                 f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__5_arg(name, arg0, arg1, arg2, arg3, arg4, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list5__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2), (u8*)#arg2), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3), (u8*)#arg3), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4), (u8*)#arg4)))

#define f2__primcfunk__init__with_c_cfunk_var__5_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, and_rest, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list7__new(initial_cause(), f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2),     (u8*)#arg2) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3),     (u8*)#arg3) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4),     (u8*)#arg4) \
													                 f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var__6_arg(name, arg0, arg1, arg2, arg3, arg4, arg5, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list6__new(initial_cause(), f2symbol__new(initial_cause(), strlen(#arg0), (u8*)#arg0), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1), (u8*)#arg1), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2), (u8*)#arg2), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3), (u8*)#arg3), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4), (u8*)#arg4), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg5), (u8*)#arg5)))

#define f2__primcfunk__init__with_c_cfunk_var__6_arg_and_rest(name, arg0, arg1, arg2, arg3, arg4, arg5, and_rest, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__cfunk_args_code(name, c_cfunk_var, is_funktional, f2list7__new(initial_cause(), f2symbol__new(initial_cause(), strlen(":rest"),   (u8*)":rest"), \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg0),     (u8*)#arg0) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg1),     (u8*)#arg1) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg2),     (u8*)#arg2) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg3),     (u8*)#arg3) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg4),     (u8*)#arg4) \
                                                                                                                         f2symbol__new(initial_cause(), strlen(#arg5),     (u8*)#arg5) \
													                 f2symbol__new(initial_cause(), strlen(#and_rest), (u8*)#and_rest)))

#define f2__primcfunk__init__with_c_cfunk_var(name, c_cfunk_var, is_funktional) \
  f2__primcfunk__init__with_c_cfunk_var__0_arg(name, c_cfunk_var, is_funktional)

#define f2__primcfunk__init(name) { \
  f2__primcfunk__init__with_c_cfunk_var(name, temp_c_cfunk_var, 0); \
}

#define f2__funktional_primcfunk__init(name) { \
  f2__primcfunk__init__with_c_cfunk_var(name, temp_c_cfunk_var, 1); \
}

#define f2__primmetro__init(is_funktional, name) { \
  def_pcfunk__symbolvar__init(name); \
  environment__add_funkvar_value(initial_cause(), global_environment(), def_pcfunk__symbolvar(name), f2metrocfunk__new(initial_cause(), f2symbol__new(initial_cause(), strlen(def_pcfunk__symbolvar_string(name)), (u8*)def_pcfunk__symbolvar_string(name)), f2pointer__new(initial_cause(), to_ptr(def_pcfunk__metrovar(name))), global_environment(), nil)); \
}

#include "f2_memory.h"
#include "f2_ptypes.h"
#include "f2_primobject__environment.h"
#include "f2_primobject__tensor.h"
#include "f2_primobjects.h"
#include "f2_compile.h"
#include "f2_time.h"
#include "f2_gmodule.h"
#include "f2_critic.h"
#include "f2_compile_x86.h"


/////// BEGIN EXTERN DEFS

extern f2ptr __argument_type_check_failure__exception__tag;
extern f2ptr __argument_type_check_failure__exception;
extern f2ptr __argument_number_check_failure__exception__tag;
extern f2ptr __argument_number_check_failure__exception;

f2ptr f2__argument_type_check_failure__exception__new(f2ptr cause, f2ptr value);
f2ptr f2__argument_number_check_failure__exception__new(f2ptr cause, f2ptr funk_symbol, int min_arg_num, f2ptr args);

int raw__length(f2ptr cause, f2ptr seq);
f2ptr f2__length(f2ptr cause, f2ptr seq);
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
bool raw__null(f2ptr x);
f2ptr f2__null(f2ptr cause, f2ptr x);
bool raw__not(f2ptr x);
f2ptr f2__not(f2ptr cause, f2ptr x);

// funk2 pointer (f2ptr)

f2ptr f2__pointer(f2ptr cause, f2ptr x);
f2ptr f2__deref_pointer(f2ptr cause, f2ptr x);

// memblock

f2ptr f2__memblock__set_init_render_xyz(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__memblock__set_init_render_on(f2ptr cause, f2ptr render_on);
f2ptr f2__memblock__set_init_render_noise(f2ptr cause, f2ptr render_noise);
f2ptr f2__memblock__creation_microseconds_since_1970(f2ptr cause, f2ptr x);

// ptype

f2ptr f2__ptype__raw(f2ptr cause, f2ptr x);
f2ptr f2__ptype__cause(f2ptr cause, f2ptr x);
f2ptr f2__ptype__cause__set(f2ptr cause, f2ptr x, f2ptr value);

// integer

bool raw__integerp(f2ptr x, f2ptr cause);
f2ptr f2__integerp(f2ptr cause, f2ptr x);
f2ptr f2__integer__to_double(f2ptr cause, f2ptr x);
f2ptr f2__integer__to_float(f2ptr cause, f2ptr x);

// double

bool raw__doublep(f2ptr x, f2ptr cause);
f2ptr f2__doublep(f2ptr cause, f2ptr x);
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

bool raw__floatp(f2ptr x, f2ptr cause);
f2ptr f2__floatp(f2ptr cause, f2ptr x);
f2ptr f2__float__to_integer(f2ptr cause, f2ptr x);
f2ptr f2__float__to_double(f2ptr cause, f2ptr x);

// pointer

bool raw__pointerp(f2ptr x, f2ptr cause);
f2ptr f2__pointerp(f2ptr cause, f2ptr x);

// gfunkptr

bool raw__gfunkptrp(f2ptr x, f2ptr cause);
f2ptr f2__gfunkptr(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__gfunkptr__new_from_pointer(f2ptr cause, f2ptr x);
f2ptr f2__gfunkptrp(f2ptr cause, f2ptr x);

// mutex

bool raw__mutexp(f2ptr x, f2ptr cause);
f2ptr f2__mutex(f2ptr cause);
f2ptr f2__mutexp(f2ptr cause, f2ptr x);
f2ptr f2__mutex__lock(f2ptr cause, f2ptr x);
f2ptr f2__mutex__unlock(f2ptr cause, f2ptr x);
f2ptr f2__mutex__trylock(f2ptr cause, f2ptr x);

// char

bool raw__charp(f2ptr x, f2ptr cause);

// string

bool raw__stringp(f2ptr x, f2ptr cause);
f2ptr f2__stringp(f2ptr cause, f2ptr x);
f2ptr f2__string__length(f2ptr cause, f2ptr x);
f2ptr f2__string__elt(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__string__eq(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__string__new_raw_c_string(f2ptr cause, f2ptr x);

// symbol

bool  raw__symbolp(f2ptr x, f2ptr cause);
f2ptr f2__symbolp(f2ptr cause, f2ptr x);
f2ptr f2__symbol__length(f2ptr cause, f2ptr x);
f2ptr f2__symbol__elt(f2ptr cause, f2ptr x, f2ptr y);
bool  raw__symbol__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__symbol__eq(f2ptr cause, f2ptr x, f2ptr y);

// array

bool  raw__cause_is_traced(f2ptr cause);
f2ptr raw__array__new(f2ptr cause, u64 length);
f2ptr raw__array__new_copy(f2ptr cause, u64 length, f2ptr init);
bool  raw__arrayp(f2ptr x, f2ptr cause);
f2ptr f2__arrayp(f2ptr cause, f2ptr x);
u64   raw__array__length(f2ptr cause, f2ptr x);
f2ptr f2__array__length(f2ptr cause, f2ptr x);
f2ptr raw__array__elt(f2ptr cause, f2ptr this, u64 index);
f2ptr f2__array__elt(f2ptr cause, f2ptr this, f2ptr index);
f2ptr raw__array__elt__set(f2ptr cause, f2ptr this, u64 index, f2ptr value);
f2ptr f2__array__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr raw__array__elt__set__trace_depth(f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth);
f2ptr raw__array__elt__tracing_on(f2ptr cause, f2ptr this, u64 index);
f2ptr f2__array__elt__tracing_on(f2ptr cause, f2ptr this, f2ptr index);
f2ptr raw__array__elt__tracing_on__set(f2ptr cause, f2ptr this, u64 index, f2ptr value);
f2ptr f2__array__elt__tracing_on__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr raw__array__elt__trace(f2ptr cause, f2ptr this, u64 index);
f2ptr f2__array__elt__trace(f2ptr cause, f2ptr this, f2ptr index);
f2ptr raw__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr f2__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr raw__array__elt__imagination_frame(f2ptr cause, f2ptr this, u64 index);
f2ptr f2__array__elt__imagination_frame(f2ptr cause, f2ptr this, f2ptr index);
f2ptr raw__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr f2__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);

// larva

bool raw__larvap(f2ptr x, f2ptr cause);

// place

bool raw__placep(f2ptr x, f2ptr cause);
f2ptr f2__place(f2ptr cause, f2ptr x);
f2ptr f2__placep(f2ptr cause, f2ptr x);
f2ptr f2__place__thing(f2ptr cause, f2ptr x);
f2ptr f2__place__thing__set(f2ptr cause, f2ptr x, f2ptr y);

// cons

bool raw__consp(f2ptr x, f2ptr cause);
f2ptr f2__cons(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__consp(f2ptr cause, f2ptr x);
f2ptr f2__cons__car(f2ptr cause, f2ptr x);
f2ptr f2__cons__car__set(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__cons__cdr(f2ptr cause, f2ptr x);
f2ptr f2__cons__cdr__set(f2ptr cause, f2ptr x, f2ptr y);

// doublelink

bool raw__doublelinkp(f2ptr x, f2ptr cause);
f2ptr f2__doublelink(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__doublelinkp(f2ptr cause, f2ptr x);
f2ptr f2__doublelink__prev(f2ptr cause, f2ptr x);
f2ptr f2__doublelink__prev__set(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__doublelink__next(f2ptr cause, f2ptr x);
f2ptr f2__doublelink__next__set(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__doublelink__value(f2ptr cause, f2ptr x);
f2ptr f2__doublelink__value__set(f2ptr cause, f2ptr x, f2ptr y);

// chunk

f2ptr f2__chunk(f2ptr cause, f2ptr length);
bool raw__chunkp(f2ptr x, f2ptr cause);
f2ptr f2__chunkp(f2ptr cause, f2ptr x);
f2ptr f2__chunk__length(f2ptr cause, f2ptr x);
f2ptr f2__chunk__bytes(f2ptr cause, f2ptr x);
f2ptr f2__chunk__new_compiled_from_funk(f2ptr cause, f2ptr x);

// primobject hashtable

// primobject thought_process

bool raw__thought_processp(f2ptr x, f2ptr cause);

// primobject thread

void f2thread__force_funk(f2ptr thread, f2ptr cause, f2ptr cfunkable, f2ptr args);
void f2thread__funk(f2ptr thread, f2ptr cause, f2ptr cfunkable, f2ptr args);
f2ptr f2__thread(f2ptr cause, f2ptr parent_thread, f2ptr parent_env, f2ptr cfunkable, f2ptr args);
f2ptr f2__thread_serial(f2ptr cause, f2ptr parent_thread, f2ptr parent_env, f2ptr cfunkable, f2ptr args);

// sequence (array, list, doublelist, etc.)

f2ptr raw__seq_elt(f2ptr this, f2ptr index, f2ptr cause);

// primobject cfunk

bool raw__cfunkp(f2ptr x, f2ptr cause);

// primobject funk

bool raw__funkp(f2ptr x, f2ptr cause);

// primobject metro

bool raw__metrop(f2ptr x, f2ptr cause);

// primobject metrocfunk

bool raw__metrocfunkp(f2ptr x, f2ptr cause);

// primobject bytecode

bool raw__bytecodep(f2ptr x, f2ptr cause);

// primobject cause

bool raw__causep(f2ptr x, f2ptr cause);

// primobject thread

bool raw__threadp(f2ptr x, f2ptr cause);

// primobject exception


// interface funkable (includes types: funk, metro, cfunk, metrocfunk)

bool raw__funkablep(f2ptr exp, f2ptr cause);
  
  
bool raw__exceptionp(f2ptr x, f2ptr cause);
f2ptr f2__exception(f2ptr cause, f2ptr tag, f2ptr value);
f2ptr f2__format(f2ptr cause, f2ptr fptr, f2ptr exp);
f2ptr f2__format__html(f2ptr cause, f2ptr fptr, f2ptr exp);
f2ptr f2__list(f2ptr cause, f2ptr seq);
void raw__exit(int value);
f2ptr f2__quit(f2ptr cause, f2ptr value);
f2ptr f2__seq_elt__set(f2ptr this, f2ptr index, f2ptr cause, f2ptr value);
bool raw__eq(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__eq(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__fopen(f2ptr cause, f2ptr filename, f2ptr mode);
f2ptr f2__fclose(f2ptr cause, f2ptr fptr);
f2ptr f2__compile(f2ptr cause, f2ptr thread, f2ptr tracewrap, f2ptr exp, f2ptr protect_environment);
f2ptr f2__identity(f2ptr cause, f2ptr exp);
f2ptr f2__make_funk(f2ptr cause, f2ptr thread, f2ptr tracewrap, f2ptr name, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr bytecodes, f2ptr is_funktional);
f2ptr f2__make_metro(f2ptr cause, f2ptr thread, f2ptr tracewrap, f2ptr name, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr bytecodes, f2ptr is_funktional);
f2ptr f2__cfunk__apply(f2ptr cause, f2ptr cfunk, f2ptr thread, f2ptr args);
f2ptr f2__metrocfunk__apply(f2ptr cause, f2ptr metrocfunk, f2ptr thread, f2ptr args);
f2ptr f2__random(f2ptr cause, f2ptr max_value);
f2ptr f2__array__new(f2ptr cause, u64 length);
f2ptr f2__array__new_1d(f2ptr cause, f2ptr length, f2ptr and_rest);
f2ptr f2__array(f2ptr cause, f2ptr and_rest);
f2ptr f2__chunk_copy(f2ptr cause, f2ptr init);
f2ptr f2__chunk__read_8bit(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr f2__chunk__write_8bit_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value);
f2ptr f2__chunk__read_8bit_signed(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr f2__chunk__read_16bit(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr f2__chunk__write_16bit_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value);
f2ptr f2__chunk__read_16bit_signed(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr f2__chunk__read_32bit(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr f2__chunk__write_32bit_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value);
f2ptr f2__chunk__read_32bit_signed(f2ptr cause, f2ptr chunk, f2ptr offset);
f2ptr f2__demetropolize_full(f2ptr cause, f2ptr thread, f2ptr env, f2ptr exp);
f2ptr f2__exps_demetropolize_full(f2ptr cause, f2ptr thread, f2ptr env, f2ptr exp);
f2ptr f2__lookup_funkvar(f2ptr cause, f2ptr env, f2ptr funkvar, f2ptr undefined_value);
f2ptr f2__wrong_argument_number_error__set(f2ptr cause, f2ptr error_bcs);
f2ptr f2__jump_to_chunk(f2ptr cause, f2ptr thread, f2ptr env, f2ptr exp, f2ptr args);
f2ptr f2__coerce_to_int(f2ptr cause, f2ptr exp);
f2ptr f2__memory_image__save(f2ptr cause, f2ptr filename);
f2ptr f2__memory_image__load(f2ptr cause, f2ptr filename);
void f2__primcfunks__reinitialize_globalvars();
void f2__primcfunks__initialize();

#endif // F2__PRIMCFUNKS__H
