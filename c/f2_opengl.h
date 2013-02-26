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
  void(*         glViewport      )(GLint x, GLint y, GLsizei width, GLsizei height);
  void(*         glMatrixMode    )(GLenum mode);
  void(*         glLoadIdentity  )();
  void(*         glShadeModel    )(GLenum mode);
  void(*         glClearColor    )(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
  void(*         glClearDepth    )(GLclampd depth);
  void(*         glEnable        )(GLenum cap);
  void(*         glDepthFunc     )(GLenum func);
  void(*         glHint          )(GLenum target, GLenum mode);
  void(*         glFlush         )();
  void(*         glClear         )(GLbitfield mask);
  void(*         glLightfv       )(GLenum light, GLenum pname, const GLfloat* params);
  void(*         glCullFace      )(GLenum mode);
  void(*         glTranslatef    )(GLfloat x, GLfloat y, GLfloat z);
  void(*         glRotatef       )(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
  void(*         glColor4f       )(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
  void(*         glBegin         )(GLenum mode);
  void(*         glNormal3f      )(GLfloat nx, GLfloat ny, GLfloat nz);
  void(*         glVertex3f      )(GLfloat x, GLfloat y, GLfloat z);
  void(*         glEnd           )();
  void(*         glMaterialfv    )(GLenum face, GLenum pname, const GLfloat* params);
  void(*         glPushMatrix    )();
  void(*         glPopMatrix     )();
  void(*         glGenTextures   )(GLsizei n, GLuint* textures);
  void(*         glDeleteTextures)(GLsizei n, GLuint* textures);
  void(*         glBindTexture   )(GLenum target, GLuint texture);
  void(*         glTexImage2D    )(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);
  void(*         glTexParameteri )(GLenum target, GLenum pname, GLint param);
  void(*         glTexCoord2f    )(GLfloat s, GLfloat t);
  void(*         glBlendFunc     )(GLenum sfactor, GLenum dfactor);
  void(*         glScalef        )(GLfloat x, GLfloat y, GLfloat z);
  void(*         glDisable       )(GLenum cap);
  GLuint(*       glGenLists      )(GLsizei range);
  void(*         glDeleteLists   )(GLuint list, GLsizei range);
  void(*         glPushAttrib    )(GLbitfield mask);
  void(*         glListBase      )(GLuint base);
  void(*         glCallLists     )(GLsizei n, GLenum type, const GLvoid* lists);
  void(*         glPopAttrib     )();
  void(*         glRasterPos3f   )(GLfloat x, GLfloat y, GLfloat z);
  void(*         glMultMatrixf   )(const GLfloat* m);
  void(*         glLoadMatrixf   )(const GLfloat* m);
  void(*         glGetFloatv      )(GLenum pname, GLfloat *params);
  // The following functions are included in libGL.so, but are
  // probably not on non-X environments, so we'll need to deal with
  // this in a port to those environments.
#endif // F2__GL__H
#if defined(F2__GLX__H)
  void(*         glXSwapBuffers   )(Display* dpy, GLXDrawable drawable);
  Bool(*         glXMakeCurrent   )(Display* dpy, GLXDrawable drawable, GLXContext ctx);
  void(*         glXDestroyContext)(Display* dpy, GLXContext ctx);
  XVisualInfo*(* glXChooseVisual  )(Display* dpy, int screen, int* attribList);
  Bool(*         glXQueryVersion  )(Display* dpy, int* Major, int* Minor);
  GLXContext(*   glXCreateContext )(Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct);
  Bool(*         glXIsDirect      )(Display* dpy, GLXContext ctx);
  void(*         glXUseXFont      )(Font font, int First, int Count, int ListBase);
#endif // F2__GLX__H
};

struct funk2_openglu_s {
  boolean_t initialized;
  f2ptr     dlfcn_pointer;
#if defined(F2__GLU__H)
  void(*    gluPerspective   )(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
  GLint(*   gluBuild2DMipmaps)(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data);
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
  boolean_t      initialized;
  f2ptr          dlfcn_pointer;
#if defined(F2__XLIB__H)
  void(*         XCloseDisplay         )(Display* display);
  Display*(*     XOpenDisplay          )(char* display_name);
  Colormap(*     XCreateColormap       )(Display* display, Window w, Visual* visual, int alloc);
  int(*          XFree                 )(void* data);   
  Window(*       XCreateWindow         )(Display* display, Window parent, int x, int y, unsigned int width, unsigned int height, unsigned int border_width, int depth, unsigned int class, Visual* visual, unsigned long valuemask, XSetWindowAttributes* attributes);
  void(*         XWarpPointer          )(Display* display, Window src_w, Window dest_w, int src_x, int src_y, unsigned int src_width, unsigned int src_height, int dest_x, int dest_y);
  void(*         XMapRaised            )(Display* display, Window w);
  int(*          XGrabKeyboard         )(Display* display, Window grab_window, Bool owner_events, int pointer_mode, int keyboard_mode, Time time);
  int(*          XGrabPointer          )(Display* display, Window grab_window, Bool owner_events, unsigned int event_mask, int pointer_mode, int keyboard_mode, Window confine_to, Cursor cursor, Time time);
  Atom(*         XInternAtom           )(Display* display, char* atom_name, Bool only_if_exists);
  Status(*       XSetWMProtocols       )(Display* display, Window w, Atom* protocols, int count);
  void(*         XSetStandardProperties)(Display* display, Window w, char* window_name, char* icon_name, Pixmap icon_pixmap, char** argv, int argc, XSizeHints *hints);
  Status(*       XGetGeometry          )(Display* display, Drawable d, Window *root_return, int* x_return, int* y_return, unsigned int* width_return, unsigned int* height_return, unsigned int* border_width_return, unsigned int* depth_return);
  void(*         XNextEvent            )(Display* display, XEvent* event_return);
  KeySym(*       XLookupKeysym         )(XKeyEvent* key_event, int index);
  char*(*        XGetAtomName          )(Display* display, Atom atom);
  int(*          XPending              )(Display *display);
  int(*          XDefaultScreen        )(Display *display);
  XFontStruct*(* XLoadQueryFont        )(Display *display, char *name);
  int(*          XFreeFont             )(Display *display, XFontStruct *font_struct); 
#endif // F2__XLIB__H
};

void      funk2_opengl__init(funk2_opengl_t* this);
void      funk2_opengl__destroy(funk2_opengl_t* this);
boolean_t  raw__opengl__load_library(f2ptr cause);

#if defined(F2__GL__H)
void   raw__opengl__glViewport(f2ptr cause, GLint x, GLint y, GLsizei width, GLsizei height);
void   raw__opengl__glMatrixMode(f2ptr cause, GLenum mode);
void   raw__opengl__glLoadIdentity(f2ptr cause);
void   raw__opengl__glShadeModel(f2ptr cause, GLenum mode);
void   raw__opengl__glClearColor(f2ptr cause, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
void   raw__opengl__glClearDepth(f2ptr cause, GLclampd depth);
void   raw__opengl__glEnable(f2ptr cause, GLenum cap);
void   raw__opengl__glDepthFunc(f2ptr cause, GLenum func);
void   raw__opengl__glHint(f2ptr cause, GLenum target, GLenum mode);
void   raw__opengl__glFlush(f2ptr cause);
void   raw__opengl__glClear(f2ptr cause, GLbitfield mask);
void   raw__opengl__glLightfv(f2ptr cause, GLenum light, GLenum pname, const GLfloat* params);
void   raw__opengl__glCullFace(f2ptr cause, GLenum mode);
void   raw__opengl__glTranslatef(f2ptr cause, GLfloat x, GLfloat y, GLfloat z);
void   raw__opengl__glRotatef(f2ptr cause, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void   raw__opengl__glColor4f(f2ptr cause, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void   raw__opengl__glBegin(f2ptr cause, GLenum mode);
void   raw__opengl__glNormal3f(f2ptr cause, GLfloat nx, GLfloat ny, GLfloat nz);
void   raw__opengl__glVertex3f(f2ptr cause, GLfloat x, GLfloat y, GLfloat z);
void   raw__opengl__glEnd(f2ptr cause);
void   raw__opengl__glMaterialfv(f2ptr cause, GLenum face, GLenum pname, const GLfloat* params);
void   raw__opengl__glPushMatrix(f2ptr cause);
void   raw__opengl__glPopMatrix(f2ptr cause);
void   raw__opengl__glGenTextures(f2ptr cause, GLsizei n, GLuint* textures);
void   raw__opengl__glDeleteTextures(f2ptr cause, GLsizei n, GLuint* textures);
void   raw__opengl__glBindTexture(f2ptr cause, GLenum target, GLuint texture);
void   raw__opengl__glTexImage2D(f2ptr cause, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);
void   raw__opengl__glTexParameteri(f2ptr cause, GLenum target, GLenum pname, GLint param);
void   raw__opengl__glTexCoord2f(f2ptr cause, GLfloat s, GLfloat t);
void   raw__opengl__glBlendFunc(f2ptr cause, GLenum sfactor, GLenum dfactor);
void   raw__opengl__glScalef(f2ptr cause, GLfloat x, GLfloat y, GLfloat z);
void   raw__opengl__glDisable(f2ptr cause, GLenum cap);
GLuint raw__opengl__glGenLists(f2ptr cause, GLsizei range);
void   raw__opengl__glDeleteLists(f2ptr cause, GLuint list, GLsizei range);
void   raw__opengl__glPushAttrib(f2ptr cause, GLbitfield mask);
void   raw__opengl__glListBase(f2ptr cause, GLuint base);
void   raw__opengl__glCallLists(f2ptr cause, GLsizei n, GLenum type, const GLvoid* lists);
void   raw__opengl__glPopAttrib(f2ptr cause);
void   raw__opengl__glRasterPos3f(f2ptr cause, GLfloat x, GLfloat y, GLfloat z);
void   raw__opengl__glGetFloatv(f2ptr cause, GLenum pname, GLfloat *params);
void   raw__opengl__glMultMatrixf(f2ptr cause, const GLfloat* m);
void   raw__opengl__glLoadMatrixf(f2ptr cause, const GLfloat* m);
#endif // F2__GL__H

#if defined(F2__GLX__H)
void         raw__opengl__glXSwapBuffers(f2ptr cause, Display* dpy, GLXDrawable drawable);
Bool         raw__opengl__glXMakeCurrent(f2ptr cause, Display* dpy, GLXDrawable drawable, GLXContext ctx);
void         raw__opengl__glXDestroyContext(f2ptr cause, Display* dpy, GLXContext ctx);
XVisualInfo* raw__opengl__glXChooseVisual(f2ptr cause, Display* dpy, int screen, int* attribList);
Bool         raw__opengl__glXQueryVersion(f2ptr cause, Display* dpy, int* Major, int* Minor);
GLXContext   raw__opengl__glXCreateContext(f2ptr cause, Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct);
Bool         raw__opengl__glXIsDirect(f2ptr cause, Display* dpy, GLXContext ctx);
void         raw__opengl__glXUseXFont(f2ptr cause, Font font, int First, int Count, int ListBase);
#endif // F2__GLX__H


void      funk2_openglu__init(funk2_openglu_t* this);
void      funk2_openglu__destroy(funk2_openglu_t* this);
boolean_t  raw__openglu__load_library(f2ptr cause);

#if defined(F2__GLU__H)
void  raw__openglu__gluPerspective(f2ptr cause, GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
GLint raw__openglu__gluBuild2DMipmaps(f2ptr cause, GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data);
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
void         raw__xlib__XCloseDisplay(f2ptr cause, Display* display);
Display*     raw__xlib__XOpenDisplay(f2ptr cause, char* display_name);
Colormap     raw__xlib__XCreateColormap(f2ptr cause, Display* display, Window w, Visual* visual, int alloc);
int          raw__xlib__XFree(f2ptr cause, void* data);
Window       raw__xlib__XCreateWindow(f2ptr cause, Display* display,
				      Window parent,
				      int x, int y,
				      unsigned int width, unsigned int height,
				      unsigned int border_width,
				      int depth,
				      unsigned int class,
				      Visual* visual,
				      unsigned long valuemask,
				      XSetWindowAttributes* attributes);
void         raw__xlib__XWarpPointer(f2ptr cause, Display* display,
				     Window src_w, Window dest_w,
				     int src_x, int src_y,
				     unsigned int src_width, unsigned int src_height,
				     int dest_x, int dest_y);
void         raw__xlib__XMapRaised(f2ptr cause, Display* display, Window w);
int          raw__xlib__XGrabKeyboard(f2ptr cause, Display* display,
				      Window grab_window,
				      Bool owner_events,
				      int pointer_mode,
				      int keyboard_mode,
				      Time time);
int          raw__xlib__XGrabPointer(f2ptr cause, Display* display,
				     Window grab_window,
				     Bool owner_events,
				     unsigned int event_mask,
				     int pointer_mode,
				     int keyboard_mode,
				     Window confine_to,
				     Cursor cursor,
				     Time time);
Atom         raw__xlib__XInternAtom(f2ptr cause, Display* display, char* atom_name, Bool only_if_exists);
Status       raw__xlib__XSetWMProtocols(f2ptr cause, Display* display, Window w, Atom* protocols, int count);
void         raw__xlib__XSetStandardProperties(f2ptr cause, Display* display,
					       Window w,
					       char* window_name,
					       char* icon_name,
					       Pixmap icon_pixmap,
					       char** argv, int argc,
					       XSizeHints *hints);
Status       raw__xlib__XGetGeometry(f2ptr cause, Display* display,
				     Drawable d,
				     Window* root_return,
				     int* x_return,
				     int* y_return,
				     unsigned int* width_return,
				     unsigned int* height_return,
				     unsigned int* border_width_return,
				     unsigned int* depth_return);
void         raw__xlib__XNextEvent(f2ptr cause, Display* display, XEvent* event_return);
KeySym       raw__xlib__XLookupKeysym(f2ptr cause, XKeyEvent* key_event, int index);
char*        raw__xlib__XGetAtomName(f2ptr cause, Display* display, Atom atom);
int          raw__xlib__XPending(f2ptr cause, Display* display);
int          raw__xlib__XDefaultScreen(f2ptr cause, Display *display);
XFontStruct* raw__xlib__XLoadQueryFont(f2ptr cause, Display* display, char* name);
int          raw__xlib__XFreeFont(f2ptr cause, Display* display, XFontStruct* font_struct);
#endif // F2__XLIB__H


#endif // F2__OPENGL__H


