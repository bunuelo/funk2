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

#include "funk2.h"

f2ptr raw__nil__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__nil__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, 2, (u8*)"[]");
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__nil__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if ((this != nil) ||
      (! raw__terminal_print_frame__is_type(cause, terminal_print_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__nil__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(nil__terminal_print_with_frame, this, terminal_print_frame, return f2__nil__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2nil__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, nil);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.nil_type.terminal_print_with_frame__funk);}
  return this;
}


// **

void f2__nil__reinitialize_globalvars() {
}

void f2__nil__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "nil", "the unique object", &f2__nil__reinitialize_globalvars);
  
  f2__nil__reinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.nil_type.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(nil__terminal_print_with_frame, this, terminal_print_frame, cfunk, 1, "prints the nil value using the given terminal_print_frame object."); __funk2.globalenv.object_type.nil_type.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}

