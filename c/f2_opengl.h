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

typedef struct funk2_opengl_s funk2_opengl_t;

#include "f2_primfunks.h"

typedef int    GLint;
typedef int    GLenum;
typedef int    GLsizei;
typedef double GLdouble;
typedef float  GLclampf;
typedef double GLclampd;
typedef int    GLbitfield;


struct funk2_opengl_s {
  boolean_t initialized;
  f2ptr     dlfcn_pointer;
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
};

struct funk2_openglu_s {
  boolean_t initialized;
  f2ptr     dlfcn_pointer;
  void(*    gluPerspective)(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
};

void funk2_opengl__init(funk2_opengl_t* this);
void funk2_opengl__destroy(funk2_opengl_t* this);

boolean_t raw__opengl__load_library(f2ptr cause);

void funk2_openglu__init(funk2_opengl_t* this);
void funk2_openglu__destroy(funk2_opengl_t* this);

boolean_t raw__openglu__load_library(f2ptr cause);

#endif // F2__OPENGL__H


