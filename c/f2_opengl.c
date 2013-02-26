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
  f2ptr filenames = raw__cons__new(cause, new__string(cause, "/usr/X11R6/lib/libGL.so"),  nil);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib/xorg/libGL.so"),   filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib64/libGL.so"),      filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib64/xorg/libGL.so"), filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/local/lib/libGL.so"),  filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib/libGL.so"),        filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/lib/libGL.so"),            filenames);
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
  this->glViewport        = (void(*)(GLint x, GLint y, GLsizei width, GLsizei height))                         from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glViewport"));        if (! (this->glViewport))        {status("funk2_opengl__load_library: failed symbol, glViewport.");        return boolean__false;}
  this->glMatrixMode      = (void(*)(GLenum mode))                                                             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glMatrixMode"));      if (! (this->glMatrixMode))      {status("funk2_opengl__load_library: failed symbol, glMatrixMode.");      return boolean__false;}
  this->glLoadIdentity    = (void(*)())                                                                        from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glLoadIdentity"));    if (! (this->glLoadIdentity))    {status("funk2_opengl__load_library: failed symbol, glLoadIdentity.");    return boolean__false;}
  this->glShadeModel      = (void(*)(GLenum mode))                                                             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glShadeModel"));      if (! (this->glShadeModel))      {status("funk2_opengl__load_library: failed symbol, glShadeModel.");      return boolean__false;}
  this->glClearColor      = (void(*)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glClearColor"));      if (! (this->glClearColor))      {status("funk2_opengl__load_library: failed symbol, glClearColor.");      return boolean__false;}
  this->glClearDepth      = (void(*)(GLclampd depth))                                                          from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glClearDepth"));      if (! (this->glClearDepth))      {status("funk2_opengl__load_library: failed symbol, glClearDepth.");      return boolean__false;}
  this->glEnable          = (void(*)(GLenum cap))                                                              from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glEnable"));          if (! (this->glEnable))          {status("funk2_opengl__load_library: failed symbol, glEnable.");          return boolean__false;}
  this->glDepthFunc       = (void(*)(GLenum func))                                                             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glDepthFunc"));       if (! (this->glDepthFunc))       {status("funk2_opengl__load_library: failed symbol, glDepthFunc.");       return boolean__false;}
  this->glHint            = (void(*)(GLenum target, GLenum mode))                                              from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glHint"));            if (! (this->glHint))            {status("funk2_opengl__load_library: failed symbol, glHint.");            return boolean__false;}
  this->glFlush           = (void(*)())                                                                        from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glFlush"));           if (! (this->glFlush))           {status("funk2_opengl__load_library: failed symbol, glFlush.");           return boolean__false;}
  this->glClear           = (void(*)(GLbitfield mask))                                                         from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glClear"));           if (! (this->glClear))           {status("funk2_opengl__load_library: failed symbol, glClear.");           return boolean__false;}
  this->glLightfv         = (void(*)(GLenum light, GLenum pname, const GLfloat* params))                       from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glLightfv"));         if (! (this->glLightfv))         {status("funk2_opengl__load_library: failed symbol, glLightfv.");         return boolean__false;}
  this->glCullFace        = (void(*)(GLenum mode))                                                             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glCullFace"));        if (! (this->glCullFace))        {status("funk2_opengl__load_library: failed symbol, glCullFace.");        return boolean__false;}
  this->glTranslatef      = (void(*)(GLfloat x, GLfloat y, GLfloat z))                                         from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glTranslatef"));      if (! (this->glTranslatef))      {status("funk2_opengl__load_library: failed symbol, glTranslatef.");      return boolean__false;}
  this->glRotatef         = (void(*)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z))                          from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glRotatef"));         if (! (this->glRotatef))         {status("funk2_opengl__load_library: failed symbol, glRotatef.");         return boolean__false;}
  this->glColor4f         = (void(*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha))                 from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glColor4f"));         if (! (this->glColor4f))         {status("funk2_opengl__load_library: failed symbol, glColor4f.");         return boolean__false;}
  this->glBegin           = (void(*)(GLenum mode))                                                             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glBegin"));           if (! (this->glBegin))           {status("funk2_opengl__load_library: failed symbol, glBegin.");           return boolean__false;}
  this->glNormal3f        = (void(*)(GLfloat nx, GLfloat ny, GLfloat nz))                                      from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glNormal3f"));        if (! (this->glNormal3f))        {status("funk2_opengl__load_library: failed symbol, glNormal3f.");        return boolean__false;}
  this->glVertex3f        = (void(*)(GLfloat x, GLfloat y, GLfloat z))                                         from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glVertex3f"));        if (! (this->glVertex3f))        {status("funk2_opengl__load_library: failed symbol, glVertex3f.");        return boolean__false;}
  this->glEnd             = (void(*)())                                                                        from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glEnd"));             if (! (this->glEnd))             {status("funk2_opengl__load_library: failed symbol, glEnd.");             return boolean__false;}
  this->glMaterialfv      = (void(*)(GLenum face, GLenum pname, const GLfloat* params))                        from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glMaterialfv"));      if (! (this->glMaterialfv))      {status("funk2_opengl__load_library: failed symbol, glMaterialfv.");      return boolean__false;}
  this->glPushMatrix      = (void(*)())                                                                        from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glPushMatrix"));      if (! (this->glPushMatrix))      {status("funk2_opengl__load_library: failed symbol, glPushMatrix.");      return boolean__false;}
  this->glPopMatrix       = (void(*)())                                                                        from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glPopMatrix"));       if (! (this->glPopMatrix))       {status("funk2_opengl__load_library: failed symbol, glPopMatrix.");       return boolean__false;}
  this->glGenTextures     = (void(*)(GLsizei n, GLuint *textures))                                             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glGenTextures"));     if (! (this->glGenTextures))     {status("funk2_opengl__load_library: failed symbol, glGenTextures.");     return boolean__false;}
  this->glDeleteTextures  = (void(*)(GLsizei n, GLuint *textures))                                             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glDeleteTextures"));  if (! (this->glDeleteTextures))  {status("funk2_opengl__load_library: failed symbol, glDeleteTextures.");  return boolean__false;}
  this->glBindTexture     = (void(*)(GLenum target, GLuint texture))                                           from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glBindTexture"));     if (! (this->glGenTextures))     {status("funk2_opengl__load_library: failed symbol, glBindTexture.");     return boolean__false;}
  this->glTexImage2D      = (void(*)(GLenum target,
				     GLint level,
				     GLint internalFormat,
				     GLsizei width,
				     GLsizei height,
				     GLint border,
				     GLenum format,
				     GLenum type,
				     const GLvoid* data))                                                      from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glTexImage2D"));      if (! (this->glTexImage2D))      {status("funk2_opengl__load_library: failed symbol, glTexImage2D.");      return boolean__false;}
  this->glTexParameteri   = (void(*)(GLenum target, GLenum pname, GLint param))                                from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glTexParameteri"));   if (! (this->glTexParameteri))   {status("funk2_opengl__load_library: failed symbol, glTexParameteri.");   return boolean__false;}
  this->glTexCoord2f      = (void(*)(GLfloat s, GLfloat t))                                                    from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glTexCoord2f"));      if (! (this->glTexCoord2f))      {status("funk2_opengl__load_library: failed symbol, glTexCoord2f.");      return boolean__false;}
  this->glBlendFunc       = (void(*)(GLenum sfactor, GLenum dfactor))                                          from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glBlendFunc"));       if (! (this->glBlendFunc))       {status("funk2_opengl__load_library: failed symbol, glBlendFunc.");       return boolean__false;}
  this->glScalef          = (void(*)(GLfloat x, GLfloat y, GLfloat z))                                         from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glScalef"));          if (! (this->glScalef))          {status("funk2_opengl__load_library: failed symbol, glScalef.");          return boolean__false;}
  this->glDisable         = (void(*)(GLenum cap))                                                              from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glDisable"));         if (! (this->glDisable))         {status("funk2_opengl__load_library: failed symbol, glDisable.");         return boolean__false;}
  this->glGenLists        = (GLuint(*)(GLsizei range))                                                         from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glGenLists"));        if (! (this->glGenLists))        {status("funk2_opengl__load_library: failed symbol, glGenLists.");        return boolean__false;}
  this->glDeleteLists     = (void(*)(GLuint list, GLsizei range))                                              from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glDeleteLists"));     if (! (this->glDeleteLists))     {status("funk2_opengl__load_library: failed symbol, glDeleteLists.");     return boolean__false;}
  this->glPushAttrib      = (void(*)(GLbitfield mask))                                                         from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glPushAttrib"));      if (! (this->glPushAttrib))      {status("funk2_opengl__load_library: failed symbol, glPushAttrib.");      return boolean__false;}
  this->glListBase        = (void(*)(GLuint base))                                                             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glListBase"));        if (! (this->glListBase))        {status("funk2_opengl__load_library: failed symbol, glListBase.");        return boolean__false;}
  this->glCallLists       = (void(*)(GLsizei n, GLenum type, const GLvoid* lists))                             from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glCallLists"));       if (! (this->glCallLists))       {status("funk2_opengl__load_library: failed symbol, glCallLists.");       return boolean__false;}
  this->glPopAttrib       = (void(*)())                                                                        from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glPopAttrib"));       if (! (this->glPopAttrib))       {status("funk2_opengl__load_library: failed symbol, glPopAttrib.");       return boolean__false;}
  this->glRasterPos3f     = (void(*)(GLfloat x, GLfloat y, GLfloat z))                                         from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glRasterPos3f"));     if (! (this->glRasterPos3f))     {status("funk2_opengl__load_library: failed symbol, glRasterPos3f.");     return boolean__false;}
  this->glGetFloatv       = (void(*)(GLenum pname, GLfloat *params))                                           from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glGetFloatv"));       if (! (this->glGetFloatv))       {status("funk2_opengl__load_library: failed symbol, glGetFloatv.");       return boolean__false;}
  this->glMultMatrixf     = (void(*)(const GLfloat* m))                                                        from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glMultMatrixf"));     if (! (this->glMultMatrixf))     {status("funk2_opengl__load_library: failed symbol, glMultMatrixf.");     return boolean__false;}
  this->glLoadMatrixf     = (void(*)(const GLfloat* m))                                                        from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glLoadMatrixf"));     if (! (this->glLoadMatrixf))     {status("funk2_opengl__load_library: failed symbol, glLoadMatrixf.");     return boolean__false;}
#endif // F2__GL__H

#if defined(F2__GLX__H)  
  // glx extension functions here
  this->glXSwapBuffers    = (void(*)(Display* dpy, GLXDrawable drawable))                                      from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glXSwapBuffers"));    if (! (this->glXSwapBuffers))    {status("funk2_opengl__load_library: failed symbol, glXSwapBuffers.");    return boolean__false;}
  this->glXMakeCurrent    = (Bool(*)(Display* dpy, GLXDrawable drawable, GLXContext ctx))                      from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glXMakeCurrent"));    if (! (this->glXMakeCurrent))    {status("funk2_opengl__load_library: failed symbol, glXMakeCurrent.");    return boolean__false;}
  this->glXDestroyContext = (void(*)(Display* dpy, GLXContext ctx))                                            from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glXDestroyContext")); if (! (this->glXDestroyContext)) {status("funk2_opengl__load_library: failed symbol, glXDestroyContext."); return boolean__false;}
  this->glXChooseVisual   = (XVisualInfo*(*)(Display* dpy, int screen, int* attribList))                       from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glXChooseVisual"));   if (! (this->glXChooseVisual))   {status("funk2_opengl__load_library: failed symbol, glXChooseVisual.");   return boolean__false;}
  this->glXQueryVersion   = (Bool(*)(Display* dpy, int* Major, int* Minor))                                    from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glXQueryVersion"));   if (! (this->glXQueryVersion))   {status("funk2_opengl__load_library: failed symbol, glXQueryVersion.");   return boolean__false;}
  this->glXCreateContext  = (GLXContext(*)(Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct)) from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glXCreateContext"));  if (! (this->glXCreateContext))  {status("funk2_opengl__load_library: failed symbol, glXCreateContext.");  return boolean__false;}
  this->glXIsDirect       = (Bool(*)(Display* dpy, GLXContext ctx))                                            from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glXIsDirect"));       if (! (this->glXIsDirect))       {status("funk2_opengl__load_library: failed symbol, glXIsDirect.");       return boolean__false;}
  this->glXUseXFont       = (void(*)(Font font, int First, int Count, int ListBase))                           from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"glXUseXFont"));       if (! (this->glXUseXFont))       {status("funk2_opengl__load_library: failed symbol, glXUseXFont.");       return boolean__false;}
#endif // F2__GLX__H
  
  status("funk2_opengl__load_library: loaded opengl function symbols successfully.");
  this->initialized = boolean__true;
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
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glViewport)(x, y, width, height);
}

void raw__opengl__glMatrixMode(f2ptr cause, GLenum mode) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glMatrixMode)(mode);
}

void raw__opengl__glLoadIdentity(f2ptr cause) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glLoadIdentity)();
}

void raw__opengl__glShadeModel(f2ptr cause, GLenum mode) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glShadeModel)(mode);
}

void raw__opengl__glClearColor(f2ptr cause, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glClearColor)(red, green, blue, alpha);
}

void raw__opengl__glClearDepth(f2ptr cause, GLclampd depth) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glClearDepth)(depth);
}

void raw__opengl__glEnable(f2ptr cause, GLenum cap) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glEnable)(cap);
}

void raw__opengl__glDepthFunc(f2ptr cause, GLenum func) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glDepthFunc)(func);
}

void raw__opengl__glHint(f2ptr cause, GLenum target, GLenum mode) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glHint)(target, mode);
}

void raw__opengl__glFlush(f2ptr cause) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glFlush)();
}

void raw__opengl__glClear(f2ptr cause, GLbitfield mask) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glClear)(mask);
}

void raw__opengl__glLightfv(f2ptr cause, GLenum light, GLenum pname, const GLfloat* params) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glLightfv)(light, pname, params);
}

void raw__opengl__glCullFace(f2ptr cause, GLenum mode) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glCullFace)(mode);
}

void raw__opengl__glTranslatef(f2ptr cause, GLfloat x, GLfloat y, GLfloat z) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glTranslatef)(x, y, z);
}

void raw__opengl__glRotatef(f2ptr cause, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glRotatef)(angle, x, y, z);
}

void raw__opengl__glColor4f(f2ptr cause, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glColor4f)(red, green, blue, alpha);
}

void raw__opengl__glBegin(f2ptr cause, GLenum mode) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glBegin)(mode);
}

void raw__opengl__glNormal3f(f2ptr cause, GLfloat nx, GLfloat ny, GLfloat nz) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glNormal3f)(nx, ny, nz);
}

void raw__opengl__glVertex3f(f2ptr cause, GLfloat x, GLfloat y, GLfloat z) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glVertex3f)(x, y, z);
}

void raw__opengl__glEnd(f2ptr cause) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glEnd)();
}

void raw__opengl__glPushMatrix(f2ptr cause) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glPushMatrix)();
}

void raw__opengl__glPopMatrix(f2ptr cause) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glPopMatrix)();
}

void raw__opengl__glMaterialfv(f2ptr cause, GLenum face, GLenum pname, const GLfloat* params) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glMaterialfv)(face, pname, params);
}

void raw__opengl__glGenTextures(f2ptr cause, GLsizei n, GLuint* textures) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glGenTextures)(n, textures);
}

void raw__opengl__glDeleteTextures(f2ptr cause, GLsizei n, GLuint* textures) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glDeleteTextures)(n, textures);
}

void raw__opengl__glBindTexture(f2ptr cause, GLenum target, GLuint texture) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glBindTexture)(target, texture);
}

void raw__opengl__glTexImage2D(f2ptr cause, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glTexImage2D)(target, level, internalFormat, width, height, border, format, type, data);
}

void raw__opengl__glTexParameteri(f2ptr cause, GLenum target, GLenum pname, GLint param) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glTexParameteri)(target, pname, param);
}

void raw__opengl__glTexCoord2f(f2ptr cause, GLfloat s, GLfloat t) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glTexCoord2f)(s, t);
}

void raw__opengl__glBlendFunc(f2ptr cause, GLenum sfactor, GLenum dfactor) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glBlendFunc)(sfactor, dfactor);
}

void raw__opengl__glScalef(f2ptr cause, GLfloat x, GLfloat y, GLfloat z) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glScalef)(x, y, z);
}

void raw__opengl__glDisable(f2ptr cause, GLenum cap) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glDisable)(cap);
}

GLuint raw__opengl__glGenLists(f2ptr cause, GLsizei range) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return -1;}
  return (*__funk2.opengl.glGenLists)(range);
}

void raw__opengl__glDeleteLists(f2ptr cause, GLuint list, GLsizei range) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glDeleteLists)(list, range);
}

void raw__opengl__glPushAttrib(f2ptr cause, GLbitfield mask) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glPushAttrib)(mask);
}

void raw__opengl__glListBase(f2ptr cause, GLuint base) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glListBase)(base);
}

void raw__opengl__glCallLists(f2ptr cause, GLsizei n, GLenum type, const GLvoid* lists) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glCallLists)(n, type, lists);
}

void raw__opengl__glPopAttrib(f2ptr cause) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glPopAttrib)();
}

void raw__opengl__glRasterPos3f(f2ptr cause, GLfloat x, GLfloat y, GLfloat z) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glRasterPos3f)(x, y, z);
}

void raw__opengl__glGetFloatv(f2ptr cause, GLenum pname, GLfloat *params) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glGetFloatv)(pname, params);
}

void raw__opengl__glMultMatrixf(f2ptr cause, const GLfloat* m) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glMultMatrixf)(m);
}

void raw__opengl__glLoadMatrixf(f2ptr cause, const GLfloat* m) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called opengl function without loading gl. ***"); return;}
  (*__funk2.opengl.glLoadMatrixf)(m);
}

#endif // F2__GL__H


#if defined(F2__GLX__H)

// glx extension functions

void raw__opengl__glXSwapBuffers(f2ptr cause, Display* dpy, GLXDrawable drawable) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called glx function without loading gl. ***"); return;}
  (*__funk2.opengl.glXSwapBuffers)(dpy, drawable);
}

Bool raw__opengl__glXMakeCurrent(f2ptr cause, Display* dpy, GLXDrawable drawable, GLXContext ctx) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called glx function without loading gl. ***"); return False;}
  return (*__funk2.opengl.glXMakeCurrent)(dpy, drawable, ctx);
}

void raw__opengl__glXDestroyContext(f2ptr cause, Display* dpy, GLXContext ctx) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called glx function without loading gl. ***"); return;}
  (*__funk2.opengl.glXDestroyContext)(dpy, ctx);
}

XVisualInfo* raw__opengl__glXChooseVisual(f2ptr cause, Display* dpy, int screen, int* attribList) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called glx function without loading gl. ***"); return NULL;}
  return (*__funk2.opengl.glXChooseVisual)(dpy, screen, attribList);
}

Bool raw__opengl__glXQueryVersion(f2ptr cause, Display* dpy, int* Major, int* Minor) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called glx function without loading gl. ***"); return False;}
  return (*__funk2.opengl.glXQueryVersion)(dpy, Major, Minor);
}

GLXContext raw__opengl__glXCreateContext(f2ptr cause, Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called glx function without loading gl. ***"); return (GLXContext)NULL;}
  return (*__funk2.opengl.glXCreateContext)(dpy, vis, shareList, direct);
}

Bool raw__opengl__glXIsDirect(f2ptr cause, Display* dpy, GLXContext ctx) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called glx function without loading gl. ***"); return False;}
  return (*__funk2.opengl.glXIsDirect)(dpy, ctx);
}

void raw__opengl__glXUseXFont(f2ptr cause, Font font, int First, int Count, int ListBase) {
  if (!__funk2.opengl.initialized) {status("*** WARNING: called glx function without loading gl. ***"); return;}
  (*__funk2.opengl.glXUseXFont)(font, First, Count, ListBase);
}


#endif // F2__GLX__H

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
  f2ptr filenames = raw__cons__new(cause, new__string(cause, "/usr/X11R6/lib/libGLU.so"),  nil);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib/xorg/libGLU.so"),   filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib64/libGLU.so"),      filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib64/xorg/libGLU.so"), filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/local/lib/libGLU.so"),  filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib/libGLU.so"),        filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/lib/libGLU.so"),            filenames);
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
  this->gluPerspective    = (void(*)(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar))                                                     from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"gluPerspective"));    if (! (this->gluPerspective)) {status("funk2_openglu__load_library: failed symbol, gluPerspective."); return boolean__false;}
  this->gluBuild2DMipmaps = (GLint(*)(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data)) from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"gluBuild2DMipmaps")); if (! (this->gluPerspective)) {status("funk2_openglu__load_library: failed symbol, gluBuild2DMipmaps."); return boolean__false;}
#endif // F2__GLU__H
  status("funk2_openglu__load_library: loaded openglu function symbols successfully.");
  this->initialized = boolean__true;
  return boolean__true;
}

#if defined(F2__GLU__H)
void raw__openglu__gluPerspective(f2ptr cause, GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
  if (!__funk2.openglu.initialized) {status("*** WARNING: called xlib function without loading glu. ***"); return;}
  (*__funk2.openglu.gluPerspective)(fovy, aspect, zNear, zFar);
}

GLint raw__openglu__gluBuild2DMipmaps(f2ptr cause, GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data) {
  if (!__funk2.openglu.initialized) {status("*** WARNING: called xlib function without loading glu. ***"); return -1;}
  return (*__funk2.openglu.gluBuild2DMipmaps)(target, internalFormat, width, height, format, type, data);
}

#endif // F2__GLU__H

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
  f2ptr filenames = raw__cons__new(cause, new__string(cause, "/usr/X11R6/lib/libXxf86vm.so"),  nil);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib/xorg/libXxf86vm.so"),   filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib64/libXxf86vm.so"),      filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib64/xorg/libXxf86vm.so"), filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/local/lib/libXxf86vm.so"),  filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib/libXxf86vm.so"),        filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/lib/libXxf86vm.so"),            filenames);
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
  this->initialized = boolean__true;
  return boolean__true;
}

#if defined(F2__XF86VMODE__H)
Bool raw__xxf86vm__XF86VidModeSwitchToMode(f2ptr cause, Display* display, int screen, XF86VidModeModeInfo* modeline) {
  if (!__funk2.openglu.initialized) {status("*** WARNING: called xlib function without loading xxf86vm. ***"); return boolean__false;}
  return (*__funk2.xxf86vm.XF86VidModeSwitchToMode)(display, screen, modeline);
}

Bool raw__xxf86vm__XF86VidModeSetViewPort(f2ptr cause, Display* display, int screen, int x, int y) {
  if (!__funk2.openglu.initialized) {status("*** WARNING: called xlib function without loading xxf86vm. ***"); return boolean__false;}
  return (*__funk2.xxf86vm.XF86VidModeSetViewPort)(display, screen, x, y);
}

Bool raw__xxf86vm__XF86VidModeQueryVersion(f2ptr cause, Display* display, int* major_version_return, int* minor_version_return) {
  if (!__funk2.openglu.initialized) {status("*** WARNING: called xlib function without loading xxf86vm. ***"); return boolean__false;}
  return (*__funk2.xxf86vm.XF86VidModeQueryVersion)(display, major_version_return, minor_version_return);
}

Bool raw__xxf86vm__XF86VidModeGetAllModeLines(f2ptr cause, Display* display, int screen, int* modecount_return, XF86VidModeModeInfo*** modesinfo) {
  if (!__funk2.openglu.initialized) {status("*** WARNING: called xlib function without loading xxf86vm. ***"); return boolean__false;}
  return (*__funk2.xxf86vm.XF86VidModeGetAllModeLines)(display, screen, modecount_return, modesinfo);
}
#endif // F2__XF86VMODE__H


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
  f2ptr filenames = raw__cons__new(cause, new__string(cause, "/usr/X11R6/lib/libX11.so"),  nil);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib/xorg/libX11.so"),   filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib64/libX11.so"),      filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib64/xorg/libX11.so"), filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/local/lib/libX11.so"),  filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/usr/lib/libX11.so"),        filenames);
  filenames       = raw__cons__new(cause, new__string(cause, "/lib/libX11.so"),            filenames);
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
  this->XDefaultScreen         = (int(*)(Display *display))                                           from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XDefaultScreen"));         if (! (this->XDefaultScreen))         {status("funk2_xlib__load_library: failed symbol, XDefaultScreen.");         return boolean__false;};
  this->XLoadQueryFont         = (XFontStruct*(*)(Display *display, char *name))                      from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XLoadQueryFont"));         if (! (this->XLoadQueryFont))         {status("funk2_xlib__load_library: failed symbol, XLoadQueryFont.");         return boolean__false;};
  this->XFreeFont              = (int(*)(Display *display, XFontStruct *font_struct))                 from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XFreeFont"));              if (! (this->XFreeFont))              {status("funk2_xlib__load_library: failed symbol, XFreeFont.");              return boolean__false;};
#endif // F2__XLIB__H
  status("funk2_xlib__load_library: loaded xlib function symbols successfully.");
  this->initialized = boolean__true;
  return boolean__true;
}

#if defined(F2__XLIB__H)
void raw__xlib__XCloseDisplay(f2ptr cause, Display* display) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return;}
  (*__funk2.xlib.XCloseDisplay)(display);
}

Display* raw__xlib__XOpenDisplay(f2ptr cause, char* display_name) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return NULL;}
  return (*__funk2.xlib.XOpenDisplay)(display_name);
}

Colormap raw__xlib__XCreateColormap(f2ptr cause, Display* display, Window w, Visual* visual, int alloc) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return (Colormap)0;}
  return (*__funk2.xlib.XCreateColormap)(display, w, visual, alloc);
}

int raw__xlib__XFree(f2ptr cause, void* data) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return 0;}
  return (*__funk2.xlib.XFree)(data);
}

Window raw__xlib__XCreateWindow(f2ptr cause, Display* display,
				Window parent,
				int x, int y,
				unsigned int width, unsigned int height,
				unsigned int border_width,
				int depth,
				unsigned int class,
				Visual* visual,
				unsigned long valuemask,
				XSetWindowAttributes* attributes) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return (Window)0;}
  return (*__funk2.xlib.XCreateWindow)(display,
				       parent,
				       x, y,
				       width, height,
				       border_width,
				       depth,
				       class,
				       visual,
				       valuemask,
				       attributes);
}

void raw__xlib__XWarpPointer(f2ptr cause, Display* display,
			     Window src_w, Window dest_w,
			     int src_x, int src_y,
			     unsigned int src_width, unsigned int src_height,
			     int dest_x, int dest_y) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return;}
  (*__funk2.xlib.XWarpPointer)(display,
			       src_w, dest_w,
			       src_x, src_y,
			       src_width, src_height,
			       dest_x, dest_y);
}

void raw__xlib__XMapRaised(f2ptr cause, Display* display, Window w) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return;}
  (*__funk2.xlib.XMapRaised)(display, w);
}

int raw__xlib__XGrabKeyboard(f2ptr cause, Display* display,
			     Window grab_window,
			     Bool owner_events,
			     int pointer_mode,
			     int keyboard_mode,
			     Time time) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return 0;}
  return (*__funk2.xlib.XGrabKeyboard)(display,
				       grab_window,
				       owner_events,
				       pointer_mode,
				       keyboard_mode,
				       time);
}

int raw__xlib__XGrabPointer(f2ptr cause, Display* display,
			    Window grab_window,
			    Bool owner_events,
			    unsigned int event_mask,
			    int pointer_mode,
			    int keyboard_mode,
			    Window confine_to,
			    Cursor cursor,
			    Time time) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return 0;}
  return (*__funk2.xlib.XGrabPointer)(display,
				      grab_window,
				      owner_events,
				      event_mask,
				      pointer_mode,
				      keyboard_mode,
				      confine_to,
				      cursor,
				      time);
}

Atom raw__xlib__XInternAtom(f2ptr cause, Display* display, char* atom_name, Bool only_if_exists) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return (Atom)0;}
  return (*__funk2.xlib.XInternAtom)(display, atom_name, only_if_exists);
}

Status raw__xlib__XSetWMProtocols(f2ptr cause, Display* display, Window w, Atom* protocols, int count) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return (Status)0;}
  return (*__funk2.xlib.XSetWMProtocols)(display, w, protocols, count);
}

void raw__xlib__XSetStandardProperties(f2ptr cause, Display* display,
				       Window w,
				       char* window_name,
				       char* icon_name,
				       Pixmap icon_pixmap,
				       char** argv, int argc,
				       XSizeHints *hints) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return;}
  (*__funk2.xlib.XSetStandardProperties)(display,
					 w,
					 window_name,
					 icon_name,
					 icon_pixmap,
					 argv, argc,
					 hints);
}

Status raw__xlib__XGetGeometry(f2ptr cause, Display* display,
			       Drawable d,
			       Window* root_return,
			       int* x_return,
			       int* y_return,
			       unsigned int* width_return,
			       unsigned int* height_return,
			       unsigned int* border_width_return,
			       unsigned int* depth_return) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return (Status)0;}
  return (*__funk2.xlib.XGetGeometry)(display,
				      d,
				      root_return,
				      x_return,
				      y_return,
				      width_return,
				      height_return,
				      border_width_return,
				      depth_return);
}

void raw__xlib__XNextEvent(f2ptr cause, Display* display, XEvent* event_return) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return;}
  (*__funk2.xlib.XNextEvent)(display, event_return);
}

KeySym raw__xlib__XLookupKeysym(f2ptr cause, XKeyEvent* key_event, int index) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return (KeySym)0;}
  return (*__funk2.xlib.XLookupKeysym)(key_event, index);
}

char* raw__xlib__XGetAtomName(f2ptr cause, Display* display, Atom atom) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return (char*)NULL;}
  return (*__funk2.xlib.XGetAtomName)(display, atom);
}

int raw__xlib__XPending(f2ptr cause, Display* display) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return 0;}
  return (*__funk2.xlib.XPending)(display);
}

int raw__xlib__XDefaultScreen(f2ptr cause, Display* display) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return 0;}
  return (*__funk2.xlib.XDefaultScreen)(display);
}

XFontStruct* raw__xlib__XLoadQueryFont(f2ptr cause, Display* display, char* name) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return 0;}
  return (*__funk2.xlib.XLoadQueryFont)(display, name);
}

//  this->XFreeFont              = (int(*)(Display *display, XFontStruct *font_struct))                 from_ptr(raw__dlfcn__dlsym(f2pointer__p(dlfcn_pointer, cause), (u8*)"XFreeFont"));              if (! (this->XFreeFont))              {status("funk2_xlib__load_library: failed symbol, XFreeFont.");              return boolean__false;};

int raw__xlib__XFreeFont(f2ptr cause, Display* display, XFontStruct* font_struct) {
  if (!__funk2.xlib.initialized) {status("*** WARNING: called xlib function without loading xlib. ***"); return 0;}
  return (*__funk2.xlib.XFreeFont)(display, font_struct);
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


