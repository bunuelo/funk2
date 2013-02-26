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

#include "f2_html.h"
#include <string.h>

void html__stream__protected_string(f2ptr cause, f2ptr stream, char* str) {
  raw__stream__writef(cause, stream, "\"");
  char* iter;
  for (iter = str; *iter; iter++) {
    if (*iter == '"') {
      raw__stream__writef(cause, stream, "\\\"");
    } else {
      raw__stream__writef(cause, stream, "%c", *iter);
    }
  }
  raw__stream__writef(cause, stream, "\"");
}

void html__stream__font(f2ptr cause, f2ptr stream, char* face, char* size, char* color) {
  raw__stream__writef(cause, stream, "<font");
  if (face)  {raw__stream__writef(cause, stream, " face=");  html__stream__protected_string(cause, stream, face);}
  if (size)  {raw__stream__writef(cause, stream, " size=");             raw__stream__writef(cause, stream, size);}
  if (color) {raw__stream__writef(cause, stream, " color=");            raw__stream__writef(cause, stream, color);}
  raw__stream__writef(cause, stream, ">");
}

void html__stream__end_font(f2ptr cause, f2ptr stream) {
  raw__stream__writef(cause, stream, "</font>");
}

void html__stream__font_face( f2ptr cause, f2ptr stream, char* face)  {html__stream__font(cause, stream, face, NULL, NULL);}
void html__stream__font_size( f2ptr cause, f2ptr stream, char* size)  {html__stream__font(cause, stream, NULL, size, NULL);}
void html__stream__font_color(f2ptr cause, f2ptr stream, char* color) {html__stream__font(cause, stream, NULL, NULL, color);}

void html__stream__ansi_foreground(f2ptr cause, f2ptr stream, ansi_color_t color) {
  html__stream__end_font(cause, stream);
  switch(color) {
  case ansi_color__black:       html__stream__font_color(cause, stream, "#000000"); break;
  case ansi_color__dark_blue:   html__stream__font_color(cause, stream, "#00007f"); break;
  case ansi_color__dark_green:  html__stream__font_color(cause, stream, "#007f00"); break;
  case ansi_color__dark_cyan:   html__stream__font_color(cause, stream, "#007f7f"); break;
  case ansi_color__dark_red:    html__stream__font_color(cause, stream, "#7f0000"); break;
  case ansi_color__dark_purple: html__stream__font_color(cause, stream, "#7f007f"); break;
  case ansi_color__brown:       html__stream__font_color(cause, stream, "#7f7f00"); break;
  case ansi_color__light_gray:  html__stream__font_color(cause, stream, "#cfcfcf"); break;
  case ansi_color__dark_gray:   html__stream__font_color(cause, stream, "#7f7f7f"); break;
  case ansi_color__light_blue:  html__stream__font_color(cause, stream, "#7f7fff"); break;
  case ansi_color__light_green: html__stream__font_color(cause, stream, "#7fff7f"); break;
  case ansi_color__light_cyan:  html__stream__font_color(cause, stream, "#7fffff"); break;
  case ansi_color__light_red:   html__stream__font_color(cause, stream, "#ff7f7f"); break;
  case ansi_color__light_purple:html__stream__font_color(cause, stream, "#ff7fff"); break;
  case ansi_color__yellow:      html__stream__font_color(cause, stream, "#ffff7f"); break;
  case ansi_color__white:       html__stream__font_color(cause, stream, "#ffffff"); break;
  }
}
