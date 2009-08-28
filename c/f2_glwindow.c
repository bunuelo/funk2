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

#if defined(F2__GLWINDOW__H)

// attributes for a single buffered visual in RGBA format with at least
// 4 bits per color and a 16 bit depth buffer
static int funk2_glwindow__attribute_list__single_buffer[] = {GLX_RGBA, GLX_RED_SIZE,  4, 
							      GLX_GREEN_SIZE,          4, 
							      GLX_BLUE_SIZE,           4, 
							      GLX_DEPTH_SIZE,         16,
							      None};

// attributes for a double buffered visual in RGBA format with at least
// 4 bits per color and a 16 bit depth buffer
static int funk2_glwindow__attribute_list__double_buffer[] = {GLX_RGBA, GLX_DOUBLEBUFFER, 
							      GLX_RED_SIZE,    4, 
							      GLX_GREEN_SIZE,  4, 
							      GLX_BLUE_SIZE,   4, 
							      GLX_DEPTH_SIZE, 16,
							      None};

static GLfloat funk2_glwindow__light1_ambient[]  = {0.1f, 0.1f,  0.1f, 1.0f}; 
static GLfloat funk2_glwindow__light1_diffuse[]  = {1.0f, 1.0f,  1.0f, 1.0f};
static GLfloat funk2_glwindow__light1_position[] = {0.0f, 0.0f, 10.0f, 1.0f};

// function called when our window is resized (should only happen in window mode)
void raw__resize_gl_scene(f2ptr cause, unsigned int width, unsigned int height) {
  if (height == 0) { // Prevent A Divide By Zero If The Window Is Too Small
    height = 1;
  }
  raw__opengl__glViewport(cause, 0, 0, width, height);    // Reset The Current Viewport And Perspective Transformation
  raw__opengl__glMatrixMode(cause, GL_PROJECTION);
  raw__opengl__glLoadIdentity(cause);
  raw__openglu__gluPerspective(cause, 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
  raw__opengl__glMatrixMode(cause, GL_MODELVIEW);
}

// general OpenGL initialization function
int glwindow__init(funk2_glwindow_t* this, f2ptr cause) {
  raw__opengl__glShadeModel(cause, GL_SMOOTH);
  raw__opengl__glClearColor(cause, 0.0f, 0.0f, 0.0f, 0.0f);
  raw__opengl__glClearDepth(cause, 1.0f);
  raw__opengl__glEnable(cause, GL_DEPTH_TEST);
  raw__opengl__glDepthFunc(cause, GL_LEQUAL);
  raw__opengl__glHint(cause, GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  
  raw__opengl__glLightfv(cause, GL_LIGHT1, GL_AMBIENT,  funk2_glwindow__light1_ambient);
  raw__opengl__glLightfv(cause, GL_LIGHT1, GL_DIFFUSE,  funk2_glwindow__light1_diffuse);
  raw__opengl__glLightfv(cause, GL_LIGHT1, GL_POSITION, funk2_glwindow__light1_position);
  raw__opengl__glEnable(cause, GL_LIGHT1);
  raw__opengl__glEnable(cause, GL_LIGHTING);
  
  raw__opengl__glCullFace(cause, GL_BACK);
  raw__opengl__glEnable(cause, GL_CULL_FACE);
  
  // we use raw__resize_gl_scene once to set up our initial perspective
  raw__resize_gl_scene(cause, this->width, this->height);
  raw__opengl__glFlush(cause);
  return True;
}

// Here goes our drawing code
int glwindow__draw_scene(funk2_glwindow_t* this, f2ptr cause, double rotate_angle) {
  raw__opengl__glClear(cause, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  raw__opengl__glLoadIdentity(cause);
  raw__opengl__glTranslatef(cause, 0, 0, -10);
  raw__opengl__glRotatef(cause, rotate_angle, 1,1,0.5);
  
  raw__opengl__glColor4f(cause, 1,1,1,1);
  raw__opengl__glBegin(cause, GL_QUADS);
  raw__opengl__glNormal3f(cause, 0,0,1);
  raw__opengl__glVertex3f(cause, -1,-1,1);
  raw__opengl__glVertex3f(cause,  1,-1,1);
  raw__opengl__glVertex3f(cause,  1, 1,1);
  raw__opengl__glVertex3f(cause, -1, 1,1);
  
  raw__opengl__glNormal3f(cause, 0,0,-1);
  raw__opengl__glVertex3f(cause, -1,-1,-1);
  raw__opengl__glVertex3f(cause, -1, 1,-1);
  raw__opengl__glVertex3f(cause,  1, 1,-1);
  raw__opengl__glVertex3f(cause,  1,-1,-1);
  
  raw__opengl__glNormal3f(cause, 0,1,0);
  raw__opengl__glVertex3f(cause, -1,1,-1);
  raw__opengl__glVertex3f(cause, -1,1, 1);
  raw__opengl__glVertex3f(cause,  1,1, 1);
  raw__opengl__glVertex3f(cause,  1,1,-1);
 
  raw__opengl__glNormal3f(cause, 0,-1,0);
  raw__opengl__glVertex3f(cause, -1,-1,-1);
  raw__opengl__glVertex3f(cause,  1,-1,-1);
  raw__opengl__glVertex3f(cause,  1,-1, 1);
  raw__opengl__glVertex3f(cause, -1,-1, 1);
  
  raw__opengl__glNormal3f(cause, 1,0,0);
  raw__opengl__glVertex3f(cause, 1,-1,-1);
  raw__opengl__glVertex3f(cause, 1, 1,-1);
  raw__opengl__glVertex3f(cause, 1, 1, 1);
  raw__opengl__glVertex3f(cause, 1,-1, 1);
  
  raw__opengl__glNormal3f(cause, -1,0,0);
  raw__opengl__glVertex3f(cause, -1,-1,-1);
  raw__opengl__glVertex3f(cause, -1,-1, 1);
  raw__opengl__glVertex3f(cause, -1, 1, 1);
  raw__opengl__glVertex3f(cause, -1, 1,-1);
  raw__opengl__glEnd(cause);
  
  if (this->double_buffered) {
    raw__opengl__glXSwapBuffers(cause, this->display, this->x_window);
  }
  return True;    
}

// function to release/destroy our resources and restoring the old desktop
GLvoid glwindow__destroy(funk2_glwindow_t* this, f2ptr cause) {
  if (this->glx_context) {
    if (!raw__opengl__glXMakeCurrent(cause, this->display, None, NULL)) {
      printf("Could not release drawing context.\n");
    }
    raw__opengl__glXDestroyContext(cause, this->display, this->glx_context);
    this->glx_context = NULL;
  }
  // switch back to original desktop resolution if we were in fs
  if (this->fullscreen) {
    raw__xxf86vm__XF86VidModeSwitchToMode(cause, this->display, this->screen, &(this->desk_mode));
    raw__xxf86vm__XF86VidModeSetViewPort(cause, this->display, this->screen, 0, 0);
  }
  raw__xlib__XCloseDisplay(cause, this->display);
}

int int__abs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

// this function creates our window and sets it up properly
// FIXME: bits is currently unused
boolean_t glwindow__create(funk2_glwindow_t* this, f2ptr cause, char* title, int width, int height, int bits, boolean_t fullscreenflag) {
  XVisualInfo *vi;
  Colormap cmap;
  int displayWidth, displayHeight;
  int i;
  int glxMajorVersion, glxMinorVersion;
  int vidModeMajorVersion, vidModeMinorVersion;
  XF86VidModeModeInfo **modes;
  int modeNum;
  int bestMode;
  Atom wmDelete;
  Window winDummy;
  unsigned int borderDummy;
  
  this->fullscreen = fullscreenflag;
  // set best mode to current
  bestMode = 0;
  // get a connection
  this->display = raw__xlib__XOpenDisplay(cause, 0);
  this->screen = DefaultScreen(this->display);
  raw__xxf86vm__XF86VidModeQueryVersion(cause, this->display, &vidModeMajorVersion,
					&vidModeMinorVersion);
  printf("XF86VidModeExtension-Version %d.%d\n", vidModeMajorVersion,
	 vidModeMinorVersion);
  raw__xxf86vm__XF86VidModeGetAllModeLines(cause, this->display, this->screen, &modeNum, &modes);
  // save desktop-resolution before switching modes
  this->desk_mode = *modes[0];
  // look for mode with closest resolution
  int min_dist = -1;
  for (i = 0; i < modeNum; i++) {
    int dist = int__abs(modes[i]->hdisplay - width) + int__abs(modes[i]->vdisplay - height);
    if ((min_dist == -1) || dist < min_dist) {
      min_dist = dist;
      bestMode = i;
    }
    printf("found mode %dx%d.%s\n", modes[i]->hdisplay, modes[i]->vdisplay, (bestMode == i) ? " <-- best mode so far!" : "");
  }
  // get an appropriate visual
  vi = raw__opengl__glXChooseVisual(cause, this->display, this->screen, funk2_glwindow__attribute_list__double_buffer);
  if (vi == NULL) {
    vi = raw__opengl__glXChooseVisual(cause, this->display, this->screen, funk2_glwindow__attribute_list__single_buffer);
    this->double_buffered = False;
    printf("single buffered visual!\n");
  } else {
    this->double_buffered = True;
    printf("double buffered visual!\n");
  }
  raw__opengl__glXQueryVersion(cause, this->display, &glxMajorVersion, &glxMinorVersion);
  printf("glX-Version %d.%d\n", glxMajorVersion, glxMinorVersion);
  // create a GLX context
  this->glx_context = raw__opengl__glXCreateContext(cause, this->display, vi, 0, GL_TRUE);
  // create a color map
  cmap = raw__xlib__XCreateColormap(cause, this->display, RootWindow(this->display, vi->screen),
				    vi->visual, AllocNone);
  this->set_window_attributes.colormap = cmap;
  this->set_window_attributes.border_pixel = 0;
  
  if (this->fullscreen) {
    raw__xxf86vm__XF86VidModeSwitchToMode(cause, this->display, this->screen, modes[bestMode]);
    raw__xxf86vm__XF86VidModeSetViewPort(cause, this->display, this->screen, 0, 0);
    displayWidth = modes[bestMode]->hdisplay;
    displayHeight = modes[bestMode]->vdisplay;
    printf("Resolution %dx%d\n", displayWidth, displayHeight);
    raw__xlib__XFree(cause, modes);
    
    // create a fullscreen window
    this->set_window_attributes.override_redirect = True;
    this->set_window_attributes.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
    this->x_window = raw__xlib__XCreateWindow(cause, this->display, RootWindow(this->display, vi->screen),
					      0, 0, displayWidth, displayHeight, 0, vi->depth, InputOutput, vi->visual,
					      CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect,
					      &this->set_window_attributes);
    raw__xlib__XWarpPointer(cause, this->display, None, this->x_window, 0, 0, 0, 0, 0, 0);
    raw__xlib__XMapRaised(cause, this->display, this->x_window);
    raw__xlib__XGrabKeyboard(cause, this->display, this->x_window, True, GrabModeAsync,
			     GrabModeAsync, CurrentTime);
    raw__xlib__XGrabPointer(cause, this->display, this->x_window, True, ButtonPressMask,
			    GrabModeAsync, GrabModeAsync, this->x_window, None, CurrentTime);
  } else {
    // create a window in window mode
    this->set_window_attributes.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
      StructureNotifyMask;
    this->x_window = raw__xlib__XCreateWindow(cause, this->display, RootWindow(this->display, vi->screen),
					      0, 0, width, height, 0, vi->depth, InputOutput, vi->visual,
					      CWBorderPixel | CWColormap | CWEventMask, &this->set_window_attributes);
    // only set window title and handle wm_delete_events if in windowed mode
    wmDelete = raw__xlib__XInternAtom(cause, this->display, "WM_DELETE_WINDOW", True);
    raw__xlib__XSetWMProtocols(cause, this->display, this->x_window, &wmDelete, 1);
    raw__xlib__XSetStandardProperties(cause, this->display, this->x_window, title,
				      title, None, NULL, 0, NULL);
    raw__xlib__XMapRaised(cause, this->display, this->x_window);
  }       
  // connect the glx-context to the window
  raw__opengl__glXMakeCurrent(cause, this->display, this->x_window, this->glx_context);
  raw__xlib__XGetGeometry(cause, this->display, this->x_window, &winDummy, &this->x, &this->y,
			  &this->width, &this->height, &borderDummy, &this->depth);
  printf("Depth %d\n", this->depth);
  if (raw__opengl__glXIsDirect(cause, this->display, this->glx_context)) {
    printf("Congrats, you have Direct Rendering!\n");
  } else {
    printf("Sorry, no Direct Rendering possible!\n");
  }
  glwindow__init(this, cause);
  return True;    
}

boolean_t glwindow__handle_events(funk2_glwindow_t* this, f2ptr cause, double rotate_angle) {
  XEvent event;
  while (raw__xlib__XPending(cause, this->display) > 0) {
    raw__xlib__XNextEvent(cause, this->display, &event);
    switch (event.type) {
    case Expose:
      if (event.xexpose.count != 0)
	break;
      glwindow__draw_scene(this, cause, rotate_angle);
      break;
    case ConfigureNotify:
      // call raw__resize_gl_scene only if our window-size changed
      if ((event.xconfigure.width != this->width) || 
	  (event.xconfigure.height != this->height)) {
	this->width = event.xconfigure.width;
	this->height = event.xconfigure.height;
	printf("Resize event: %dx%d\n", this->width, this->height);
	raw__resize_gl_scene(cause,
			     event.xconfigure.width,
			     event.xconfigure.height);
      }
      break;
      // exit in case of a mouse button press
    case ButtonPress:     
      this->done = True;
      break;
    case KeyPress:
      if (raw__xlib__XLookupKeysym(cause, &event.xkey, 0) == XK_Escape) {
	this->done = True;
      }
      if (raw__xlib__XLookupKeysym(cause, &event.xkey,0) == XK_F1) {
	glwindow__destroy(this, cause);
	this->fullscreen = !this->fullscreen;
	printf("creating new window: %dx%d\n", this->width, this->height);
	glwindow__create(this, cause, "NeHe's OpenGL Framework", this->width, this->height, this->depth, this->fullscreen);
      }
      break;
    case ClientMessage:
      if (*raw__xlib__XGetAtomName(cause, this->display, event.xclient.message_type) == *"WM_PROTOCOLS") {
	printf("Exiting sanely...\n");
	this->done = True;
      }
      break;
    default:
      break;
    }
  }
  return this->done;
}

int glwindow__main(f2ptr cause) {
  float rotate_angle = 0;
  
  // default to fullscreen
  boolean_t fullscreen = False;
  glwindow__create(&(__funk2.glwindow), cause, "NeHe's OpenGL Framework", 1024, 768, 24, fullscreen);
  
  __funk2.glwindow.done = boolean__false;
  // wait for events
  while (!__funk2.glwindow.done) {
    // handle the events in the queue
    glwindow__handle_events(&(__funk2.glwindow), cause, rotate_angle);
    if (! __funk2.glwindow.done) {
      glwindow__draw_scene(&(__funk2.glwindow), cause, rotate_angle);
      rotate_angle += 1;
      if (rotate_angle >= 360) {
	rotate_angle -= 360;
      }
    }
  }
  glwindow__destroy(&(__funk2.glwindow), cause);
}

#endif // F2__GLWINDOW__H

boolean_t raw__glwindow__supported(f2ptr cause) {
#if defined(F2__GLWINDOW__H)
  return boolean__true;
#else
  return boolean__false;
#endif  
}

f2ptr f2__glwindow__supported(f2ptr cause) {
  return f2bool__new(raw__glwindow__supported(cause));
}


void raw__glwindow__create(f2ptr cause, char* title, s64 width, s64 height, s64 depth, boolean_t fullscreen) {
#if defined(F2__GLWINDOW__H)
  glwindow__create(&(__funk2.glwindow), cause, title, width, height, depth, fullscreen);
#else
  status("\nglwindow not supported.");
  printf("\nglwindow not supported.");
#endif  
}

f2ptr f2__glwindow__create(f2ptr cause, f2ptr title, f2ptr width, f2ptr height, f2ptr depth, f2ptr fullscreen) {
  if ((! raw__string__is_type(cause, title)) ||
      (! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height)) ||
      (! raw__integer__is_type(cause, depth))) {
  }
  u64 title__length = f2string__length(title, cause);
  u8* title__str = (u8*)from_ptr(f2__malloc(title__length + 1));
  f2string__str_copy(title, cause, title__str);
  title__str[title__length] = (char)0;
  s64 width__i = f2integer__i(width, cause);
  s64 height__i = f2integer__i(height, cause);
  s64 depth__i = f2integer__i(height, cause);
  raw__glwindow__create(cause, title__str, width__i, height__i, depth__i, fullscreen ? boolean__true : boolean__false);
  f2__free(to_ptr(title__str));
  return nil;
}

