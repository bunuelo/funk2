#include <funk2.h>

#if defined(F2__GLWINDOW__H)

// attributes for a single buffered visual in RGBA format with at least
// 4 bits per color and a 16 bit depth buffer
static int funk2_glwindow__attribute_list__single_buffer[] = {GLX_RGBA, GLX_RED_SIZE, 4, 
							      GLX_GREEN_SIZE, 4, 
							      GLX_BLUE_SIZE, 4, 
							      GLX_DEPTH_SIZE, 16,
							      None};

// attributes for a double buffered visual in RGBA format with at least
// 4 bits per color and a 16 bit depth buffer
static int funk2_glwindow__attribute_list__double_buffer[] = {GLX_RGBA, GLX_DOUBLEBUFFER, 
							      GLX_RED_SIZE, 4, 
							      GLX_GREEN_SIZE, 4, 
							      GLX_BLUE_SIZE, 4, 
							      GLX_DEPTH_SIZE, 16,
							      None};

static GLfloat funk2_glwindow__light1_ambient[]  = {0.1f, 0.1f,  0.1f, 1.0f}; 
static GLfloat funk2_glwindow__light1_diffuse[]  = {1.0f, 1.0f,  1.0f, 1.0f};
static GLfloat funk2_glwindow__light1_position[] = {0.0f, 0.0f, 10.0f, 1.0f};

// function called when our window is resized (should only happen in window mode)
void resize_gl_scene(unsigned int width, unsigned int height) {
  if (height == 0) {    // Prevent A Divide By Zero If The Window Is Too Small
    height = 1;
  }
  glViewport(0, 0, width, height);    // Reset The Current Viewport And Perspective Transformation
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

// general OpenGL initialization function
int glwindow__init(funk2_glwindow_t* this) {
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  
  glLightfv(GL_LIGHT1, GL_AMBIENT,  funk2_glwindow__light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  funk2_glwindow__light1_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, funk2_glwindow__light1_position);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);
  
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  
  // we use resize_gl_scene once to set up our initial perspective
  resize_gl_scene(this->width, this->height);
  glFlush();
  return True;
}

// Here goes our drawing code
int glwindow__draw_scene(funk2_glwindow_t* this, double rotate_angle) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0, 0, -10);
  glRotatef(rotate_angle, 1,1,0.5);
  
  glColor4f(1,1,1,1);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glVertex3f(-1,-1,1);
  glVertex3f( 1,-1,1);
  glVertex3f( 1, 1,1);
  glVertex3f(-1, 1,1);
  
  glNormal3f(0,0,-1);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1, 1,-1);
  glVertex3f( 1, 1,-1);
  glVertex3f( 1,-1,-1);
  
  glNormal3f(0,1,0);
  glVertex3f(-1,1,-1);
  glVertex3f(-1,1, 1);
  glVertex3f( 1,1, 1);
  glVertex3f( 1,1,-1);
 
  glNormal3f(0,-1,0);
  glVertex3f(-1,-1,-1);
  glVertex3f( 1,-1,-1);
  glVertex3f( 1,-1, 1);
  glVertex3f(-1,-1, 1);
  
  glNormal3f(1,0,0);
  glVertex3f(1,-1,-1);
  glVertex3f(1, 1,-1);
  glVertex3f(1, 1, 1);
  glVertex3f(1,-1, 1);
  
  glNormal3f(-1,0,0);
  glVertex3f(-1,-1,-1);
  glVertex3f(-1,-1, 1);
  glVertex3f(-1, 1, 1);
  glVertex3f(-1, 1,-1);
  glEnd();
  
  if (this->double_buffered) {
    glXSwapBuffers(this->display, this->x_window);
  }
  return True;    
}

// function to release/destroy our resources and restoring the old desktop
GLvoid glwindow__destroy(funk2_glwindow_t* this) {
  if (this->glx_context) {
    if (!glXMakeCurrent(this->display, None, NULL)) {
      printf("Could not release drawing context.\n");
    }
    glXDestroyContext(this->display, this->glx_context);
    this->glx_context = NULL;
  }
  // switch back to original desktop resolution if we were in fs
  if (this->fullscreen) {
    XF86VidModeSwitchToMode(this->display, this->screen, &(this->desk_mode));
    XF86VidModeSetViewPort(this->display, this->screen, 0, 0);
  }
  XCloseDisplay(this->display);
}

int int__abs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

// this function creates our window and sets it up properly
// FIXME: bits is currently unused
Bool glwindow__create(funk2_glwindow_t* this, char* title, int width, int height, int bits, Bool fullscreenflag) {
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
  this->display = XOpenDisplay(0);
  this->screen = DefaultScreen(this->display);
  XF86VidModeQueryVersion(this->display, &vidModeMajorVersion,
			  &vidModeMinorVersion);
  printf("XF86VidModeExtension-Version %d.%d\n", vidModeMajorVersion,
	 vidModeMinorVersion);
  XF86VidModeGetAllModeLines(this->display, this->screen, &modeNum, &modes);
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
  vi = glXChooseVisual(this->display, this->screen, funk2_glwindow__attribute_list__double_buffer);
  if (vi == NULL) {
    vi = glXChooseVisual(this->display, this->screen, funk2_glwindow__attribute_list__single_buffer);
    this->double_buffered = False;
    printf("single buffered visual!\n");
  } else {
    this->double_buffered = True;
    printf("double buffered visual!\n");
  }
  glXQueryVersion(this->display, &glxMajorVersion, &glxMinorVersion);
  printf("glX-Version %d.%d\n", glxMajorVersion, glxMinorVersion);
  // create a GLX context
  this->glx_context = glXCreateContext(this->display, vi, 0, GL_TRUE);
  // create a color map
  cmap = XCreateColormap(this->display, RootWindow(this->display, vi->screen),
			 vi->visual, AllocNone);
  this->set_window_attributes.colormap = cmap;
  this->set_window_attributes.border_pixel = 0;
  
  if (this->fullscreen) {
    XF86VidModeSwitchToMode(this->display, this->screen, modes[bestMode]);
    XF86VidModeSetViewPort(this->display, this->screen, 0, 0);
    displayWidth = modes[bestMode]->hdisplay;
    displayHeight = modes[bestMode]->vdisplay;
    printf("Resolution %dx%d\n", displayWidth, displayHeight);
    XFree(modes);
    
    // create a fullscreen window
    this->set_window_attributes.override_redirect = True;
    this->set_window_attributes.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
    this->x_window = XCreateWindow(this->display, RootWindow(this->display, vi->screen),
				   0, 0, displayWidth, displayHeight, 0, vi->depth, InputOutput, vi->visual,
				   CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect,
				   &this->set_window_attributes);
    XWarpPointer(this->display, None, this->x_window, 0, 0, 0, 0, 0, 0);
    XMapRaised(this->display, this->x_window);
    XGrabKeyboard(this->display, this->x_window, True, GrabModeAsync,
		  GrabModeAsync, CurrentTime);
    XGrabPointer(this->display, this->x_window, True, ButtonPressMask,
		 GrabModeAsync, GrabModeAsync, this->x_window, None, CurrentTime);
  } else {
    // create a window in window mode
    this->set_window_attributes.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
      StructureNotifyMask;
    this->x_window = XCreateWindow(this->display, RootWindow(this->display, vi->screen),
				   0, 0, width, height, 0, vi->depth, InputOutput, vi->visual,
				   CWBorderPixel | CWColormap | CWEventMask, &this->set_window_attributes);
    // only set window title and handle wm_delete_events if in windowed mode
    wmDelete = XInternAtom(this->display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(this->display, this->x_window, &wmDelete, 1);
    XSetStandardProperties(this->display, this->x_window, title,
			   title, None, NULL, 0, NULL);
    XMapRaised(this->display, this->x_window);
  }       
  // connect the glx-context to the window
  glXMakeCurrent(this->display, this->x_window, this->glx_context);
  XGetGeometry(this->display, this->x_window, &winDummy, &this->x, &this->y,
	       &this->width, &this->height, &borderDummy, &this->depth);
  printf("Depth %d\n", this->depth);
  if (glXIsDirect(this->display, this->glx_context)) {
    printf("Congrats, you have Direct Rendering!\n");
  } else {
    printf("Sorry, no Direct Rendering possible!\n");
  }
  glwindow__init(this);
  return True;    
}

Bool glwindow__handle_events(funk2_glwindow_t* this, double rotate_angle) {
  Bool done = False;
  XEvent event;
  while (XPending(this->display) > 0) {
    XNextEvent(this->display, &event);
    switch (event.type) {
    case Expose:
      if (event.xexpose.count != 0)
	break;
      glwindow__draw_scene(this, rotate_angle);
      break;
    case ConfigureNotify:
      // call resize_gl_scene only if our window-size changed
      if ((event.xconfigure.width != this->width) || 
	  (event.xconfigure.height != this->height)) {
	this->width = event.xconfigure.width;
	this->height = event.xconfigure.height;
	printf("Resize event: %dx%d\n", this->width, this->height);
	resize_gl_scene(event.xconfigure.width,
			event.xconfigure.height);
      }
      break;
      // exit in case of a mouse button press
    case ButtonPress:     
      done = True;
      break;
    case KeyPress:
      if (XLookupKeysym(&event.xkey, 0) == XK_Escape) {
	done = True;
      }
      if (XLookupKeysym(&event.xkey,0) == XK_F1) {
	glwindow__destroy(this);
	this->fullscreen = !this->fullscreen;
	printf("creating new window: %dx%d\n", this->width, this->height);
	glwindow__create(this, "NeHe's OpenGL Framework", this->width, this->height, this->depth, this->fullscreen);
      }
      break;
    case ClientMessage:
      if (*XGetAtomName(this->display, event.xclient.message_type) == *"WM_PROTOCOLS") {
	printf("Exiting sanely...\n");
	done = True;
      }
      break;
    default:
      break;
    }
  }
  return done;
}

int main(int argc, char **argv) {
  float rotate_angle = 0;
  funk2_glwindow_t glwindow;
  
  // default to fullscreen
  Bool fullscreen = False;
  glwindow__create(&glwindow, "NeHe's OpenGL Framework", 1024, 768, 24, fullscreen);
  
  Bool done = False;
  // wait for events
  while (!done) {
    // handle the events in the queue
    done = glwindow__handle_events(&glwindow, rotate_angle);
    if (! done) {
      glwindow__draw_scene(&glwindow, rotate_angle);
      rotate_angle += 1;
      if (rotate_angle >= 360) {
	rotate_angle -= 360;
      }
    }
  }
  glwindow__destroy(&glwindow);
  exit (0);
}

#endif // F2__GLWINDOW__H
