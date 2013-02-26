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
  u8*                            name;
  int                            width;
  int                            height;
  GLuint                         texture_id;
  struct funk2_opengl_texture_s* next;
} funk2_opengl_texture_t;

void funk2_opengl_texture__init(funk2_opengl_texture_t* this, u8* name, int width, int height, GLuint texture_id);
void funk2_opengl_texture__destroy(funk2_opengl_texture_t* this);

typedef struct funk2_opengl_texture_handler_s {
  funk2_processor_mutex_t mutex;
  funk2_opengl_texture_t* textures;
} funk2_opengl_texture_handler_t;

void                    funk2_opengl_texture_handler__init(funk2_opengl_texture_handler_t* this);
void                    funk2_opengl_texture_handler__destroy(funk2_opengl_texture_handler_t* this);
boolean_t               funk2_opengl_texture_handler__load_texture(funk2_opengl_texture_handler_t* this, f2ptr cause, u8* name, u8* filename);
funk2_opengl_texture_t* funk2_opengl_texture_handler__lookup_texture(funk2_opengl_texture_handler_t* this, f2ptr cause, f2ptr texture_name);
#endif // F2__GLWINDOW__SUPPORTED

#if defined(F2__GLWINDOW__SUPPORTED)
typedef struct funk2_opengl_font_s {
  GLuint base_display_list;
} funk2_opengl_font_t;
#endif // F2__GLWINDOW__SUPPORTED

// stuff about our window grouped together
typedef struct funk2_glwindow_s {
  funk2_processor_mutex_t        mutex;
  boolean_t                      initialized;
  boolean_t                      window_created;
  u8*                            title;
  int                            x;
  int                            y;
  unsigned int                   width;
  unsigned int                   height;
  unsigned int                   depth;
  boolean_t                      done;
  float                          rotate_angle;
  boolean_t                      fullscreen;
  boolean_t                      needs_redraw;
  u64                            last_redraw__nanoseconds_since_1970;
  
#if defined(F2__GLWINDOW__SUPPORTED)
  Display*                       display;
  int                            screen;
  Window                         x_window;
  GLXContext                     glx_context;
  XSetWindowAttributes           set_window_attributes;
  XF86VidModeModeInfo            desk_mode;
  boolean_t                      double_buffered;
  unsigned int                   resolution;
  funk2_opengl_texture_handler_t texture_handler;
  funk2_opengl_font_t            fixed_font;
#endif // defined(F2__GLWINDOW__SUPPORTED)
  
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

void funk2_glwindow__render_relative_physical_thing(funk2_glwindow_t* this, f2ptr cause, f2ptr relative_object, f2ptr physical_thing);


#if defined(F2__GLWINDOW__SUPPORTED)

boolean_t funk2_opengl_font__init(funk2_opengl_font_t* this, f2ptr cause, Display* display, char* font_name);
void funk2_opengl_font__destroy(funk2_opengl_font_t* this, f2ptr cause);
void funk2_opengl_font__printf(funk2_opengl_font_t* this, f2ptr cause, const char* fmt, ...);
boolean_t funk2_texture_image__load_bmp(funk2_texture_image_t* texture, u8* filename);
boolean_t funk2_opengl_texture__load_gl_texture_from_bmp(funk2_opengl_texture_t* this, f2ptr cause, u8* bmp_filename);
void funk2_opengl_texture__bind(funk2_opengl_texture_t* this, f2ptr cause);
void raw__resize_gl_scene(f2ptr cause, unsigned int width, unsigned int height);
void funk2_glwindow__init(funk2_glwindow_t* this, u8* title, int width, int height, int depth, boolean_t fullscreen);
void funk2_glwindow__reinit(funk2_glwindow_t* this, u8* title, int width, int height, int depth, boolean_t fullscreen);
void funk2_glwindow__destroy(funk2_glwindow_t* this);
void funk2_glwindow__hide(funk2_glwindow_t* this, f2ptr cause);
boolean_t funk2_glwindow__show(funk2_glwindow_t* this, f2ptr cause);
boolean_t funk2_glwindow__handle_events(funk2_glwindow_t* this, f2ptr cause);
boolean_t funk2_glwindow__initialize_opengl(funk2_glwindow_t* this, f2ptr cause);
void funk2_glwindow__bind_texture(funk2_glwindow_t* this, f2ptr cause, f2ptr texture_name);
void raw__draw_gl_cube(f2ptr cause);
void raw__draw_xy_square(f2ptr cause);
void raw__gl_set_material_color(f2ptr cause, float red, float green, float blue, float alpha);
void opengl__render_physical_position(f2ptr cause, f2ptr this);
void opengl__render_physical_rotation(f2ptr cause, f2ptr this);
void opengl__render_physical_position_as_raster(f2ptr cause, f2ptr this);
GLfloat funk2_glwindow__get_render_font_width(funk2_glwindow_t* this, f2ptr cause, f2ptr text);
void funk2_glwindow__render_outlined_font(funk2_glwindow_t* this, f2ptr cause, f2ptr text, double x, double y);
void funk2_glwindow__render_relative_physical_object(funk2_glwindow_t* this, f2ptr cause, f2ptr relative_object, f2ptr physical_object);
void opengl__render_physical_transform(f2ptr cause, f2ptr this);
void funk2_glwindow__render_relative_physical_place(funk2_glwindow_t* this, f2ptr cause, f2ptr relative_object, f2ptr physical_place);
void funk2_glwindow__render_relative_physical_person(funk2_glwindow_t* this, f2ptr cause, f2ptr relative_object, f2ptr physical_person);
void funk2_glwindow__render_physical_place(funk2_glwindow_t* this, f2ptr cause, f2ptr physical_place);
void funk2_glwindow__render_physical_object(funk2_glwindow_t* this, f2ptr cause, f2ptr physical_object);
void funk2_glwindow__render_relative_physical_thing(funk2_glwindow_t* this, f2ptr cause, f2ptr relative_object, f2ptr physical_thing);
void funk2_glwindow__render_physical_thing(funk2_glwindow_t* this, f2ptr cause, f2ptr physical_thing);
void funk2_glwindow__render_background(funk2_glwindow_t* this, f2ptr cause, f2ptr background_texture_name);
void funk2_glwindow__render_physical_scene(funk2_glwindow_t* this, f2ptr cause, f2ptr physical_scene);
void funk2_glwindow__draw_scene(funk2_glwindow_t* this, f2ptr cause);
void funk2_glwindow__main(f2ptr cause);

#endif // F2__GLWINDOW__SUPPORTED

boolean_t raw__glwindow__supported(f2ptr cause);
f2ptr f2__glwindow__supported(f2ptr cause);
void raw__glwindow__create(f2ptr cause, u8* title, s64 width, s64 height, s64 depth, boolean_t fullscreen);
f2ptr f2__glwindow__create(f2ptr cause, f2ptr title, f2ptr width, f2ptr height, f2ptr depth, f2ptr fullscreen);
boolean_t raw__glwindow__handle_events(f2ptr cause);
f2ptr f2__glwindow__handle_events(f2ptr cause);
void raw__glwindow__destroy(f2ptr cause);
f2ptr f2__glwindow__destroy(f2ptr cause);


// **

void f2__glwindow__reinitialize_globalvars();
void f2__glwindow__initialize();

#endif // F2__GLWINDOW__H

