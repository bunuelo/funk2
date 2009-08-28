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
#define F2__GLWINDOW__H
#include "f2_system_headers.h"

#if defined(F2__GL__H) && defined(F2__GLX__H) && defined(F2__GLU__H) && defined(F2__XF86VMODE__H) && defined(F2__XLIB__H) && defined(F2__KEYSYM__H)
#  define F2__GLWINDOW__SUPPORTED
#endif

int int__abs(int x);

// stuff about our window grouped together
typedef struct funk2_glwindow_s {
  boolean_t            window_created;

#if defined(F2__GLWINDOW__SUPPORTED)
  Display*             display;
  int                  screen;
  Window               x_window;
  GLXContext           glx_context;
  XSetWindowAttributes set_window_attributes;
  XF86VidModeModeInfo  desk_mode;
  boolean_t            fullscreen;
  boolean_t            double_buffered;
  char*                title;
  int                  x;
  int                  y;
  unsigned int         width;
  unsigned int         height;
  unsigned int         depth;
  boolean_t            done;
  float                rotate_angle;
#endif // F2__GLWINDOW__SUPPORTED

} funk2_glwindow_t;

void raw__resize_gl_scene(f2ptr cause, unsigned int width, unsigned int height);

void      funk2_glwindow__init(funk2_glwindow_t* this);
void      funk2_glwindow__destroy(funk2_glwindow_t* this);

#if defined(F2__GLWINDOW__SUPPORTED)
boolean_t funk2_glwindow__create(funk2_glwindow_t* this, f2ptr cause, u8* title, int width, int height, int bits, boolean_t fullscreenflag);
boolean_t funk2_glwindow__handle_events(funk2_glwindow_t* this, f2ptr cause);
int       funk2_glwindow__initialize_opengl(funk2_glwindow_t* this, f2ptr cause);
int       funk2_glwindow__draw_scene(funk2_glwindow_t* this, f2ptr cause);
void      funk2_glwindow__main(f2ptr cause);
#endif // F2__GLWINDOW__SUPPORTED

boolean_t raw__glwindow__supported(f2ptr cause);
f2ptr      f2__glwindow__supported(f2ptr cause);
void      raw__glwindow__create(f2ptr cause, u8* title, s64 width, s64 height, s64 depth, boolean_t fullscreen);
f2ptr      f2__glwindow__create(f2ptr cause, f2ptr title, f2ptr width, f2ptr height, f2ptr depth, f2ptr fullscreen);
boolean_t raw__glwindow__handle_events(f2ptr cause);
f2ptr      f2__glwindow__handle_events(f2ptr cause);
void      raw__glwindow__destroy(f2ptr cause);
f2ptr      f2__glwindow__destroy(f2ptr cause);

// **

void f2__glwindow__reinitialize_globalvars();
void f2__glwindow__initialize();

#endif // F2__GLWINDOW__H

