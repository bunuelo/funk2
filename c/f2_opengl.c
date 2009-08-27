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

#include "funk2.h"

// funk2_opengl

void funk2_opengl__init(funk2_opengl_t* this) {
  this->initialized   = boolean__false;
  this->dlfcn_pointer = nil;
}

void funk2_opengl__destroy(funk2_opengl_t* this) {
}



boolean_t funk2_opengl__load_library(funk2_opengl_t* this, f2ptr cause) {
  if (this->initialized) {
    return boolean__true;
  }
  if (! f2__dlfcn__supported(cause)) {
    status("funk2_opengl__load_library: dlfcn is not supported on this system, so could not load opengl.");
    return boolean__false;
  }
  f2ptr filenames = f2cons__new(cause, new__string(cause, "/usr/X11R6/lib/libGL.so"),  nil);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib/xorg/libGL.so"),   filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib64/libGL.so"),      filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib64/xorg/libGL.so"), filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/local/lib/libGL.so"),  filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib/libGL.so"),        filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/lib/libGL.so"),            filenames);
  f2ptr dlfcn_pointer = nil;
  {
    f2ptr filename_iter = filenames;
    while ((! dlfcn_pointer) && filename_iter) {
      f2ptr filename  = f2cons__car(filename_iter, cause);
      dlfcn_pointer = f2__dlfcn__dlopen(cause, filename, nil);
      filename_iter = f2cons__cdr(filename_iter, cause);
    }
  }
  if (! dlfcn_pointer) {
    status("funk2_opengl__load_library: failed to open opengl dynamic library.");
    return boolean__false;
  }
  this->dlfcn_pointer = dlfcn_pointer;
  status("funk2_opengl__load_library: loaded opengl dynamic library successfully.");
#if defined(F2__GL__H)
  this->glViewport     = (void(*)(GLint x, GLint y, GLsizei width, GLsizei height))             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glViewport"));     if (! (this->glViewport))     {status("funk2_opengl__load_library: failed symbol, glViewport.");     return boolean__false;}
  this->glMatrixMode   = (void(*)(GLenum mode))                                                 from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glMatrixMode"));   if (! (this->glMatrixMode))   {status("funk2_opengl__load_library: failed symbol, glMatrixMode.");   return boolean__false;}
  this->glLoadIdentity = (void(*)())                                                            from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glLoadIdentity")); if (! (this->glLoadIdentity)) {status("funk2_opengl__load_library: failed symbol, glLoadIdentity."); return boolean__false;}
  this->glShadeModel   = (void(*)(GLenum mode))                                                 from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glShadeModel"));   if (! (this->glShadeModel))   {status("funk2_opengl__load_library: failed symbol, glShadeModel.");   return boolean__false;}
  this->glClearColor   = (void(*)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)) from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glClearColor"));   if (! (this->glClearColor))   {status("funk2_opengl__load_library: failed symbol, glClearColor.");   return boolean__false;}
  this->glClearDepth   = (void(*)(GLclampd depth))                                              from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glClearDepth"));   if (! (this->glClearDepth))   {status("funk2_opengl__load_library: failed symbol, glClearDepth.");   return boolean__false;}
  this->glEnable       = (void(*)(GLenum cap))                                                  from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glEnable"));       if (! (this->glEnable))       {status("funk2_opengl__load_library: failed symbol, glEnable.");       return boolean__false;}
  this->glDepthFunc    = (void(*)(GLenum func))                                                 from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glDepthFunc"));    if (! (this->glDepthFunc))    {status("funk2_opengl__load_library: failed symbol, glDepthFunc.");    return boolean__false;}
  this->glHint         = (void(*)(GLenum target, GLenum mode))                                  from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glHint"));         if (! (this->glHint))         {status("funk2_opengl__load_library: failed symbol, glHint.");         return boolean__false;}
  this->glFlush        = (void(*)())                                                            from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glFlush"));        if (! (this->glFlush))        {status("funk2_opengl__load_library: failed symbol, glFlush.");        return boolean__false;}
  this->glClear        = (void(*)(GLbitfield mask))                                             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glClear"));        if (! (this->glClear))        {status("funk2_opengl__load_library: failed symbol, glClear.");        return boolean__false;}
#endif // F2__GL__H
  status("funk2_opengl__load_library: loaded opengl function symbols successfully.");
  return boolean__true;
}

boolean_t raw__opengl__load_library(f2ptr cause) {
#if defined(F2__GL__H)
  return funk2_opengl__load_library(&(__funk2.opengl), cause);
#else
  status("funk2_opengl__load_library: opengl dynamic library not supported in this compile.");
  return boolean__false;
#endif // F2__GL__H
}

#if defined(F2__GL__H)
void raw__opengl__glViewport(f2ptr cause, GLint x, GLint y, GLsizei width, GLsizei height) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glViewport)(x, y, width, height);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
void raw__opengl__glMatrixMode(f2ptr cause, GLenum mode) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glMatrixMode)(mode);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
void raw__opengl__glLoadIdentity(f2ptr cause) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glLoadIdentity)();
}
#endif // F2__GL__H

#if defined(F2__GL__H)
void raw__opengl__glShadeModel(f2ptr cause, GLenum mode) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glShadeModel)(mode);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
void raw__opengl__glClearColor(f2ptr cause, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glClearColor)(red, green, blue, alpha);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
void raw__opengl__glClearDepth(f2ptr cause, GLclampd depth) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glClearDepth)(depth);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
void raw__opengl__glEnable(f2ptr cause, GLenum cap) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glEnable)(cap);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
void raw__opengl__glDepthFunc(f2ptr cause, GLenum func) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glDepthFunc)(func);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
void raw__opengl__glHint(f2ptr cause, GLenum target, GLenum mode) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glHint)(target, mode);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
void raw__opengl__glFlush(f2ptr cause) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glFlush)();
}
#endif // F2__GL__H

#if defined(F2__GL__H)
void raw__opengl__glClear(f2ptr cause, GLbitfield mask) {
  if (!__funk2.opengl.initialized) {return;}
  (*__funk2.opengl.glClear)(mask);
}
#endif // F2__GL__H

// funk2_openglu

void funk2_openglu__init(funk2_openglu_t* this) {
  this->initialized   = boolean__false;
  this->dlfcn_pointer = nil;
}

void funk2_openglu__destroy(funk2_openglu_t* this) {
}

boolean_t funk2_openglu__load_library(funk2_openglu_t* this, f2ptr cause) {
  if (this->initialized) {
    return boolean__true;
  }
  if (! f2__dlfcn__supported(cause)) {
    status("funk2_openglu__load_library: dlfcn is not supported on this system, so could not load openglu.");
    return boolean__false;
  }
  f2ptr filenames = f2cons__new(cause, new__string(cause, "/usr/X11R6/lib/libGLU.so"),  nil);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib/xorg/libGLU.so"),   filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib64/libGLU.so"),      filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib64/xorg/libGLU.so"), filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/local/lib/libGLU.so"),  filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib/libGLU.so"),        filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/lib/libGLU.so"),            filenames);
  f2ptr dlfcn_pointer = nil;
  {
    f2ptr filename_iter = filenames;
    while ((! dlfcn_pointer) && filename_iter) {
      f2ptr filename  = f2cons__car(filename_iter, cause);
      dlfcn_pointer = f2__dlfcn__dlopen(cause, filename, nil);
      filename_iter = f2cons__cdr(filename_iter, cause);
    }
  }
  if (! dlfcn_pointer) {
    status("funk2_openglu__load_library: failed to open openglu dynamic library.");
    return boolean__false;
  }
  this->dlfcn_pointer = dlfcn_pointer;
  status("funk2_openglu__load_library: loaded openglu dynamic library successfully.");
#if defined(F2__GLU__H)
  this->gluPerspective = (void(*)(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)) from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"gluPerspective")); if (! (this->gluPerspective)) {status("funk2_openglu__load_library: failed symbol, gluPerspective."); return boolean__false;}
#endif // F2__GLU__H
  status("funk2_openglu__load_library: loaded openglu function symbols successfully.");
  return boolean__true;
}

#if defined(F2__GL__H)
void raw__openglu__gluPerspective(f2ptr cause, GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
  if (!__funk2.openglu.initialized) {return;}
  (*__funk2.openglu.gluPerspective)(fovy, aspect, zNear, zFar);
}
#endif // F2__GL__H

boolean_t raw__openglu__load_library(f2ptr cause) {
#if defined(F2__GLU__H)
  return funk2_openglu__load_library(&(__funk2.openglu), cause);
#else
  status("funk2_openglu__load_library: openglu dynamic library not supported in this compile.");
  return boolean__false;
#endif // F2__GLU__H
}

// funk2_xxf86vm

void funk2_xxf86vm__init(funk2_xxf86vm_t* this) {
  this->initialized   = boolean__false;
  this->dlfcn_pointer = nil;
}

void funk2_xxf86vm__destroy(funk2_xxf86vm_t* this) {
}

boolean_t funk2_xxf86vm__load_library(funk2_xxf86vm_t* this, f2ptr cause) {
  if (this->initialized) {
    return boolean__true;
  }
  if (! f2__dlfcn__supported(cause)) {
    status("funk2_xxf86vm__load_library: dlfcn is not supported on this system, so could not load xxf86vm.");
    return boolean__false;
  }
  f2ptr filenames = f2cons__new(cause, new__string(cause, "/usr/X11R6/lib/libXxf86vm.so"),  nil);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib/xorg/libXxf86vm.so"),   filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib64/libXxf86vm.so"),      filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib64/xorg/libXxf86vm.so"), filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/local/lib/libXxf86vm.so"),  filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib/libXxf86vm.so"),        filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/lib/libXxf86vm.so"),            filenames);
  f2ptr dlfcn_pointer = nil;
  {
    f2ptr filename_iter = filenames;
    while ((! dlfcn_pointer) && filename_iter) {
      f2ptr filename  = f2cons__car(filename_iter, cause);
      dlfcn_pointer = f2__dlfcn__dlopen(cause, filename, nil);
      filename_iter = f2cons__cdr(filename_iter, cause);
    }
  }
  if (! dlfcn_pointer) {
    status("funk2_xxf86vm__load_library: failed to open xxf86vm dynamic library.");
    return boolean__false;
  }
  this->dlfcn_pointer = dlfcn_pointer;
  //status("funk2_xxf86vm__load_library: loaded xxf86vm dynamic library successfully.");
#if defined(F2__XF86VMODE__H)
  this->XF86VidModeSwitchToMode    = (Bool(*)(Display* display, int screen, XF86VidModeModeInfo* modeline))                           from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XF86VidModeSwitchToMode"));    if (! (this->XF86VidModeSwitchToMode))    {status("funk2_xxf86vm__load_library: failed symbol, XF86VidModeSwitchToMode."); return boolean__false;}
  this->XF86VidModeSetViewPort     = (Bool(*)(Display* display, int screen, int x, int y))                                            from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XF86VidModeSetViewPort"));     if (! (this->XF86VidModeSetViewPort))     {status("funk2_xxf86vm__load_library: failed symbol, XF86VidModeSetViewPort."); return boolean__false;}
  this->XF86VidModeQueryVersion    = (Bool(*)(Display* display, int* major_version_return, int* minor_version_return))                from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XF86VidModeQueryVersion"));    if (! (this->XF86VidModeQueryVersion))    {status("funk2_xxf86vm__load_library: failed symbol, XF86VidModeQueryVersion."); return boolean__false;}
  this->XF86VidModeGetAllModeLines = (Bool(*)(Display* display, int screen, int* modecount_return, XF86VidModeModeInfo*** modesinfo)) from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XF86VidModeGetAllModeLines")); if (! (this->XF86VidModeGetAllModeLines)) {status("funk2_xxf86vm__load_library: failed symbol, XF86VidModeGetAllModeLines."); return boolean__false;}
#endif // F2__XF86VMODE__H
  status("funk2_xxf86vm__load_library: loaded xxf86vm function symbols successfully.");
  return boolean__true;
}

#if defined(F2__GL__H)
Bool raw__xxf86vm__XF86VidModeSwitchToMode(f2ptr cause, Display* display, int screen, XF86VidModeModeInfo* modeline) {
  if (!__funk2.openglu.initialized) {return boolean__false;;}
  return (*__funk2.xxf86vm.XF86VidModeSwitchToMode)(display, screen, modeline);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
Bool raw__xxf86vm__XF86VidModeSetViewPort(f2ptr cause, Display* display, int screen, int x, int y) {
  if (!__funk2.openglu.initialized) {return boolean__false;;}
  return (*__funk2.xxf86vm.XF86VidModeSetViewPort)(display, screen, x, y);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
Bool raw__xxf86vm__XF86VidModeQueryVersion(f2ptr cause, Display* display, int* major_version_return, int* minor_version_return) {
  if (!__funk2.openglu.initialized) {return boolean__false;}
  return (*__funk2.xxf86vm.XF86VidModeQueryVersion)(display, major_version_return, minor_version_return);
}
#endif // F2__GL__H

#if defined(F2__GL__H)
Bool raw__xxf86vm__XF86VidModeGetAllModeLines(f2ptr cause, Display* display, int screen, int* modecount_return, XF86VidModeModeInfo*** modesinfo) {
  if (!__funk2.openglu.initialized) {return boolean__false;}
  return (*__funk2.xxf86vm.XF86VidModeGetAllModeLines)(display, screen, modecount_return, modesinfo);
}
#endif // F2__GL__H


boolean_t raw__xxf86vm__load_library(f2ptr cause) {
#if defined(F2__XF86VMODE__H)
  return funk2_xxf86vm__load_library(&(__funk2.xxf86vm), cause);
#else
  status("funk2_xxf86vm__load_library: xxf86vm dynamic library not supported in this compile.");
  return boolean__false;
#endif // F2__XF86VMODE__H
}


// funk2_xlib

void funk2_xlib__init(funk2_xlib_t* this) {
  this->initialized   = boolean__false;
  this->dlfcn_pointer = nil;
}

void funk2_xlib__destroy(funk2_xlib_t* this) {
}

boolean_t funk2_xlib__load_library(funk2_xlib_t* this, f2ptr cause) {
  if (this->initialized) {
    return boolean__true;
  }
  if (! f2__dlfcn__supported(cause)) {
    status("funk2_xlib__load_library: dlfcn is not supported on this system, so could not load xlib.");
    return boolean__false;
  }
  f2ptr filenames = f2cons__new(cause, new__string(cause, "/usr/X11R6/lib/libX11.so"),  nil);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib/xorg/libX11.so"),   filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib64/libX11.so"),      filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib64/xorg/libX11.so"), filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/local/lib/libX11.so"),  filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/usr/lib/libX11.so"),        filenames);
  filenames       = f2cons__new(cause, new__string(cause, "/lib/libX11.so"),            filenames);
  f2ptr dlfcn_pointer = nil;
  {
    f2ptr filename_iter = filenames;
    while ((! dlfcn_pointer) && filename_iter) {
      f2ptr filename  = f2cons__car(filename_iter, cause);
      dlfcn_pointer = f2__dlfcn__dlopen(cause, filename, nil);
      filename_iter = f2cons__cdr(filename_iter, cause);
    }
  }
  if (! dlfcn_pointer) {
    status("funk2_xlib__load_library: failed to open xlib dynamic library.");
    return boolean__false;
  }
  this->dlfcn_pointer = dlfcn_pointer;
  status("funk2_xlib__load_library: loaded xlib dynamic library successfully.");
#if defined(F2__XLIB__H)
  this->XCloseDisplay          = (void(*)(Display* display))                                          from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XCloseDisplay"));          if (! (this->XCloseDisplay))          {status("funk2_xlib__load_library: failed symbol, XCloseDisplay.");   return boolean__false;}
  this->XOpenDisplay           = (Display*(*)(char* display_name))                                    from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XOpenDisplay"));           if (! (this->XOpenDisplay))           {status("funk2_xlib__load_library: failed symbol, XOpenDisplay.");    return boolean__false;}
  this->XCreateColormap        = (Colormap(*)(Display* display, Window w, Visual* visual, int alloc)) from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XCreateColormap"));        if (! (this->XCreateColormap))        {status("funk2_xlib__load_library: failed symbol, XCreateColormap."); return boolean__false;}
  this->XFree                  = (int(*)(void* data))                                                 from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XFree"));                  if (! (this->XFree))                  {status("funk2_xlib__load_library: failed symbol, XFree.");           return boolean__false;}
  this->XCreateWindow          = (Window(*)(Display* display,
					     Window parent,
					     int x, int y,
					     unsigned int width, unsigned int height,
					     unsigned int border_width,
					     int depth,
					     unsigned int class,
					     Visual* visual,
					     unsigned long valuemask,
					     XSetWindowAttributes* attributes))                        from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XCreateWindow"));          if (! (this->XCreateWindow))          {status("funk2_xlib__load_library: failed symbol, XCreateWindow.");   return boolean__false;};
  this->XWarpPointer           = (void(*)(Display* display,
					  Window src_w, Window dest_w,
					  int src_x, int src_y,
					  unsigned int src_width, unsigned int src_height,
					  int dest_x, int dest_y))                                    from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XWarpPointer"));           if (! (this->XWarpPointer))           {status("funk2_xlib__load_library: failed symbol, XWarpPointer.");    return boolean__false;};
  this->XMapRaised             = (void(*)(Display* display, Window w))                                from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XMapRaised"));             if (! (this->XMapRaised))             {status("funk2_xlib__load_library: failed symbol, XMapRaised.");      return boolean__false;};
  this->XGrabKeyboard          = (int(*)(Display* display,
					 Window grab_window,
					 Bool owner_events,
					 int pointer_mode,
					 int keyboard_mode,
					 Time time))                                                  from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XGrabKeyboard"));          if (! (this->XGrabKeyboard))          {status("funk2_xlib__load_library: failed symbol, XGrabKeyboard.");   return boolean__false;};
  this->XGrabPointer           = (int(*)(Display* display,
					 Window grab_window,
					 Bool owner_events,
					 unsigned int event_mask,
					 int pointer_mode,
					 int keyboard_mode,
					 Window confine_to,
					 Cursor cursor,
					 Time time))                                                  from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XGrabPointer"));           if (! (this->XGrabPointer))           {status("funk2_xlib__load_library: failed symbol, XGrabPointer.");    return boolean__false;};
  this->XInternAtom            = (Atom(*)(Display* display, char* atom_name, Bool only_if_exists))    from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XInternAtom"));            if (! (this->XInternAtom))            {status("funk2_xlib__load_library: failed symbol, XInternAtom.");     return boolean__false;};
  this->XSetWMProtocols        = (Status(*)(Display* display, Window w, Atom* protocols, int count))  from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XSetWMProtocols"));        if (! (this->XSetWMProtocols))        {status("funk2_xlib__load_library: failed symbol, XSetWMProtocols."); return boolean__false;};
  this->XSetStandardProperties = (void(*)(Display* display,
					  Window w,
					  char* window_name,
					  char* icon_name,
					  Pixmap icon_pixmap,
					  char** argv, int argc,
					  XSizeHints *hints))                                         from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XSetStandardProperties")); if (! (this->XSetStandardProperties)) {status("funk2_xlib__load_library: failed symbol, XSetStandardProperties."); return boolean__false;};
  this->XGetGeometry           = (Status(*)(Display* display,
					    Drawable d,
					    Window* root_return,
					    int* x_return,
					    int* y_return,
					    unsigned int* width_return,
					    unsigned int* height_return,
					    unsigned int* border_width_return,
					    unsigned int* depth_return))                              from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XGetGeometry"));           if (! (this->XGetGeometry))           {status("funk2_xlib__load_library: failed symbol, XGetGeometry.");           return boolean__false;};
  this->XNextEvent             = (void(*)(Display* display, XEvent* event_return))                    from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XNextEvent"));             if (! (this->XNextEvent))             {status("funk2_xlib__load_library: failed symbol, XNextEvent.");             return boolean__false;};
  this->XLookupKeysym          = (KeySym(*)(XKeyEvent* key_event, int index))                         from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XLookupKeysym"));          if (! (this->XLookupKeysym))          {status("funk2_xlib__load_library: failed symbol, XLookupKeysym.");          return boolean__false;};
  this->XGetAtomName           = (char*(*)(Display* display, Atom atom))                              from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XGetAtomName"));           if (! (this->XGetAtomName))           {status("funk2_xlib__load_library: failed symbol, XGetAtomName.");           return boolean__false;};
  this->XPending               = (int(*)(Display *display))                                           from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XPending"));               if (! (this->XPending))               {status("funk2_xlib__load_library: failed symbol, XPending.");               return boolean__false;};
#endif // F2__XLIB__H
  status("funk2_xlib__load_library: loaded xlib function symbols successfully.");
  return boolean__true;
}

#if defined(F2__XLIB__H)
void raw__xlib__XCloseDisplay(f2ptr cause, Display* display) {
  if (!__funk2.xlib.initialized) {return;}
  (*__funk2.xlib.XCloseDisplay)(display);
}
#endif // F2__XLIB__H

#if defined(F2__XLIB__H)
Display* raw__xlib__XOpenDisplay(f2ptr cause, char* display_name) {
  if (!__funk2.xlib.initialized) {return NULL;}
  return (*__funk2.xlib.XOpenDisplay)(display_name);
}
#endif // F2__XLIB__H

#if defined(F2__XLIB__H)
Colormap raw__xlib__XCreateColormap(f2ptr cause, Display* display, Window w, Visual* visual, int alloc) {
  if (!__funk2.xlib.initialized) {return (Colormap)0;}
  return (*__funk2.xlib.XCreateColormap)(display, w, visual, alloc);
}
#endif // F2__XLIB__H


boolean_t raw__xlib__load_library(f2ptr cause) {
#if defined(F2__XLIB__H)
  return funk2_xlib__load_library(&(__funk2.xlib), cause);
#else
  status("funk2_xlib__load_library: xlib dynamic library not supported in this compile.");
  return boolean__false;
#endif // F2__XLIB__H
}


