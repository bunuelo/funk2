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

#ifndef F2__OPENGL__H
#define F2__OPENGL__H

typedef struct funk2_opengl_s  funk2_opengl_t;
typedef struct funk2_openglu_s funk2_openglu_t;
typedef struct funk2_xxf86vm_s funk2_xxf86vm_t;
typedef struct funk2_xlib_s    funk2_xlib_t;

#include "f2_primfunks.h"

struct funk2_opengl_s {
  boolean_t initialized;
  f2ptr     dlfcn_pointer;
#if defined(F2__GL__H)
  void(*    glViewport    )(GLint x, GLint y, GLsizei width, GLsizei height);
  void(*    glMatrixMode  )(GLenum mode);
  void(*    glLoadIdentity)();
  void(*    glShadeModel  )(GLenum mode);
  void(*    glClearColor  )(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
  void(*    glClearDepth  )(GLclampd depth);
  void(*    glEnable      )(GLenum cap);
  void(*    glDepthFunc   )(GLenum func);
  void(*    glHint        )(GLenum target, GLenum mode);
  void(*    glFlush       )();
  void(*    glClear       )(GLbitfield mask);
#endif // F2__GL__H
};

struct funk2_openglx_s {
  boolean_t initialized;
  f2ptr     dlfcn_pointer;
#if defined(F2__GLX__H)
  void(*         glXSwapBuffers   )(Display* dpy, GLXDrawable drawable);
  Bool(*         glXMakeCurrent   )(Display* dpy, GLXDrawable drawable, GLXContext ctx);
  void(*         glXDestroyContext)(Display* dpy, GLXContext ctx);
  XVisualInfo*(* glXChooseVisual  )(Display* dpy, int screen, int* attribList);
  Bool(*         glXQueryVersion  )(Display* dpy, int* Major, int* Minor);
  GLXContext(*   glXCreateContext )(Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct);
  Bool(*         glXIsDirect      )(Display* dpy, GLXContext ctx);
#endif // F2__GLX__H
};

struct funk2_openglu_s {
  boolean_t initialized;
  f2ptr     dlfcn_pointer;
#if defined(F2__GLU__H)
  void(*    gluPerspective)(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
#endif // F2__GLU__H
};

struct funk2_xxf86vm_s {
  boolean_t      initialized;
  f2ptr          dlfcn_pointer;
#if defined(F2__XF86VMODE__H)
  Bool(* XF86VidModeSwitchToMode   )(Display* display, int screen, XF86VidModeModeInfo* modeline);
  Bool(* XF86VidModeSetViewPort    )(Display* display, int screen, int x, int y);
  Bool(* XF86VidModeQueryVersion   )(Display* display, int* major_version_return, int* minor_version_return);
  Bool(* XF86VidModeGetAllModeLines)(Display* display, int screen, int* modecount_return, XF86VidModeModeInfo*** modesinfo);
#endif // F2__XF86VMODE__H
};

struct funk2_xlib_s {
  boolean_t  initialized;
  f2ptr      dlfcn_pointer;
#if defined(F2__XLIB__H)
  void(*     XCloseDisplay         )(Display* display);
  Display*(* XOpenDisplay          )(char* display_name);
  Colormap(* XCreateColormap       )(Display* display, Window w, Visual* visual, int alloc);
  int(*      XFree                 )(void* data);   
  Window(*   XCreateWindow         )(Display* display, Window parent, int x, int y, unsigned int width, unsigned int height, unsigned int border_width, int depth, unsigned int class, Visual* visual, unsigned long valuemask, XSetWindowAttributes* attributes);
  void(*     XWarpPointer          )(Display* display, Window src_w, Window dest_w, int src_x, int src_y, unsigned int src_width, unsigned int src_height, int dest_x, int dest_y);
  void(*     XMapRaised            )(Display* display, Window w);
  int(*      XGrabKeyboard         )(Display* display, Window grab_window, Bool owner_events, int pointer_mode, int keyboard_mode, Time time);
  int(*      XGrabPointer          )(Display* display, Window grab_window, Bool owner_events, unsigned int event_mask, int pointer_mode, int keyboard_mode, Window confine_to, Cursor cursor, Time time);
  Atom(*     XInternAtom           )(Display* display, char* atom_name, Bool only_if_exists);
  Status(*   XSetWMProtocols       )(Display* display, Window w, Atom* protocols, int count);
  void(*     XSetStandardProperties)(Display* display, Window w, char* window_name, char* icon_name, Pixmap icon_pixmap, char** argv, int argc, XSizeHints *hints);
  Status(*   XGetGeometry          )(Display* display, Drawable d, Window *root_return, int* x_return, int* y_return, unsigned int* width_return, unsigned int* height_return, unsigned int* border_width_return, unsigned int* depth_return);
  void(*     XNextEvent            )(Display* display, XEvent* event_return);
  KeySym(*   XLookupKeysym         )(XKeyEvent* key_event, int index);
  char*(*    XGetAtomName          )(Display* display, Atom atom);
  int(*      XPending              )(Display *display);
#endif // F2__XLIB__H
};

void      funk2_opengl__init(funk2_opengl_t* this);
void      funk2_opengl__destroy(funk2_opengl_t* this);
boolean_t  raw__opengl__load_library(f2ptr cause);

#if defined(F2__GL__H)
void raw__opengl__glViewport(f2ptr cause, GLint x, GLint y, GLsizei width, GLsizei height);
void raw__opengl__glMatrixMode(f2ptr cause, GLenum mode);
void raw__opengl__glLoadIdentity(f2ptr cause);
void raw__opengl__glShadeModel(f2ptr cause, GLenum mode);
void raw__opengl__glClearColor(f2ptr cause, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
void raw__opengl__glClearDepth(f2ptr cause, GLclampd depth);
void raw__opengl__glEnable(f2ptr cause, GLenum cap);
void raw__opengl__glDepthFunc(f2ptr cause, GLenum func);
void raw__opengl__glHint(f2ptr cause, GLenum target, GLenum mode);
void raw__opengl__glFlush(f2ptr cause);
void raw__opengl__glClear(f2ptr cause, GLbitfield mask);
#endif // F2__GL__H


void      funk2_openglu__init(funk2_openglu_t* this);
void      funk2_openglu__destroy(funk2_openglu_t* this);
boolean_t  raw__openglu__load_library(f2ptr cause);

#if defined(F2__GLU__H)
void raw__openglu__gluPerspective(f2ptr cause, GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
#endif // F2__GLU__H


void      funk2_xxf86vm__init(funk2_xxf86vm_t* this);
void      funk2_xxf86vm__destroy(funk2_xxf86vm_t* this);
boolean_t  raw__xxf86vm__load_library(f2ptr cause);

#if defined(F2__XF86VMODE__H)
Bool raw__xxf86vm__XF86VidModeSwitchToMode(f2ptr cause, Display* display, int screen, XF86VidModeModeInfo* modeline);
Bool raw__xxf86vm__XF86VidModeSetViewPort(f2ptr cause, Display* display, int screen, int x, int y);
Bool raw__xxf86vm__XF86VidModeQueryVersion(f2ptr cause, Display* display, int* major_version_return, int* minor_version_return);
Bool raw__xxf86vm__XF86VidModeGetAllModeLines(f2ptr cause, Display* display, int screen, int* modecount_return, XF86VidModeModeInfo*** modesinfo);
#endif // F2__XF86VMODE__H


void      funk2_xlib__init(funk2_xlib_t* this);
void      funk2_xlib__destroy(funk2_xlib_t* this);
boolean_t  raw__xlib__load_library(f2ptr cause);

#if defined(F2__XLIB__H)
void     raw__xlib__XCloseDisplay(f2ptr cause, Display* display);
Display* raw__xlib__XOpenDisplay(f2ptr cause, char* display_name);
Colormap raw__xlib__XCreateColormap(f2ptr cause, Display* display, Window w, Visual* visual, int alloc);
#endif // F2__XLIB__H


#endif // F2__OPENGL__H


