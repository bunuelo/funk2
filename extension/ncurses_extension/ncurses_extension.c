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

#include "ncurses_extension.h"

#if F2__NCURSESW_SUPPORTED
#  include <ncurses.h>
#endif // F2__NCURSESW_SUPPORTED

void funk2_ncurses_extension__test() {
  setlocale(LC_ALL,"");
  initscr();
  curs_set(0); //remove cursor
  addstr("\u2019"); //Print out the unicode character
  refresh(); //update screen
  getch();  //wait for input
  endwin();
}

#endif


f2ptr f2__ncurses_extension__test(f2ptr cause) {
#if F2__NCURSESW_SUPPORTED
  funk2_ncurses_extension__test();
#endif
  return nil;
}
export_cefunk0(ncurses_extension__test, 0, "");


// **

f2ptr f2__ncurses_extension__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(ncurses_extension__core_extension__ping, 0, "");

f2ptr f2__ncurses_extension__core_extension__initialize(f2ptr cause) {
  status("ncurses_extension initialized.");
  return nil;
}
export_cefunk0(ncurses_extension__core_extension__initialize, 0, "");

f2ptr f2__ncurses_extension__core_extension__define_types(f2ptr cause) {
  status("ncurses_extension types defined.");
  return nil;
}
export_cefunk0(ncurses_extension__core_extension__define_types, 0, "");

f2ptr f2__ncurses_extension__core_extension__destroy(f2ptr cause) {
  status("ncurses_extension destroyed.");
  return nil;
}
export_cefunk0(ncurses_extension__core_extension__destroy, 0, "");


