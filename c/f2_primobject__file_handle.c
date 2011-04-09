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

#include "funk2.h"

// file_handle

def_primobject_1_slot(file_handle,
		      file_descriptor);

f2ptr raw__file_handle__new(f2ptr cause, s64 file_descriptor) {
  return f2file_handle__new(cause,
			    f2integer__new(cause, file_descriptor));
}

f2ptr f2__file_handle__new(f2ptr cause, f2ptr file_descriptor) {
  assert_argument_type(integer, file_descriptor);
  s64 file_descriptor__i = f2integer__i(file_descriptor, cause);
  return raw__file_handle__new(cause, file_descriptor__i);
}
def_pcfunk1(file_handle__new, file_descriptor,
	    "Returns a new file_handle object for the given integral file_descriptor.",
	    return f2__file_handle__new(this_cause, file_descriptor));


f2ptr raw__file_handle__close(f2ptr cause, f2ptr this) {
  f2ptr file_descriptor = f2__file_handle__file_descriptor(cause, this);
  if (! raw__integer__is_type(cause, file_descriptor)) {
    return f2larva__new(cause, 13515611, nil);
  }
  int fd = f2integer__i(file_descriptor, cause);
  int result = close(fd);
  if (result == -1) {
    return nil;
  }
  return f2integer__new(cause, result);
}

f2ptr f2__file_handle__close(f2ptr cause, f2ptr this) {
  assert_argument_type(file_handle, this);
  return raw__file_handle__close(cause, this);
}
def_pcfunk1(file_handle__close, this,
	    "Closes this file_handle.",
	    return f2__file_handle__close(this_cause, this));


int raw__file_handle__nonblocking__set(f2ptr cause, f2ptr this, boolean_t value) {
  f2ptr file_descriptor = f2file_handle__file_descriptor(this, cause);
  s64   fd              = f2integer__i(file_descriptor, cause);
  return file_descriptor__set_nonblocking(fd, value);
}

f2ptr f2__file_handle__nonblocking__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(file_handle, this);
  return f2integer__new(cause, raw__file_handle__nonblocking__set(cause, this, (value != nil)));
}
def_pcfunk2(file_handle__nonblocking__set, this, value,
	    "Sets the nonblocking status of this file_handle.",
	    return f2__file_handle__nonblocking__set(this_cause, this, value));


f2ptr raw__file_handle__try_read_character(f2ptr cause, f2ptr this) {
  f2ptr file_descriptor = f2file_handle__file_descriptor(this, cause);
  if (! raw__integer__is_type(cause, file_descriptor)) {return f2larva__new(cause, 172462, nil);}
  u64 fd = f2integer__i(file_descriptor, cause);
  u8  data[2] = {0, 0};
  u32 bytes_read = 0;
  read_nonblocking_result_t result = read_nonblocking(fd, data, 1, &bytes_read);
  switch (result) {
  case read_nonblocking_result__success:
    if (bytes_read == 1) {
      return f2char__new(cause, data[0]);
    }
    break;
  case read_nonblocking_result__end_of_file:
    return f2larva__new(cause, 23515, nil);
  case read_nonblocking_result__read_failure:
  case read_nonblocking_result__select_failure:
  case read_nonblocking_result__unknown_failure:
    break;
  }
  return nil;
}

f2ptr f2__file_handle__try_read_character(f2ptr cause, f2ptr this) {
  assert_argument_type(file_handle, this);
  return raw__file_handle__try_read_character(cause, this);
}
def_pcfunk1(file_handle__try_read_character, this,
	    "Tries to read one character from the file_handle.  "
	    "If the file_handle is set to non-blocking mode and no character is waiting, nil is returned.  "
	    "If end of file is reached, bug is returned.  ",
	    return f2__file_handle__try_read_character(this_cause, this));


f2ptr raw__file_handle__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "file_handle"),
					       new__symbol(cause, "file_descriptor"),   f2__file_handle__file_descriptor(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__file_handle__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(file_handle,          this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__file_handle__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(file_handle__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this file_handle to the given terminal.",
	    return f2__file_handle__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2file_handle__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2file_handle__primobject_type__new(cause);
  {char* slot_name = "close";                     f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_file_handle.close__funk);}
  {char* slot_name = "nonblocking";               f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_file_handle.nonblocking__set__funk);}
  {char* slot_name = "try_read_character";        f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_file_handle.try_read_character__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_file_handle.terminal_print_with_frame__funk);}
  return this;
}



// **

void f2__primobject__file_handle__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  __file_handle__symbol = new__symbol(cause, "file_handle");
}

void f2__primobject__file_handle__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "file_handle", "", &f2__primobject__file_handle__reinitialize_globalvars);
  
  f2__primobject__file_handle__reinitialize_globalvars();
  
  // file_handle
  
  initialize_primobject_1_slot(file_handle,
			       file_descriptor);
  
  {char* symbol_str = "close"; __funk2.globalenv.object_type.primobject.primobject_type_file_handle.close__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(file_handle__close, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_file_handle.close__funk = never_gc(cfunk);}
  {char* symbol_str = "nonblocking-set"; __funk2.globalenv.object_type.primobject.primobject_type_file_handle.nonblocking__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(file_handle__nonblocking__set, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_file_handle.nonblocking__set__funk = never_gc(cfunk);}
  {char* symbol_str = "try_read_character"; __funk2.globalenv.object_type.primobject.primobject_type_file_handle.try_read_character__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(file_handle__try_read_character, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_file_handle.try_read_character__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_file_handle.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(file_handle__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_file_handle.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}

