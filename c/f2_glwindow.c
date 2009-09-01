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

int int__abs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

#if defined(F2__GLWINDOW__SUPPORTED)

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

void funk2_glwindow__init(funk2_glwindow_t* this, u8* title, int width, int height, int depth, boolean_t fullscreen) {
  int title__length = strlen((char*)title);
  this->title = (u8*)from_ptr(f2__malloc(title__length + 1));
  strcpy((char*)(this->title), (char*)title);
  
  this->width          = width;
  this->height         = height;
  this->depth          = depth;
  this->fullscreen     = fullscreen;
  
  this->window_created = boolean__false;
  this->rotate_angle = 0;
  this->done = boolean__false;
  
  this->initialized = boolean__true;
}

void funk2_glwindow__reinit(funk2_glwindow_t* this, u8* title, int width, int height, int depth, boolean_t fullscreen) {
  funk2_glwindow__destroy(this);
  
  int title__length = strlen((char*)title);
  this->title = (u8*)from_ptr(f2__malloc(title__length + 1));
  strcpy((char*)(this->title), (char*)title);
  
  this->width          = width;
  this->height         = height;
  this->depth          = depth;
  this->fullscreen     = fullscreen;
  this->window_created = boolean__false;
  this->rotate_angle   = 0;
  this->done           = boolean__false;
  this->needs_redraw   = boolean__true;
  
  this->last_redraw__nanoseconds_since_1970 = 0;
  
  this->initialized = boolean__true;
}

void funk2_glwindow__destroy(funk2_glwindow_t* this) {
  if (this->initialized) {
    this->initialized = boolean__false;
    
    funk2_glwindow__hide(this, nil);
    f2__free(to_ptr(this->title));
  }
}

// function to release/destroy our resources and restoring the old desktop
void funk2_glwindow__hide(funk2_glwindow_t* this, f2ptr cause) {
  if (this->window_created) {
    this->window_created = boolean__false;
    if (this->glx_context) {
      if (! raw__opengl__glXMakeCurrent(cause, this->display, None, NULL)) {
        status("WARNING: could not release drawing context.");
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
}

// this function creates our window and sets it up properly
// FIXME: bits is currently unused
boolean_t funk2_glwindow__show(funk2_glwindow_t* this, f2ptr cause) {
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
  
  if (! raw__opengl__load_library(nil))  {return boolean__false;}
  if (! raw__openglu__load_library(nil)) {return boolean__false;}
  if (! raw__xxf86vm__load_library(nil)) {return boolean__false;}
  if (! raw__xlib__load_library(nil))    {return boolean__false;}
  
  // set best mode to current
  bestMode = 0;
  // get a connection
  this->display = raw__xlib__XOpenDisplay(cause, 0);
  if (! this->display) {
    status("could not open default display.  check DISPLAY environment variable.");
    return boolean__false;
  }
  this->screen = raw__xlib__XDefaultScreen(cause, this->display);
  raw__xxf86vm__XF86VidModeQueryVersion(cause, this->display, &vidModeMajorVersion,
					&vidModeMinorVersion);
  status("XF86VidModeExtension version %d.%d", vidModeMajorVersion,
	 vidModeMinorVersion);
  raw__xxf86vm__XF86VidModeGetAllModeLines(cause, this->display, this->screen, &modeNum, &modes);
  // save desktop-resolution before switching modes
  this->desk_mode = *modes[0];
  // look for mode with closest resolution
  int min_dist = -1;
  for (i = 0; i < modeNum; i++) {
    int dist = int__abs(modes[i]->hdisplay - this->width) + int__abs(modes[i]->vdisplay - this->height);
    if ((min_dist == -1) || dist < min_dist) {
      min_dist = dist;
      bestMode = i;
    }
    status("found mode %dx%d.%s", modes[i]->hdisplay, modes[i]->vdisplay, (bestMode == i) ? " <-- best mode so far!" : "");
  }
  // get an appropriate visual
  vi = raw__opengl__glXChooseVisual(cause, this->display, this->screen, funk2_glwindow__attribute_list__double_buffer);
  if (vi == NULL) {
    vi = raw__opengl__glXChooseVisual(cause, this->display, this->screen, funk2_glwindow__attribute_list__single_buffer);
    this->double_buffered = False;
    status("single buffered visual!");
  } else {
    this->double_buffered = True;
    status("double buffered visual!");
  }
  raw__opengl__glXQueryVersion(cause, this->display, &glxMajorVersion, &glxMinorVersion);
  status("glX version %d.%d", glxMajorVersion, glxMinorVersion);
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
    status("resolution %dx%d", displayWidth, displayHeight);
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
					      0, 0, this->width, this->height, 0, vi->depth, InputOutput, vi->visual,
					      CWBorderPixel | CWColormap | CWEventMask, &this->set_window_attributes);
    // only set window title and handle wm_delete_events if in windowed mode
    wmDelete = raw__xlib__XInternAtom(cause, this->display, "WM_DELETE_WINDOW", True);
    raw__xlib__XSetWMProtocols(cause, this->display, this->x_window, &wmDelete, 1);
    raw__xlib__XSetStandardProperties(cause, this->display, this->x_window, (char*)(this->title),
				      (char*)(this->title), None, NULL, 0, NULL);
    raw__xlib__XMapRaised(cause, this->display, this->x_window);
  }       
  // connect the glx-context to the window
  raw__opengl__glXMakeCurrent(cause, this->display, this->x_window, this->glx_context);
  raw__xlib__XGetGeometry(cause, this->display, this->x_window, &winDummy, &this->x, &this->y,
			  &this->width, &this->height, &borderDummy, &this->depth);
  status("depth %d", this->depth);
  if (raw__opengl__glXIsDirect(cause, this->display, this->glx_context)) {
    status("we have direct rendering");
  } else {
    status("we do not have direct rendering");
  }
  funk2_glwindow__initialize_opengl(this, cause);
  
  this->window_created = boolean__true;
  return True;
}

boolean_t funk2_glwindow__handle_events(funk2_glwindow_t* this, f2ptr cause) {
  if (this->window_created) {
    boolean_t draw_scene_constantly = boolean__true;
    if (draw_scene_constantly) {
      if ((raw__nanoseconds_since_1970() - this->last_redraw__nanoseconds_since_1970) >= ((1.0 / 10.0) * nanoseconds_per_second)) {
	this->needs_redraw = boolean__true;
      }
    }
    XEvent event;
    while (raw__xlib__XPending(cause, this->display) > 0) {
      raw__xlib__XNextEvent(cause, this->display, &event);
      switch (event.type) {
      case Expose:
	if (event.xexpose.count != 0)
	  break;
	this->needs_redraw = boolean__true;
	break;
      case ConfigureNotify:
	// call raw__resize_gl_scene only if our window-size changed
	if ((event.xconfigure.width != this->width) || 
	    (event.xconfigure.height != this->height)) {
	  this->width = event.xconfigure.width;
	  this->height = event.xconfigure.height;
	  status("resize event: %dx%d", this->width, this->height);
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
	  funk2_glwindow__hide(this, cause);
	  this->fullscreen = !this->fullscreen;
	  status("creating new window: %dx%d", this->width, this->height);
	  funk2_glwindow__show(this, cause);
	}
	break;
      case ClientMessage:
	if (*raw__xlib__XGetAtomName(cause, this->display, event.xclient.message_type) == *"WM_PROTOCOLS") {
	  status("Exiting sanely...");
	  this->done = True;
	}
	break;
      default:
	break;
      }
    }
    if (this->needs_redraw) {
      funk2_glwindow__draw_scene(this, cause);
      this->needs_redraw = boolean__false;
      this->last_redraw__nanoseconds_since_1970 = raw__nanoseconds_since_1970();
    }
  }
  return this->done;
}

// general OpenGL initialization function
int funk2_glwindow__initialize_opengl(funk2_glwindow_t* this, f2ptr cause) {
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

void raw__draw_gl_cube(f2ptr cause) {
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
}

void raw__gl_set_material_color(f2ptr cause, float red, float green, float blue, float alpha) {
  float mcolor[] = { red, green, blue, alpha };
  raw__opengl__glMaterialfv(cause, GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
}

// Here goes our drawing code
void funk2_glwindow__draw_scene(funk2_glwindow_t* this, f2ptr cause) {
  raw__opengl__glClear(cause, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  raw__opengl__glLoadIdentity(cause);
  
  f2ptr global_environment = funk2_memory__global_environment(&(__funk2.memory));
  f2ptr value = f2__environment__lookup_type_var_value(cause, global_environment, __funk2.primobject__frame.variable__symbol, new__symbol(cause, "glwindow_value"));
  if (value) {
    raw__opengl__glTranslatef(cause, 0, 0, -10);
    raw__opengl__glRotatef(cause, this->rotate_angle, 1,1,0.5);
    if (raw__larva__is_type(cause, value)) {
      raw__gl_set_material_color(cause, 1,0,0,1);
      raw__draw_gl_cube(cause);
    } else {
      raw__gl_set_material_color(cause, 1,1,1,1);
      raw__draw_gl_cube(cause);
    }
  }
  
  if (this->double_buffered) {
    raw__opengl__glXSwapBuffers(cause, this->display, this->x_window);
  }
}

void funk2_glwindow__main(f2ptr cause) {
  // default to fullscreen
  boolean_t fullscreen = False;
  funk2_glwindow__reinit(&(__funk2.glwindow), (u8*)"NeHe's OpenGL Framework", 1024, 768, 24, fullscreen);
  funk2_glwindow__show(&(__funk2.glwindow), cause);
  
  // wait for events
  while (! __funk2.glwindow.done) {
    // handle the events in the queue
    funk2_glwindow__handle_events(&(__funk2.glwindow), cause);
    if (! __funk2.glwindow.done) {
      funk2_glwindow__draw_scene(&(__funk2.glwindow), cause);
      __funk2.glwindow.rotate_angle += 1;
      if (__funk2.glwindow.rotate_angle >= 360) {
	__funk2.glwindow.rotate_angle -= 360;
      }
    }
  }
  funk2_glwindow__destroy(&(__funk2.glwindow));
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
def_pcfunk0(glwindow__supported, return f2__glwindow__supported(this_cause));

void raw__glwindow__create(f2ptr cause, u8* title, s64 width, s64 height, s64 depth, boolean_t fullscreen) {
#if defined(F2__GLWINDOW__H)
  funk2_glwindow__reinit(&(__funk2.glwindow), title, width, height, depth, fullscreen);
  funk2_glwindow__show(&(__funk2.glwindow), cause);
#else
  status("glwindow not supported.");
#endif
}

f2ptr f2__glwindow__create(f2ptr cause, f2ptr title, f2ptr width, f2ptr height, f2ptr depth, f2ptr fullscreen) {
  if ((! raw__string__is_type(cause, title)) ||
      (! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height)) ||
      (! raw__integer__is_type(cause, depth))) {
    return f2larva__new(cause, 1);
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
def_pcfunk5(glwindow__create, title, width, height, depth, fullscreen, return f2__glwindow__create(this_cause, title, width, height, depth, fullscreen));


boolean_t raw__glwindow__handle_events(f2ptr cause) {
  return funk2_glwindow__handle_events(&(__funk2.glwindow), cause);
}

f2ptr f2__glwindow__handle_events(f2ptr cause) {
  return f2bool__new(raw__glwindow__handle_events(cause));
}
def_pcfunk0(glwindow__handle_events, return f2__glwindow__handle_events(this_cause));


void raw__glwindow__destroy(f2ptr cause) {
  funk2_glwindow__destroy(&(__funk2.glwindow));
}

f2ptr f2__glwindow__destroy(f2ptr cause) {
  raw__glwindow__destroy(cause);
  return nil;
}
def_pcfunk0(glwindow__destroy, return f2__glwindow__destroy(this_cause));




// physical_object

def_primobject_2_slot(physical_object, position, rotation, size, );

f2ptr f2__physical_object__new(f2ptr cause, f2ptr position, f2ptr rotation, f2ptr size) {return f2physical_object__new(cause, position, rotation, size);}
def_pcfunk3(physical_object__new, position, rotation, size, return f2__bytecode_event__new(this_cause, position, rotation, size));



// **

void f2__glwindow__reinitialize_globalvars() {
}

void f2__glwindow__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "glwindow", "", &f2__glwindow__reinitialize_globalvars);
  
  f2__glwindow__reinitialize_globalvars();
  
  if (raw__glwindow__supported(nil)) {
    status("glwindow is supported in this funk2 build!");
  } else {
    status("glwindow is not supported in this funk2 build.");
  }
  
  f2__primcfunk__init__0(glwindow__supported, "glwindow cfunk declared in f2_glwindow.c");
  f2__primcfunk__init__5(glwindow__create, title, width, height, depth, fullscreen, "glwindow cfunk declared in f2_glwindow.c");
  f2__primcfunk__init__0(glwindow__handle_events, "glwindow cfunk declared in f2_glwindow.c");
  f2__primcfunk__init__0(glwindow__destroy, "glwindow cfunk declared in f2_glwindow.c");
  
  f2__primcfunk__init__3(physical_object__new, position, rotation, size, "glwindow cfunk declared in f2_glwindow.c");
}

