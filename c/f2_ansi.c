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

void raw__ansi__stream__write(f2ptr cause, f2ptr stream, f2ptr string) {
  f2__cmutex__lock(cause, f2__stream__cmutex(cause, stream));
  u64 string__utf8_length = raw__string__utf8_length(cause, string);
  u8* string__utf8_str    = (u8*)from_ptr(f2__malloc(string__utf8_length + 1));
  raw__string__utf8_str_copy(cause, string, string__utf8_str);
  string__utf8_str[string__utf8_length] = 0;
  raw__stream__writef(cause, stream, "%s", string__utf8_str);
  f2__cmutex__unlock(cause, f2__stream__cmutex(cause, stream));
}

f2ptr f2__ansi__stream__write(f2ptr cause, f2ptr stream, f2ptr string) {
  assert_argument_type(stream, stream);
  assert_argument_type(string, string);
  raw__ansi__stream__write(cause, stream, string);
  return nil;
}
def_pcfunk2(ansi__stream__write, stream, string,
	    "",
	    return f2__ansi__stream__write(this_cause, stream, string));



void raw__ansi__stream__print_code(f2ptr cause, f2ptr stream, int code) {
  f2__cmutex__lock(cause, f2__stream__cmutex(cause, stream));
  raw__stream__writef(cause, stream, "%c[%dm", 27, code);
  f2__cmutex__unlock(cause, f2__stream__cmutex(cause, stream));
}

f2ptr f2__ansi__stream__print_code(f2ptr cause, f2ptr stream, f2ptr code) {
  assert_argument_type(stream,  stream);
  assert_argument_type(integer, code);
  int raw_code = f2integer__i(code, cause);
  raw__ansi__stream__print_code(cause, stream, raw_code);
  return nil;
}
def_pcfunk2(ansi__stream__print_code, stream, code,
	    "",
	    return f2__ansi__stream__print_code(this_cause, stream, code));



f2ptr f2__ansi__stream__reset(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 0);
  return nil;
}
def_pcfunk1(ansi__stream__reset, stream,
	    "",
	    return f2__ansi__stream__reset(this_cause, stream));

f2ptr f2__ansi__stream__bold(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 1);
  return nil;
}
def_pcfunk1(ansi__stream__bold, stream,
	    "",
	    return f2__ansi__stream__bold(this_cause, stream));

f2ptr f2__ansi__stream__half_bright(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 2);
  return nil;
}
def_pcfunk1(ansi__stream__half_bright, stream,
	    "",
	    return f2__ansi__stream__half_bright(this_cause, stream));

f2ptr f2__ansi__stream__underscore(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 4);
  return nil;
}
def_pcfunk1(ansi__stream__underscore, stream,
	    "",
	    return f2__ansi__stream__underscore(this_cause, stream));

f2ptr f2__ansi__stream__blink(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 5);
  return nil;
}
def_pcfunk1(ansi__stream__blink, stream,
	    "",
	    return f2__ansi__stream__blink(this_cause, stream));

f2ptr f2__ansi__stream__reverse_video(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 7);
  return nil;
}
def_pcfunk1(ansi__stream__reverse_video, stream,
	    "",
	    return f2__ansi__stream__reverse_video(this_cause, stream));

f2ptr f2__ansi__stream__normal_intensity(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 22);
  return nil;
}
def_pcfunk1(ansi__stream__normal_intensity, stream,
	    "",
	    return f2__ansi__stream__normal_intensity(this_cause, stream));

f2ptr f2__ansi__stream__underline_off(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 24);
  return nil;
}
def_pcfunk1(ansi__stream__underline_off, stream,
	    "",
	    return f2__ansi__stream__underline_off(this_cause, stream));

f2ptr f2__ansi__stream__blink_off(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 25);
  return nil;
}
def_pcfunk1(ansi__stream__blink_off, stream,
	    "",
	    return f2__ansi__stream__blink_off(this_cause, stream));

f2ptr f2__ansi__stream__reverse_video_off(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 27);
  return nil;
}
def_pcfunk1(ansi__stream__reverse_video_off, stream,
	    "",
	    return f2__ansi__stream__reverse_video_off(this_cause, stream));

f2ptr f2__ansi__stream__black_foreground(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 30);
  return nil;
}
def_pcfunk1(ansi__stream__black_foreground, stream,
	    "",
	    return f2__ansi__stream__black_foreground(this_cause, stream));

f2ptr f2__ansi__stream__red_foreground(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 31);
  return nil;
}
def_pcfunk1(ansi__stream__red_foreground, stream,
	    "",
	    return f2__ansi__stream__red_foreground(this_cause, stream));

f2ptr f2__ansi__stream__green_foreground(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 32);
  return nil;
}
def_pcfunk1(ansi__stream__green_foreground, stream,
	    "",
	    return f2__ansi__stream__green_foreground(this_cause, stream));

f2ptr f2__ansi__stream__brown_foreground(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 33);
  return nil;
}
def_pcfunk1(ansi__stream__brown_foreground, stream,
	    "",
	    return f2__ansi__stream__brown_foreground(this_cause, stream));

f2ptr f2__ansi__stream__blue_foreground(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 34);
  return nil;
}
def_pcfunk1(ansi__stream__blue_foreground, stream,
	    "",
	    return f2__ansi__stream__blue_foreground(this_cause, stream));

f2ptr f2__ansi__stream__magenta_foreground(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 35);
  return nil;
}
def_pcfunk1(ansi__stream__magenta_foreground, stream,
	    "",
	    return f2__ansi__stream__magenta_foreground(this_cause, stream));

f2ptr f2__ansi__stream__cyan_foreground(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 36);
  return nil;
}
def_pcfunk1(ansi__stream__cyan_foreground, stream,
	    "",
	    return f2__ansi__stream__cyan_foreground(this_cause, stream));

f2ptr f2__ansi__stream__white_foreground(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 37);
  return nil;
}
def_pcfunk1(ansi__stream__white_foreground, stream,
	    "",
	    return f2__ansi__stream__white_foreground(this_cause, stream));

f2ptr f2__ansi__stream__underscore_with_default_foreground(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 38);
  return nil;
}
def_pcfunk1(ansi__stream__underscore_with_default_foreground, stream,
	    "",
	    return f2__ansi__stream__underscore_with_default_foreground(this_cause, stream));

f2ptr f2__ansi__stream__underscore_off_with_default_foreground(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 39);
  return nil;
}
def_pcfunk1(ansi__stream__underscore_off_with_default_foreground, stream,
	    "",
	    return f2__ansi__stream__underscore_off_with_default_foreground(this_cause, stream));

f2ptr f2__ansi__stream__black_background(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 40);
  return nil;
}
def_pcfunk1(ansi__stream__black_background, stream,
	    "",
	    return f2__ansi__stream__black_background(this_cause, stream));

f2ptr f2__ansi__stream__red_background(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 41);
  return nil;
}
def_pcfunk1(ansi__stream__red_background, stream,
	    "",
	    return f2__ansi__stream__red_background(this_cause, stream));

f2ptr f2__ansi__stream__green_background(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 42);
  return nil;
}
def_pcfunk1(ansi__stream__green_background, stream,
	    "",
	    return f2__ansi__stream__green_background(this_cause, stream));

f2ptr f2__ansi__stream__brown_background(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 43);
  return nil;
}
def_pcfunk1(ansi__stream__brown_background, stream,
	    "",
	    return f2__ansi__stream__brown_background(this_cause, stream));

f2ptr f2__ansi__stream__blue_background(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 44);
  return nil;
}
def_pcfunk1(ansi__stream__blue_background, stream,
	    "",
	    return f2__ansi__stream__blue_background(this_cause, stream));

f2ptr f2__ansi__stream__magenta_background(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 45);
  return nil;
}
def_pcfunk1(ansi__stream__magenta_background, stream,
	    "",
	    return f2__ansi__stream__magenta_background(this_cause, stream));

f2ptr f2__ansi__stream__cyan_background(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 46);
  return nil;
}
def_pcfunk1(ansi__stream__cyan_background, stream,
	    "",
	    return f2__ansi__stream__cyan_background(this_cause, stream));

f2ptr f2__ansi__stream__white_background(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 47);
  return nil;
}
def_pcfunk1(ansi__stream__white_background, stream,
	    "",
	    return f2__ansi__stream__white_background(this_cause, stream));

f2ptr f2__ansi__stream__default_background(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__ansi__stream__print_code(cause, stream, 49);
  return nil;
}
def_pcfunk1(ansi__stream__default_background, stream,
	    "",
	    return f2__ansi__stream__default_background(this_cause, stream));

f2ptr f2__ansi__stream__clear_screen(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  f2__cmutex__lock(cause, f2__stream__cmutex(cause, stream));
  raw__stream__writef(cause, stream, "%c[2J", 27);
  f2__cmutex__unlock(cause, f2__stream__cmutex(cause, stream));
  return nil;
}
def_pcfunk1(ansi__stream__clear_screen, stream,
	    "",
	    return f2__ansi__stream__clear_screen(this_cause, stream));

f2ptr f2__ansi__stream__clear_keyboard_leds(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  f2__cmutex__lock(cause, f2__stream__cmutex(cause, stream));
  raw__stream__writef(cause, stream, "%c[0q", 27);
  f2__cmutex__unlock(cause, f2__stream__cmutex(cause, stream));
  return nil;
}
def_pcfunk1(ansi__stream__clear_keyboard_leds, stream,
	    "",
	    return f2__ansi__stream__clear_keyboard_leds(this_cause, stream));

f2ptr f2__ansi__stream__set_scroll_lock_led(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  f2__cmutex__lock(cause, f2__stream__cmutex(cause, stream));
  raw__stream__writef(cause, stream, "%c[1q", 27);
  f2__cmutex__unlock(cause, f2__stream__cmutex(cause, stream));
  return nil;
}
def_pcfunk1(ansi__stream__set_scroll_lock_led, stream,
	    "",
	    return f2__ansi__stream__set_scroll_lock_led(this_cause, stream));

f2ptr f2__ansi__stream__set_num_lock_led(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  f2__cmutex__lock(cause, f2__stream__cmutex(cause, stream));
  raw__stream__writef(cause, stream, "%c[2q", 27);
  f2__cmutex__unlock(cause, f2__stream__cmutex(cause, stream));
  return nil;
}
def_pcfunk1(ansi__stream__set_num_lock_led, stream,
	    "",
	    return f2__ansi__stream__set_num_lock_led(this_cause, stream));

f2ptr f2__ansi__stream__set_caps_lock_led(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  f2__cmutex__lock(cause, f2__stream__cmutex(cause, stream));
  raw__stream__writef(cause, stream, "%c[3q", 27);
  f2__cmutex__unlock(cause, f2__stream__cmutex(cause, stream));
  return nil;
}
def_pcfunk1(ansi__stream__set_caps_lock_led, stream,
	    "",
	    return f2__ansi__stream__set_caps_lock_led(this_cause, stream));

void raw__ansi__stream__move_cursor(f2ptr cause, f2ptr stream, int x, int y) {
  if (x < 0 || y < 0) {
    return;
  }
  f2__cmutex__lock(cause, f2__stream__cmutex(cause, stream));
  raw__stream__writef(cause, stream, "%c[%d;%dH", 27, y, x);
  f2__cmutex__unlock(cause, f2__stream__cmutex(cause, stream));
}

f2ptr f2__ansi__stream__move_cursor(f2ptr cause, f2ptr stream, f2ptr x, f2ptr y) {
  assert_argument_type(stream,  stream);
  assert_argument_type(integer, x);
  assert_argument_type(integer, y);
  int raw_x = f2integer__i(x, cause);
  int raw_y = f2integer__i(y, cause);
  raw__ansi__stream__move_cursor(cause, stream, raw_x, raw_y);
  return nil;
}
def_pcfunk3(ansi__stream__move_cursor, stream, x, y,
	    "",
	    return f2__ansi__stream__move_cursor(this_cause, stream, x, y));

f2ptr f2__ansi__stream__beep(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  raw__stream__writef(cause, stream, "%c", 7);
  return nil;
}
def_pcfunk1(ansi__stream__beep, stream,
	    "",
	    return f2__ansi__stream__beep(this_cause, stream));


f2ptr raw__ansi__stream__foreground(f2ptr cause, f2ptr stream, ansi_color_t color) {
  switch(color) {
  case ansi_color__black:        f2__ansi__stream__normal_intensity(cause, stream); return f2__ansi__stream__black_foreground(                      cause, stream);
  case ansi_color__dark_blue:    f2__ansi__stream__normal_intensity(cause, stream); return f2__ansi__stream__blue_foreground(                       cause, stream);
  case ansi_color__dark_green:   f2__ansi__stream__normal_intensity(cause, stream); return f2__ansi__stream__green_foreground(                      cause, stream);
  case ansi_color__dark_cyan:    f2__ansi__stream__normal_intensity(cause, stream); return f2__ansi__stream__cyan_foreground(                       cause, stream);
  case ansi_color__dark_red:     f2__ansi__stream__normal_intensity(cause, stream); return f2__ansi__stream__red_foreground(                        cause, stream);
  case ansi_color__dark_purple:  f2__ansi__stream__normal_intensity(cause, stream); return f2__ansi__stream__magenta_foreground(                    cause, stream);
  case ansi_color__brown:        f2__ansi__stream__normal_intensity(cause, stream); return f2__ansi__stream__brown_foreground(                      cause, stream);
  case ansi_color__light_gray:   f2__ansi__stream__normal_intensity(cause, stream); return f2__ansi__stream__white_foreground(                      cause, stream);
  case ansi_color__dark_gray:    f2__ansi__stream__bold(            cause, stream); return f2__ansi__stream__black_foreground(                      cause, stream);
  case ansi_color__light_blue:   f2__ansi__stream__bold(            cause, stream); return f2__ansi__stream__blue_foreground(                       cause, stream);
  case ansi_color__light_green:  f2__ansi__stream__bold(            cause, stream); return f2__ansi__stream__green_foreground(                      cause, stream);
  case ansi_color__light_cyan:   f2__ansi__stream__bold(            cause, stream); return f2__ansi__stream__cyan_foreground(                       cause, stream);
  case ansi_color__light_red:    f2__ansi__stream__bold(            cause, stream); return f2__ansi__stream__red_foreground(                        cause, stream);
  case ansi_color__light_purple: f2__ansi__stream__bold(            cause, stream); return f2__ansi__stream__magenta_foreground(                    cause, stream);
  case ansi_color__yellow:       f2__ansi__stream__bold(            cause, stream); return f2__ansi__stream__brown_foreground(                      cause, stream);
  case ansi_color__white:        f2__ansi__stream__bold(            cause, stream); return f2__ansi__stream__underscore_off_with_default_foreground(cause, stream);
  }
  return nil;
}

f2ptr f2__ansi__stream__foreground(f2ptr cause, f2ptr stream, f2ptr color) {
  assert_argument_type(stream,  stream);
  assert_argument_type(integer, color);
  ansi_color_t raw_color = (ansi_color_t)f2integer__i(color, cause);
  return raw__ansi__stream__foreground(cause, stream, raw_color);
}
def_pcfunk2(ansi__stream__foreground, stream, color,
	    "",
	    return f2__ansi__stream__foreground(this_cause, stream, color));

f2ptr raw__ansi__stream__background(f2ptr cause, f2ptr stream, ansi_color_t color) {
  switch(color) {
  case ansi_color__black:        return f2__ansi__stream__black_background(  cause, stream);
  case ansi_color__dark_blue:    return f2__ansi__stream__blue_background(   cause, stream);
  case ansi_color__dark_green:   return f2__ansi__stream__green_background(  cause, stream);
  case ansi_color__dark_cyan:    return f2__ansi__stream__cyan_background(   cause, stream);
  case ansi_color__dark_red:     return f2__ansi__stream__red_background(    cause, stream);
  case ansi_color__dark_purple:  return f2__ansi__stream__magenta_background(cause, stream);
  case ansi_color__brown:        return f2__ansi__stream__brown_background(  cause, stream);
  case ansi_color__light_gray:   return f2__ansi__stream__white_background(  cause, stream);
  case ansi_color__dark_gray:    return f2__ansi__stream__black_background(  cause, stream);
  case ansi_color__light_blue:   return f2__ansi__stream__blue_background(   cause, stream);
  case ansi_color__light_green:  return f2__ansi__stream__green_background(  cause, stream);
  case ansi_color__light_cyan:   return f2__ansi__stream__cyan_background(   cause, stream);
  case ansi_color__light_red:    return f2__ansi__stream__red_background(    cause, stream);
  case ansi_color__light_purple: return f2__ansi__stream__magenta_background(cause, stream);
  case ansi_color__yellow:       return f2__ansi__stream__brown_background(  cause, stream);
  case ansi_color__white:        return f2__ansi__stream__white_background(  cause, stream);
  }
  return nil;
}

f2ptr f2__ansi__stream__background(f2ptr cause, f2ptr stream, f2ptr color) {
  assert_argument_type(stream,  stream);
  assert_argument_type(integer, color);
  ansi_color_t raw_color = (ansi_color_t)f2integer__i(color, cause);
  return raw__ansi__stream__background(cause, stream, raw_color);
}
def_pcfunk2(ansi__stream__background, stream, color,
	    "",
	    return f2__ansi__stream__background(this_cause, stream, color));

void raw__ansi__stream__rectangle(f2ptr cause, f2ptr stream, s64 x0, s64 y0, s64 x1, s64 y1, u8 ch) {
  if (y0 > y1) {u32 swap = y0; y0 = y1; y1 = swap;}
  if (x0 > x1) {u32 swap = x0; x0 = x1; x1 = swap;}
  s64 y;
  for (y = y0; y <= y1; y ++) {
    raw__ansi__stream__move_cursor(cause, stream, x0, y);
    s64 x;
    for (x = x0; x <= x1; x ++) {
      raw__stream__writef(cause, stream, "%c", ch);
    }
  }
}

f2ptr f2__ansi__stream__rectangle(f2ptr cause, f2ptr stream, f2ptr x0, f2ptr y0, f2ptr x1, f2ptr y1, f2ptr ch) {
  assert_argument_type(stream,  stream);
  assert_argument_type(integer, x0);
  assert_argument_type(integer, y0);
  assert_argument_type(integer, x1);
  assert_argument_type(integer, y1);
  assert_argument_type(char,    ch);
  s64 raw_x0 = f2integer__i(x0, cause);
  s64 raw_y0 = f2integer__i(y0, cause);
  s64 raw_x1 = f2integer__i(x1, cause);
  s64 raw_y1 = f2integer__i(y1, cause);
  u8  raw_ch = f2char__ch(ch, cause);
  raw__ansi__stream__rectangle(cause, stream, raw_x0, raw_y0, raw_x1, raw_y1, raw_ch);
  return nil;
}
def_pcfunk6(ansi__stream__rectangle, stream, x0, y0, x1, y1, ch,
	    "",
	    return f2__ansi__stream__rectangle(this_cause, stream, x0, y0, x1, y1, ch));


void raw__ansi__stream__bordered_rectangle(f2ptr cause, f2ptr stream, int x0, int y0, int x1, int y1, char background_char) {
  raw__ansi__stream__move_cursor(cause, stream, x0, y0); raw__stream__writef(cause, stream, "/");
  raw__ansi__stream__move_cursor(cause, stream, x1, y0); raw__stream__writef(cause, stream, "\\");
  raw__ansi__stream__move_cursor(cause, stream, x0, y1); raw__stream__writef(cause, stream, "\\");
  raw__ansi__stream__move_cursor(cause, stream, x1, y1); raw__stream__writef(cause, stream, "/");
  if ((x1 - x0) > 1) {
    raw__ansi__stream__rectangle(cause, stream, (x0 + 1), y0, (x1 - 1), y0, '-');
    raw__ansi__stream__rectangle(cause, stream, (x0 + 1), y1, (x1 - 1), y1, '-');
  }
  if ((y1 - y0) > 1) {
    raw__ansi__stream__rectangle(cause, stream, x0, (y0 + 1), x0, (y1 - 1), '|');
    raw__ansi__stream__rectangle(cause, stream, x1, (y0 + 1), x1, (y1 - 1), '|');
  }
  if (((x1 - x0) > 1) &&
      ((y1 - y0) > 1)) {
    raw__ansi__stream__rectangle(cause, stream, (x0 + 1), (y0 + 1), (x1 - 1), (y1 - 1), background_char);
  }
}

f2ptr f2__ansi__stream__bordered_rectangle(f2ptr cause, f2ptr stream, f2ptr x0, f2ptr y0, f2ptr x1, f2ptr y1, f2ptr background_char) {
  assert_argument_type(stream,  stream);
  assert_argument_type(integer, x0);
  assert_argument_type(integer, y0);
  assert_argument_type(integer, x1);
  assert_argument_type(integer, y1);
  assert_argument_type(char,    background_char);
  s64 raw_x0              = f2integer__i(x0, cause);
  s64 raw_y0              = f2integer__i(y0, cause);
  s64 raw_x1              = f2integer__i(x1, cause);
  s64 raw_y1              = f2integer__i(y1, cause);
  u8  raw_background_char = f2char__ch(background_char, cause);
  raw__ansi__stream__bordered_rectangle(cause, stream, raw_x0, raw_y0, raw_x1, raw_y1, raw_background_char);
  return nil;
}
def_pcfunk6(ansi__stream__bordered_rectangle, stream, x0, y0, x1, y1, background_char,
	    "",
	    return f2__ansi__stream__bordered_rectangle(this_cause, stream, x0, y0, x1, y1, background_char));

// **

void f2__ansi__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__write);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__print_code);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__reset);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__bold);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__half_bright);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__underscore);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__blink);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__reverse_video);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__normal_intensity);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__underline_off);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__blink_off);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__reverse_video_off);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__black_foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__red_foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__green_foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__brown_foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__blue_foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__magenta_foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__cyan_foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__white_foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__underscore_with_default_foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__underscore_off_with_default_foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__black_background);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__red_background);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__green_background);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__brown_background);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__blue_background);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__magenta_background);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__cyan_background);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__white_background);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__default_background);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__clear_screen);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__clear_keyboard_leds);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__set_scroll_lock_led);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__set_num_lock_led);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__set_caps_lock_led);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__move_cursor);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__beep);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__foreground);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__background);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__rectangle);
  f2__primcfunk__init__defragment__fix_pointers(ansi__stream__bordered_rectangle);
}

void f2__ansi__reinitialize_globalvars() {
  f2__primcfunk__init(ansi__stream__write);
  f2__primcfunk__init(ansi__stream__print_code);
  f2__primcfunk__init(ansi__stream__reset);
  f2__primcfunk__init(ansi__stream__bold);
  f2__primcfunk__init(ansi__stream__half_bright);
  f2__primcfunk__init(ansi__stream__underscore);
  f2__primcfunk__init(ansi__stream__blink);
  f2__primcfunk__init(ansi__stream__reverse_video);
  f2__primcfunk__init(ansi__stream__normal_intensity);
  f2__primcfunk__init(ansi__stream__underline_off);
  f2__primcfunk__init(ansi__stream__blink_off);
  f2__primcfunk__init(ansi__stream__reverse_video_off);
  f2__primcfunk__init(ansi__stream__black_foreground);
  f2__primcfunk__init(ansi__stream__red_foreground);
  f2__primcfunk__init(ansi__stream__green_foreground);
  f2__primcfunk__init(ansi__stream__brown_foreground);
  f2__primcfunk__init(ansi__stream__blue_foreground);
  f2__primcfunk__init(ansi__stream__magenta_foreground);
  f2__primcfunk__init(ansi__stream__cyan_foreground);
  f2__primcfunk__init(ansi__stream__white_foreground);
  f2__primcfunk__init(ansi__stream__underscore_with_default_foreground);
  f2__primcfunk__init(ansi__stream__underscore_off_with_default_foreground);
  f2__primcfunk__init(ansi__stream__black_background);
  f2__primcfunk__init(ansi__stream__red_background);
  f2__primcfunk__init(ansi__stream__green_background);
  f2__primcfunk__init(ansi__stream__brown_background);
  f2__primcfunk__init(ansi__stream__blue_background);
  f2__primcfunk__init(ansi__stream__magenta_background);
  f2__primcfunk__init(ansi__stream__cyan_background);
  f2__primcfunk__init(ansi__stream__white_background);
  f2__primcfunk__init(ansi__stream__default_background);
  f2__primcfunk__init(ansi__stream__clear_screen);
  f2__primcfunk__init(ansi__stream__clear_keyboard_leds);
  f2__primcfunk__init(ansi__stream__set_scroll_lock_led);
  f2__primcfunk__init(ansi__stream__set_num_lock_led);
  f2__primcfunk__init(ansi__stream__set_caps_lock_led);
  f2__primcfunk__init(ansi__stream__move_cursor);
  f2__primcfunk__init(ansi__stream__beep);
  f2__primcfunk__init(ansi__stream__foreground);
  f2__primcfunk__init(ansi__stream__background);
  f2__primcfunk__init(ansi__stream__rectangle);
  f2__primcfunk__init(ansi__stream__bordered_rectangle);
}

void f2__ansi__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "ansi", "", &f2__ansi__reinitialize_globalvars, &f2__ansi__defragment__fix_pointers);
  
  f2__ansi__reinitialize_globalvars();
}


