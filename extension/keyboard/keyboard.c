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

#include "keyboard.h"


f2ptr funk2_keyboard__getch(f2ptr cause, int file_descriptor) {
  struct termios org_opts, new_opts;
  //-----  store old settings -----------
  int res = tcgetattr(file_descriptor, &org_opts);
  if (res != 0) {
    return f2larva__new(cause, 62351, nil);
  }
  //---- set new terminal parms --------
  memcpy(&new_opts, &org_opts, sizeof(new_opts));
  new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
  tcsetattr(file_descriptor, TCSANOW, &new_opts);
  s64 ch = getchar();
  //------  restore old settings ---------
  res=tcsetattr(file_descriptor, TCSANOW, &org_opts);
  if (res != 0) {
    return f2larva__new(cause, 62352, nil);
  }
  return f2integer__new(cause, ch);
}

f2ptr raw__keyboard__getch(f2ptr cause, f2ptr file_descriptor) {
  int file_descriptor__i = f2integer__i(file_descriptor, cause);
  return funk2_keyboard__getch(cause, file_descriptor__i);
}

f2ptr f2__keyboard__getch(f2ptr cause, f2ptr file_descriptor) {
  assert_argument_type(integer, file_descriptor);
  return raw__keyboard__getch(cause, file_descriptor);
}
export_cefunk1(keyboard__getch, file_descriptor, 0, "Get current key from keyboard without waiting.");


// **

f2ptr f2__keyboard__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(keyboard__core_extension__ping, 0, "");

f2ptr f2__keyboard__core_extension__initialize(f2ptr cause) {
  status("keyboard initialized.");
  return nil;
}
export_cefunk0(keyboard__core_extension__initialize, 0, "");

f2ptr f2__keyboard__core_extension__define_types(f2ptr cause) {
  status("keyboard types defined.");
  return nil;
}
export_cefunk0(keyboard__core_extension__define_types, 0, "");

f2ptr f2__keyboard__core_extension__destroy(f2ptr cause) {
  status("keyboard destroyed.");
  return nil;
}
export_cefunk0(keyboard__core_extension__destroy, 0, "");


