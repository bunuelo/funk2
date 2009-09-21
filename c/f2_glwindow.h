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

typedef struct funk2_texture_image_s {
  int            width;
  int            height;
  unsigned char* data;
} funk2_texture_image_t;

#if defined(F2__GLWINDOW__SUPPORTED)
typedef struct funk2_opengl_texture_s {
  int    width;
  int    height;
  GLuint texture_id;
} funk2_opengl_texture_t;
#endif // F2__GLWINDOW__SUPPORTED

#if defined(F2__GLWINDOW__SUPPORTED)
typedef struct funk2_opengl_font_s {
  GLuint base_display_list;
} funk2_opengl_font_t;
#endif // F2__GLWINDOW__SUPPORTED

// stuff about our window grouped together
typedef struct funk2_glwindow_s {
  boolean_t              initialized;
  boolean_t              window_created;
  
#if defined(F2__GLWINDOW__SUPPORTED)
  Display*               display;
  int                    screen;
  Window                 x_window;
  GLXContext             glx_context;
  XSetWindowAttributes   set_window_attributes;
  XF86VidModeModeInfo    desk_mode;
  boolean_t              fullscreen;
  boolean_t              double_buffered;
  u8*                    title;
  int                    x;
  int                    y;
  unsigned int           width;
  unsigned int           height;
  unsigned int           resolution;
  unsigned int           depth;
  boolean_t              done;
  float                  rotate_angle;
  u64                    last_redraw__nanoseconds_since_1970;
  boolean_t              needs_redraw;
  funk2_opengl_texture_t texture;
  funk2_opengl_texture_t bucket_object_texture;
  funk2_opengl_texture_t female_child_agent_sitting_texture;
  funk2_opengl_texture_t female_child_agent_standing_texture;
  funk2_opengl_texture_t fork_object_texture;
  funk2_opengl_texture_t male_child_agent_sitting_texture;
  funk2_opengl_texture_t male_child_agent_standing_texture;
  funk2_opengl_texture_t mud_object_texture;
  funk2_opengl_texture_t mud_puddle_scene_texture;
  funk2_opengl_texture_t shovel_object_texture;
  funk2_opengl_texture_t spoon_object_texture;
  
  funk2_opengl_texture_t blue_left_shoe_texture;
  funk2_opengl_texture_t blue_right_shoe_texture;
  funk2_opengl_texture_t blue_shirt_texture;
  funk2_opengl_texture_t bluegreen_blouse_texture;
  funk2_opengl_texture_t orange_shorts_texture;
  funk2_opengl_texture_t pink_left_shoe_texture;
  funk2_opengl_texture_t pink_right_shoe_texture;
  funk2_opengl_texture_t red_skirt_texture;
  funk2_opengl_texture_t sideview_blue_shirt_texture;
  funk2_opengl_texture_t sideview_bluegreen_blouse_texture;
  funk2_opengl_texture_t sideview_orange_shorts_texture;
  funk2_opengl_texture_t sideview_red_skirt_texture;
  
  funk2_opengl_font_t    fixed_font;
#endif // F2__GLWINDOW__SUPPORTED

} funk2_glwindow_t;

void raw__resize_gl_scene(f2ptr cause, unsigned int width, unsigned int height);

void      funk2_glwindow__init(funk2_glwindow_t* this, u8* title, int width, int height, int depth, boolean_t fullscreen);
void      funk2_glwindow__reinit(funk2_glwindow_t* this, u8* title, int width, int height, int depth, boolean_t fullscreen);
void      funk2_glwindow__destroy(funk2_glwindow_t* this);

#if defined(F2__GLWINDOW__SUPPORTED)
void      funk2_glwindow__hide(funk2_glwindow_t* this, f2ptr cause);
boolean_t funk2_glwindow__show(funk2_glwindow_t* this, f2ptr cause);
boolean_t funk2_glwindow__handle_events(funk2_glwindow_t* this, f2ptr cause);
boolean_t funk2_glwindow__initialize_opengl(funk2_glwindow_t* this, f2ptr cause);
void      funk2_glwindow__draw_scene(funk2_glwindow_t* this, f2ptr cause);
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

