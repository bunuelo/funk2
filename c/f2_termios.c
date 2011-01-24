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

int raw__termios__noecho() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ECHO;
  return tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

f2ptr f2__termios__noecho(f2ptr cause) {
  return f2integer__new(cause, raw__termios__noecho());
}
def_pcfunk0(termios__noecho, return f2__termios__noecho(this_cause));

int raw__termios__echo() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag |= ECHO;
  return tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

f2ptr f2__termios__echo(f2ptr cause) {
  return f2integer__new(cause, raw__termios__echo());
}
def_pcfunk0(termios__echo, return f2__termios__echo(this_cause));


int raw__termios__nocanon() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ICANON;
  return tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

f2ptr f2__termios__nocanon(f2ptr cause) {
  return f2integer__new(cause, raw__termios__nocanon());
}
def_pcfunk0(termios__nocanon, return f2__termios__nocanon(this_cause));


int raw__termios__canon() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag |= ICANON;
  return tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

f2ptr f2__termios__canon(f2ptr cause) {
  return f2integer__new(cause, raw__termios__canon());
}
def_pcfunk0(termios__canon, return f2__termios__canon(this_cause));

// **

void f2__termios__reinitialize_globalvars() {
  //f2ptr cause = f2_termios_c__cause__new(initial_cause());
  // set global (funk2_t) __funk2 variables
}

void f2__termios__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "termios", "", &f2__termios__reinitialize_globalvars);
  
  f2__termios__reinitialize_globalvars();
  
  f2__primcfunk__init(termios__width, "returns the current width of the terminal. (as defined in termios.h)");
  f2__primcfunk__init(termios__height, "returns the current height of the terminal.  (as defined in termios.h)");
  f2__primcfunk__init(termios__noecho, "(as defined in termios.h)");
  f2__primcfunk__init(termios__echo, "(as defined in termios.h)");
  f2__primcfunk__init(termios__nocanon, "(as defined in termios.h)");
  f2__primcfunk__init(termios__canon, "(as defined in termios.h)");
}


