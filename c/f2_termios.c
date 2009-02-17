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

#include "funk2.h"

int raw__termios__height() {
  struct winsize winsize_arg;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize_arg);
  return winsize_arg.ws_row;
}

f2ptr f2__termios__height(f2ptr cause) {
  return f2integer__new(cause, raw__termios__height());
}
def_pcfunk0(termios__height, return f2__termios__height(this_cause));

int raw__termios__width() {
  struct winsize winsize_arg;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize_arg);
  return winsize_arg.ws_col;
}

f2ptr f2__termios__width(f2ptr cause) {
  return f2integer__new(cause, raw__termios__width());
}
def_pcfunk0(termios__width, return f2__termios__width(this_cause));

// **

void f2__termios__reinitialize_globalvars() {
  //f2ptr cause = f2_termios_c__cause__new(initial_cause());
  // set global (funk2_t) __funk2 variables
}

void f2__termios__initialize() {
  pause_gc();
  
  //f2ptr cause = f2_termios_c__cause__new(initial_cause());
  
  f2__termios__reinitialize_globalvars();
  
  f2__primcfunk__init(termios__width);
  f2__primcfunk__init(termios__height);
  
  resume_gc();
  try_gc();
}


