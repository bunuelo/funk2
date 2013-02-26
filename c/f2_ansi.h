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

#ifndef F2__ANSI__TYPES__H
#define F2__ANSI__TYPES__H

typedef enum ansi_color_e {
  ansi_color__black        =  0,
  ansi_color__dark_blue    =  1,
  ansi_color__dark_green   =  2,
  ansi_color__dark_cyan    =  3,
  ansi_color__dark_red     =  4,
  ansi_color__dark_purple  =  5,
  ansi_color__brown        =  6,
  ansi_color__light_gray   =  7,
  ansi_color__dark_gray    =  8,
  ansi_color__light_blue   =  9,
  ansi_color__light_green  = 10,
  ansi_color__light_cyan   = 11,
  ansi_color__light_red    = 12,
  ansi_color__light_purple = 13,
  ansi_color__yellow       = 14,
  ansi_color__white        = 15
} ansi_color_t;

#endif // F2__ANSI__TYPES__H


#ifndef F2__ANSI__H
#define F2__ANSI__H

#include "f2_primfunks.h"
#include "f2_status.h"

void raw__ansi__stream__print_code(f2ptr cause, f2ptr stream, int code);
f2ptr f2__ansi__stream__print_code(f2ptr cause, f2ptr stream, f2ptr code);
f2ptr f2__ansi__stream__reset(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__bold(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__half_bright(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__underscore(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__blink(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__reverse_video(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__normal_intensity(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__underline_off(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__blink_off(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__reverse_video_off(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__black_foreground(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__red_foreground(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__green_foreground(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__brown_foreground(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__blue_foreground(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__magenta_foreground(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__cyan_foreground(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__white_foreground(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__underscore_with_default_foreground(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__underscore_off_with_default_foreground(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__black_background(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__red_background(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__green_background(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__brown_background(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__blue_background(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__magenta_background(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__cyan_background(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__white_background(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__default_background(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__clear_screen(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__clear_keyboard_leds(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__set_scroll_lock_led(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__set_num_lock_led(f2ptr cause, f2ptr stream);
f2ptr f2__ansi__stream__set_caps_lock_led(f2ptr cause, f2ptr stream);
void raw__ansi__stream__move_cursor(f2ptr cause, f2ptr stream, int x, int y);
f2ptr f2__ansi__stream__move_cursor(f2ptr cause, f2ptr stream, f2ptr x, f2ptr y);
f2ptr f2__ansi__stream__beep(f2ptr cause, f2ptr stream);
f2ptr raw__ansi__stream__foreground(f2ptr cause, f2ptr stream, ansi_color_t color);
f2ptr f2__ansi__stream__foreground(f2ptr cause, f2ptr stream, f2ptr color);
f2ptr raw__ansi__stream__background(f2ptr cause, f2ptr stream, ansi_color_t color);
f2ptr f2__ansi__stream__background(f2ptr cause, f2ptr stream, f2ptr color);
void raw__ansi__stream__rectangle(f2ptr cause, f2ptr stream, s64 x0, s64 y0, s64 x1, s64 y1, u8 ch);
f2ptr f2__ansi__stream__rectangle(f2ptr cause, f2ptr stream, f2ptr x0, f2ptr y0, f2ptr x1, f2ptr y1, f2ptr ch);
void raw__ansi__stream__bordered_rectangle(f2ptr cause, f2ptr stream, int x0, int y0, int x1, int y1, char background_char);
f2ptr f2__ansi__stream__bordered_rectangle(f2ptr cause, f2ptr stream, f2ptr x0, f2ptr y0, f2ptr x1, f2ptr y1, f2ptr background_char);

// **

void f2__ansi__reinitialize_globalvars();
void f2__ansi__initialize();

#endif // F2__ANSI__H
