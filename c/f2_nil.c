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

#include "funk2.h"

f2ptr raw__nil__as__string(f2ptr cause, f2ptr this) {
  return new__string(cause, "[]");
}

boolean_t raw__nil__is_type(f2ptr cause, f2ptr this) {
  return (this == nil);
}

f2ptr f2__nil__as__string(f2ptr cause, f2ptr this) {
  assert_argument_type(nil, this);
  return raw__nil__as__string(cause, this);
}
def_pcfunk1(nil__as__string, this,
	    "returns the string '[]'.",
	    return f2__nil__as__string(this_cause, this));


f2ptr raw__nil__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  {
    u64               temp_str__length = 2;
    funk2_character_t temp_str[2];
    temp_str[0] = f2char__ch(__funk2.reader.char__left_paren,  cause);
    temp_str[1] = f2char__ch(__funk2.reader.char__right_paren, cause);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__nil__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, temp_str__length, temp_str);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  }
  return nil;
}

f2ptr f2__nil__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(nil,                  this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__nil__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(nil__terminal_print_with_frame, this, terminal_print_frame,
	    "prints the nil value using the given terminal_print_frame object.",
	    return f2__nil__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2nil__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, nil);
  {char* slot_name = "as-string";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.nil_type.as__string__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.nil_type.terminal_print_with_frame__funk);}
  return this;
}


// **

void f2__nil__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  defragment__fix_pointer(__funk2.globalenv.object_type.nil_type.as__string__symbol);
  f2__primcfunk__init__defragment__fix_pointers(nil__as__string);
  defragment__fix_pointer(__funk2.globalenv.object_type.nil_type.as__string__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.nil_type.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(nil__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.nil_type.terminal_print_with_frame__funk);
}

void f2__nil__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  {char* str = "as-string"; __funk2.globalenv.object_type.nil_type.as__string__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(nil__as__string, this, cfunk); __funk2.globalenv.object_type.nil_type.as__string__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.nil_type.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(nil__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.nil_type.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__nil__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "nil", "the unique object", &f2__nil__reinitialize_globalvars, &f2__nil__defragment__fix_pointers);
  
  f2__nil__reinitialize_globalvars();
}

