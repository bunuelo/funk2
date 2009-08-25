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
  this->initialized     = boolean__false;
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
  status("funk2_opengl__load_library: loaded opengl function symbols successfully.");
  return boolean__true;
}

boolean_t raw__opengl__load_library(f2ptr cause) {
  return funk2_opengl__load_library(&(__funk2.opengl), cause);
}


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
  this->gluPerspective = (void(*)(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)) from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"gluPerspective")); if (! (this->gluPerspective)) {status("funk2_openglu__load_library: failed symbol, gluPerspective."); return boolean__false;}
  status("funk2_openglu__load_library: loaded openglu function symbols successfully.");
  return boolean__true;
}

boolean_t raw__openglu__load_library(f2ptr cause) {
  return funk2_openglu__load_library(&(__funk2.openglu), cause);
}



//lesson01.c:(.text+0x164): undefined reference to `glXSwapBuffers'
//lesson01.c:(.text+0x197): undefined reference to `glXMakeCurrent'
//lesson01.c:(.text+0x1be): undefined reference to `glXDestroyContext'
//lesson01.c:(.text+0x375): undefined reference to `glXChooseVisual'
//lesson01.c:(.text+0x39d): undefined reference to `glXChooseVisual'
//lesson01.c:(.text+0x3ea): undefined reference to `glXQueryVersion'
//lesson01.c:(.text+0x429): undefined reference to `glXCreateContext'
//lesson01.c:(.text+0x834): undefined reference to `glXMakeCurrent'
//lesson01.c:(.text+0x8ae): undefined reference to `glXIsDirect'

//lesson01.c:(.text+0x1f0): undefined reference to `XF86VidModeSwitchToMode'
//lesson01.c:(.text+0x217): undefined reference to `XF86VidModeSetViewPort'
//lesson01.c:(.text+0x224): undefined reference to `XCloseDisplay'
//lesson01.c:(.text+0x24a): undefined reference to `XOpenDisplay'
//lesson01.c:(.text+0x27b): undefined reference to `XF86VidModeQueryVersion'
//lesson01.c:(.text+0x2bb): undefined reference to `XF86VidModeGetAllModeLines'
//lesson01.c:(.text+0x474): undefined reference to `XCreateColormap'
//lesson01.c:(.text+0x4c0): undefined reference to `XF86VidModeSwitchToMode'
//lesson01.c:(.text+0x4e7): undefined reference to `XF86VidModeSetViewPort'
//lesson01.c:(.text+0x53c): undefined reference to `XFree'
//lesson01.c:(.text+0x5dc): undefined reference to `XCreateWindow'
//lesson01.c:(.text+0x630): undefined reference to `XWarpPointer'
//lesson01.c:(.text+0x647): undefined reference to `XMapRaised'
//lesson01.c:(.text+0x67e): undefined reference to `XGrabKeyboard'
//lesson01.c:(.text+0x6cf): undefined reference to `XGrabPointer'
//lesson01.c:(.text+0x76a): undefined reference to `XCreateWindow'
//lesson01.c:(.text+0x78c): undefined reference to `XInternAtom'
//lesson01.c:(.text+0x7b6): undefined reference to `XSetWMProtocols'
//lesson01.c:(.text+0x7fc): undefined reference to `XSetStandardProperties'
//lesson01.c:(.text+0x813): undefined reference to `XMapRaised'
//lesson01.c:(.text+0x882): undefined reference to `XGetGeometry'
//lesson01.c:(.text+0x95b): undefined reference to `XNextEvent'
//lesson01.c:(.text+0xa00): undefined reference to `XLookupKeysym'
//lesson01.c:(.text+0xa21): undefined reference to `XLookupKeysym'
//lesson01.c:(.text+0xa83): undefined reference to `XGetAtomName'
//lesson01.c:(.text+0xaaf): undefined reference to `XPending'
