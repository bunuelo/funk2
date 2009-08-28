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

#ifndef F2__GLWINDOW__H
#include "f2_system_headers.h"
#if defined(F2__GL__H) && defined(F2__GLX__H) && defined(F2__GLU__H) && defined(F2__XF86VMODE__H) && defined(F2__XLIB__H) && defined(F2__KEYSYM__H)
#define F2__GLWINDOW__H

// stuff about our window grouped together
typedef struct funk2_glwindow_s {
  Display*             display;
  int                  screen;
  Window               x_window;
  GLXContext           glx_context;
  XSetWindowAttributes set_window_attributes;
  XF86VidModeModeInfo  desk_mode;
  boolean_t            fullscreen;
  boolean_t            double_buffered;
  int                  x;
  int                  y;
  unsigned int         width;
  unsigned int         height;
  unsigned int         depth;
  boolean_t            done;
} funk2_glwindow_t;

#endif
#endif // F2__GLWINDOW__H

