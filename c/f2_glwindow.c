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

// Much of the OpenGL code in this document was adapted from
// combinations of the NeHe GLX lessons.  NeHe is the best organized
// and largest OpenGL codebase that I've found over the last 15 years
// of programming OpenGL.  I start all of my OpenGL projects from
// their lessons, highly recommended.  -- Bo

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

boolean_t funk2_opengl_font__init(funk2_opengl_font_t* this, f2ptr cause, Display* display, char* font_name) {
  XFontStruct* font = raw__xlib__XLoadQueryFont(cause, display, font_name);
  if (font == NULL) {
    status("funk2_opengl_font__init: could not find any '%s' fonts.", font_name);
    return boolean__true;
  }
  this->base_display_list = raw__opengl__glGenLists(cause, 96);
  raw__opengl__glXUseXFont(cause, font->fid, 32, 96, this->base_display_list);
  raw__xlib__XFreeFont(cause, display, font);
  status("funk2_opengl_font__init: successfully loaded a '%s' font.", font_name);
  return boolean__false;
}

void funk2_opengl_font__destroy(funk2_opengl_font_t* this, f2ptr cause) {
  raw__opengl__glDeleteLists(cause, this->base_display_list, 96);
}

void funk2_opengl_font__printf(funk2_opengl_font_t* this, f2ptr cause, const char* fmt, ...) {
  va_list ap;
  char text[256];
  if (fmt == NULL) {
    return;
  }
  va_start(ap, fmt);
  vsnprintf(text, 256, fmt, ap);
  va_end(ap);
  text[256 - 1] = (char)0;
  raw__opengl__glPushAttrib(cause, GL_LIST_BIT);
  raw__opengl__glListBase(cause, this->base_display_list - 32);
  raw__opengl__glCallLists(cause, strlen(text), GL_UNSIGNED_BYTE, text);
  raw__opengl__glPopAttrib(cause);
}

// simple loader for 24-bit bitmaps (data is in rgb-format)
boolean_t funk2_texture_image__load_bmp(funk2_texture_image_t* texture, u8* filename) {
  FILE*              file;
  u16                bfType;
  s32                bfOffBits;
  s16                biPlanes;
  s16                biBitCount;
  s32                biSizeImage;
  
  texture->data = NULL;
  
  // make sure the file is there and open it read-only (binary)
  if ((file = fopen((char*)filename, "rb")) == NULL) {
    status("File not found : %s", (char*)filename);
    return boolean__true;
  }
  if(!fread(&bfType, sizeof(s16), 1, file)) {
    status("Error reading file!\n");
    return boolean__true;
  }
  // check if file is a bitmap
  if (bfType != 19778) {
    status("Not a Bitmap-File!\n");
    return boolean__true;
  }        
  // get the file size
  // skip file size and reserved fields of bitmap file header
  fseek(file, 8, SEEK_CUR);
  // get the position of the actual bitmap data
  if (!fread(&bfOffBits, sizeof(s32), 1, file)) {
    status("Error reading file!");
    return boolean__true;
  }
  status("Data at Offset: " s32__fstr, bfOffBits);
  // skip size of bitmap info header
  fseek(file, 4, SEEK_CUR);
  // get the width of the bitmap
  fread(&texture->width, sizeof(s32), 1, file);
  status("Width of Bitmap: %d", texture->width);
  // get the height of the bitmap
  fread(&texture->height, sizeof(s32), 1, file);
  status("Height of Bitmap: %d", texture->height);
  // get the number of planes (must be set to 1)
  fread(&biPlanes, sizeof(s16), 1, file);
  if (biPlanes != 1) {
    status("Error: number of Planes not 1!");
    return boolean__true;
  }
  // get the number of bits per pixel
  if (!fread(&biBitCount, sizeof(s16), 1, file)) {
    status("Error reading file!");
    return boolean__true;
  }
  status("bits per Pixel: %d", biBitCount);
  if ((biBitCount != 24) &&
      (biBitCount != 32)) {
    status("funk2_texture_image__load_bmp failure: we only support 24 or 32 bits per pixel!");
    return boolean__true;
  }
  // calculate the size of the image in bytes
  u64 image_pixel_num = texture->width * texture->height;
  biSizeImage = image_pixel_num * 4;
  status("Size of the image data: " s32__fstr, biSizeImage);
  texture->data = from_ptr(f2__malloc(biSizeImage));
  // seek to the actual data
  fseek(file, bfOffBits, SEEK_SET);
  if (biBitCount == 32) {
    if (! fread(texture->data, biSizeImage, 1, file)) {
      status("Error 32 bit argb data!");
      return boolean__true;
    }
    // swap red and blue (argb -> rgba)
    u64 pixel_index = 0;
    for (pixel_index = 0; pixel_index < image_pixel_num; pixel_index ++) {
      // from agrb
      u8 blue  = texture->data[(pixel_index << 2) + 0];
      u8 green = texture->data[(pixel_index << 2) + 1];
      u8 red   = texture->data[(pixel_index << 2) + 2];
      u8 alpha = texture->data[(pixel_index << 2) + 3];
      // to rgba
      texture->data[(pixel_index << 2) + 0] = red;
      texture->data[(pixel_index << 2) + 1] = green;
      texture->data[(pixel_index << 2) + 2] = blue;
      texture->data[(pixel_index << 2) + 3] = alpha;
    }
  } else if (biBitCount == 24) {
    u64 pixel_index = 0;
    while (pixel_index < image_pixel_num) {
      u8 bgr_pixel[3];
      if (! fread(bgr_pixel, 3, 1, file)) {
	status("Error loading 24 bit bgr data!");
	return boolean__true;
      }
      ((u8*)(texture->data))[(pixel_index << 2) + 0] = bgr_pixel[2];
      ((u8*)(texture->data))[(pixel_index << 2) + 1] = bgr_pixel[1];
      ((u8*)(texture->data))[(pixel_index << 2) + 2] = bgr_pixel[0];
      ((u8*)(texture->data))[(pixel_index << 2) + 3] = 0xFF;
      pixel_index ++;
    }
  }
  return boolean__false;
}

boolean_t funk2_opengl_texture__load_gl_texture_from_bmp(funk2_opengl_texture_t* this, f2ptr cause, u8* bmp_filename) {
  boolean_t              failure_status = boolean__false;
  funk2_texture_image_t* image;
  
  image = from_ptr(f2__malloc(sizeof(funk2_texture_image_t)));
  if (funk2_texture_image__load_bmp(image, bmp_filename)) {
    failure_status = boolean__true;
  }
  if (! failure_status) {
    {
      GLuint texture_id = 0;
      raw__opengl__glGenTextures(cause, 1, &texture_id);
      this->texture_id = texture_id;
    }
    this->width  = image->width;
    this->height = image->height;
    raw__opengl__glBindTexture(cause, GL_TEXTURE_2D, this->texture_id);
    raw__opengl__glTexParameteri(cause, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    raw__opengl__glTexParameteri(cause, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    raw__openglu__gluBuild2DMipmaps(cause, GL_TEXTURE_2D, 4, image->width, image->height, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
  }
  if (image) {
    if (image->data) {
      f2__free(to_ptr(image->data));
    }
    f2__free(to_ptr(image));
  }
  return failure_status;
}

void funk2_opengl_texture__bind(funk2_opengl_texture_t* this, f2ptr cause) {
  raw__opengl__glBindTexture(cause, GL_TEXTURE_2D, this->texture_id);
}

boolean_t funk2_glwindow__load_gl_textures(funk2_glwindow_t* this, f2ptr cause) {
  boolean_t failure_status = boolean__false;
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->texture),                             cause, (u8*)"data/texture.bmp");}  
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->bucket_object_texture),               cause, (u8*)"data/bucket_object.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->female_child_agent_sitting_texture),  cause, (u8*)"data/female_child_agent_sitting.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->female_child_agent_standing_texture), cause, (u8*)"data/female_child_agent_standing.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->fork_object_texture),                 cause, (u8*)"data/fork_object.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->male_child_agent_sitting_texture),    cause, (u8*)"data/male_child_agent_sitting.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->male_child_agent_standing_texture),   cause, (u8*)"data/male_child_agent_standing.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->mud_object_texture),                  cause, (u8*)"data/mud_object.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->mud_puddle_scene_texture),            cause, (u8*)"data/mud_puddle_scene.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->shovel_object_texture),               cause, (u8*)"data/shovel_object.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->spoon_object_texture),                cause, (u8*)"data/spoon_object.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->blue_left_shoe_texture),              cause, (u8*)"data/blue_left_shoe.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->blue_right_shoe_texture),             cause, (u8*)"data/blue_right_shoe.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->blue_shirt_texture),                  cause, (u8*)"data/blue_shirt.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->bluegreen_blouse_texture),            cause, (u8*)"data/bluegreen_blouse.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->orange_shorts_texture),               cause, (u8*)"data/orange_shorts.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->pink_left_shoe_texture),              cause, (u8*)"data/pink_left_shoe.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->pink_right_shoe_texture),             cause, (u8*)"data/pink_right_shoe.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->red_skirt_texture),                   cause, (u8*)"data/red_skirt.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->sideview_blue_shirt_texture),         cause, (u8*)"data/sideview_blue_shirt.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->sideview_bluegreen_blouse_texture),   cause, (u8*)"data/sideview_bluegreen_blouse.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->sideview_orange_shorts_texture),      cause, (u8*)"data/sideview_orange_shorts.bmp");}
  if (! failure_status) {failure_status |= funk2_opengl_texture__load_gl_texture_from_bmp(&(this->sideview_red_skirt_texture),          cause, (u8*)"data/sideview_red_skirt.bmp");}
  return failure_status;
}

// function called when our window is resized (should only happen in window mode)
void raw__resize_gl_scene(f2ptr cause, unsigned int width, unsigned int height) {
  if (height == 0) { // Prevent A Divide By Zero If The Window Is Too Small
    height = 1;
  }
  raw__opengl__glViewport(cause, 0, 0, width, height);    // Reset The Current Viewport And Perspective Transformation
  raw__opengl__glMatrixMode(cause, GL_PROJECTION);
  raw__opengl__glLoadIdentity(cause);
  raw__opengl__glScalef(cause, 1.0, (GLfloat)width / (GLfloat)height, 1.0);
  //raw__openglu__gluPerspective(cause, 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
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
  this->rotate_angle   = 0;
  this->done           = boolean__false;
  
  this->initialized    = boolean__true;
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
    
    funk2_opengl_font__destroy(&(this->fixed_font), nil);
    
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
//   FIXME: bits is currently unused
boolean_t funk2_glwindow__show(funk2_glwindow_t* this, f2ptr cause) {
  XVisualInfo* vi;
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
  
  if (! raw__opengl__load_library(nil))  {return boolean__true;}
  if (! raw__openglu__load_library(nil)) {return boolean__true;}
  if (! raw__xxf86vm__load_library(nil)) {return boolean__true;}
  if (! raw__xlib__load_library(nil))    {return boolean__true;}
  
  // set best mode to current
  bestMode = 0;
  // get a connection
  this->display = raw__xlib__XOpenDisplay(cause, 0);
  if (! this->display) {
    status("could not open default display.  check DISPLAY environment variable.");
    return boolean__true;
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
  if (funk2_glwindow__initialize_opengl(this, cause)) {
    return boolean__true;
  }
  
  this->window_created = boolean__true;
  return boolean__false;
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
boolean_t funk2_glwindow__initialize_opengl(funk2_glwindow_t* this, f2ptr cause) {
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
  
  raw__opengl__glBlendFunc(cause, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  raw__opengl__glEnable(cause, GL_BLEND);
  
  // we use raw__resize_gl_scene once to set up our initial perspective
  raw__resize_gl_scene(cause, this->width, this->height);
  
  if (funk2_glwindow__load_gl_textures(this, cause)) {
    status("funk2_glwindow__initialize_opengl failure: loading gl textures.");
    return boolean__true;
  }
  raw__opengl__glEnable(cause, GL_TEXTURE_2D);
  
  if (funk2_opengl_font__init(&(this->fixed_font), cause, this->display, "-*-times-bold-r-*-*-14-*-*-*-p-*-iso8859-1")) {
    if (funk2_opengl_font__init(&(this->fixed_font), cause, this->display, "-*-times-bold-r-*-*-12-*-*-*-p-*-iso8859-1")) {
      if (funk2_opengl_font__init(&(this->fixed_font), cause, this->display, "-*-helvetica-bold-r-normal--12-*-*-*-p-*-iso8859-1")) {
	if (funk2_opengl_font__init(&(this->fixed_font), cause, this->display, "fixed")) {
	  status("funk2_glwindow__initialize_opengl failure: could not find a font.");
	  return boolean__true;
	}
      }
    }
  }
  
  raw__opengl__glFlush(cause);
  return boolean__false;
}

funk2_opengl_texture_t* funk2_glwindow__lookup_texture(funk2_glwindow_t* this, f2ptr cause, f2ptr texture_name) {
  //printf("\n  funk2_glwindow__lookup_texture, texture_name="); f2__write(cause, nil, texture_name); fflush(stdout);
  if      (raw__symbol__eq(cause, texture_name, new__symbol(cause, "bucket_object")))               {return &(this->bucket_object_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "female_child_agent_sitting")))  {return &(this->female_child_agent_sitting_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "female_child_agent_standing"))) {return &(this->female_child_agent_standing_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "fork_object")))                 {return &(this->fork_object_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "male_child_agent_sitting")))    {return &(this->male_child_agent_sitting_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "male_child_agent_standing")))   {return &(this->male_child_agent_standing_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "mud_object")))                  {return &(this->mud_object_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "mud_puddle_scene")))            {return &(this->mud_puddle_scene_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "shovel_object")))               {return &(this->shovel_object_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "spoon_object")))                {return &(this->spoon_object_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "blue_left_shoe")))              {return &(this->blue_left_shoe_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "blue_right_shoe")))             {return &(this->blue_right_shoe_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "blue_shirt")))                  {return &(this->blue_shirt_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "bluegreen_blouse")))            {return &(this->bluegreen_blouse_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "orange_shorts")))               {return &(this->orange_shorts_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "pink_left_shoe")))              {return &(this->pink_left_shoe_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "pink_right_shoe")))             {return &(this->pink_right_shoe_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "red_skirt")))                   {return &(this->red_skirt_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "sideview_blue_shirt")))         {return &(this->sideview_blue_shirt_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "sideview_bluegreen_blouse")))   {return &(this->sideview_bluegreen_blouse_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "sideview_orange_shorts")))      {return &(this->sideview_orange_shorts_texture);}
  else if (raw__symbol__eq(cause, texture_name, new__symbol(cause, "sideview_red_skirt")))          {return &(this->sideview_red_skirt_texture);}
  else                                                                                              {return &(this->texture);}
}

void funk2_glwindow__bind_texture(funk2_glwindow_t* this, f2ptr cause, f2ptr texture_name) {
  funk2_opengl_texture_t* texture = funk2_glwindow__lookup_texture(this, cause, texture_name);
  //printf("\n  funk2_glwindow__bind_texture, texture_id=%d", texture->texture_id); fflush(stdout);
  funk2_opengl_texture__bind(texture, cause);
}

void raw__draw_gl_cube(f2ptr cause) {
  raw__opengl__glBegin(cause, GL_QUADS);
  raw__opengl__glNormal3f(cause, 0,0,1);
  raw__opengl__glTexCoord2f(cause, 0, 0);
  raw__opengl__glVertex3f(cause, -1,-1,1);
  raw__opengl__glTexCoord2f(cause, 1, 0);
  raw__opengl__glVertex3f(cause,  1,-1,1);
  raw__opengl__glTexCoord2f(cause, 1, 1);
  raw__opengl__glVertex3f(cause,  1, 1,1);
  raw__opengl__glTexCoord2f(cause, 0, 1);
  raw__opengl__glVertex3f(cause, -1, 1,1);
  
  raw__opengl__glNormal3f(cause, 0,0,-1);
  raw__opengl__glTexCoord2f(cause, 0, 0);
  raw__opengl__glVertex3f(cause, -1,-1,-1);
  raw__opengl__glTexCoord2f(cause, 1, 0);
  raw__opengl__glVertex3f(cause, -1, 1,-1);
  raw__opengl__glTexCoord2f(cause, 1, 1);
  raw__opengl__glVertex3f(cause,  1, 1,-1);
  raw__opengl__glTexCoord2f(cause, 0, 1);
  raw__opengl__glVertex3f(cause,  1,-1,-1);
  
  raw__opengl__glNormal3f(cause, 0,1,0);
  raw__opengl__glTexCoord2f(cause, 0, 0);
  raw__opengl__glVertex3f(cause, -1,1,-1);
  raw__opengl__glTexCoord2f(cause, 1, 0);
  raw__opengl__glVertex3f(cause, -1,1, 1);
  raw__opengl__glTexCoord2f(cause, 1, 1);
  raw__opengl__glVertex3f(cause,  1,1, 1);
  raw__opengl__glTexCoord2f(cause, 0, 1);
  raw__opengl__glVertex3f(cause,  1,1,-1);
 
  raw__opengl__glNormal3f(cause, 0,-1,0);
  raw__opengl__glTexCoord2f(cause, 0, 0);
  raw__opengl__glVertex3f(cause, -1,-1,-1);
  raw__opengl__glTexCoord2f(cause, 1, 0);
  raw__opengl__glVertex3f(cause,  1,-1,-1);
  raw__opengl__glTexCoord2f(cause, 1, 1);
  raw__opengl__glVertex3f(cause,  1,-1, 1);
  raw__opengl__glTexCoord2f(cause, 0, 1);
  raw__opengl__glVertex3f(cause, -1,-1, 1);
  
  raw__opengl__glNormal3f(cause, 1,0,0);
  raw__opengl__glTexCoord2f(cause, 0, 0);
  raw__opengl__glVertex3f(cause, 1,-1,-1);
  raw__opengl__glTexCoord2f(cause, 1, 0);
  raw__opengl__glVertex3f(cause, 1, 1,-1);
  raw__opengl__glTexCoord2f(cause, 1, 1);
  raw__opengl__glVertex3f(cause, 1, 1, 1);
  raw__opengl__glTexCoord2f(cause, 0, 1);
  raw__opengl__glVertex3f(cause, 1,-1, 1);
  
  raw__opengl__glNormal3f(cause, -1,0,0);
  raw__opengl__glTexCoord2f(cause, 0, 0);
  raw__opengl__glVertex3f(cause, -1,-1,-1);
  raw__opengl__glTexCoord2f(cause, 1, 0);
  raw__opengl__glVertex3f(cause, -1,-1, 1);
  raw__opengl__glTexCoord2f(cause, 1, 1);
  raw__opengl__glVertex3f(cause, -1, 1, 1);
  raw__opengl__glTexCoord2f(cause, 0, 1);
  raw__opengl__glVertex3f(cause, -1, 1,-1);
  raw__opengl__glEnd(cause);
}

void raw__draw_xy_square(f2ptr cause) {
  raw__opengl__glBegin(cause, GL_QUADS);
  raw__opengl__glNormal3f(cause, 0,0,1);
  raw__opengl__glTexCoord2f(cause, 0, 0);
  raw__opengl__glVertex3f(cause, -1,-1,1);
  raw__opengl__glTexCoord2f(cause, 1, 0);
  raw__opengl__glVertex3f(cause,  1,-1,1);
  raw__opengl__glTexCoord2f(cause, 1, 1);
  raw__opengl__glVertex3f(cause,  1, 1,1);
  raw__opengl__glTexCoord2f(cause, 0, 1);
  raw__opengl__glVertex3f(cause, -1, 1,1);
  raw__opengl__glEnd(cause);
}

void raw__gl_set_material_color(f2ptr cause, float red, float green, float blue, float alpha) {
  float mcolor[] = { red, green, blue, alpha };
  raw__opengl__glMaterialfv(cause, GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
}

void opengl__render_physical_position(f2ptr cause, f2ptr this) {
  f2ptr x = f2__physical_position__x(cause, this);
  f2ptr y = f2__physical_position__y(cause, this);
  f2ptr z = f2__physical_position__z(cause, this);
  double x__d = f2double__d(x, cause);
  double y__d = f2double__d(y, cause);
  double z__d = f2double__d(z, cause);
  raw__opengl__glTranslatef(cause, x__d, y__d, z__d);
}

void opengl__render_physical_rotation(f2ptr cause, f2ptr this) {
  f2ptr array = f2__physical_rotation__array(cause, this);
  GLfloat rot_matrix[16] =
    {1,0,0,0,
     0,1,0,0,
     0,0,1,0,
     0,0,0,1};
  int yi, xi;
  for (yi = 0; yi < 3; yi ++) {
    for (xi = 0; xi < 3; xi ++) {
      f2ptr elt = raw__array__elt(cause, array, ((yi << 1) + yi) + xi);
      double d = 0;
      if (raw__double__is_type(cause, elt)) {
	d = f2double__d(elt, cause);
      } else if (raw__integer__is_type(cause, elt)) {
	d = f2integer__i(elt, cause);
      } else {
	return;
      }
      rot_matrix[(yi << 2) + xi] = (GLfloat)d;
    }
  }
  raw__opengl__glMultMatrixf(cause, rot_matrix);
}

void opengl__render_physical_position_as_raster(f2ptr cause, f2ptr this) {
  f2ptr x = f2__physical_position__x(cause, this);
  f2ptr y = f2__physical_position__y(cause, this);
  f2ptr z = f2__physical_position__z(cause, this);
  double x__d = f2double__d(x, cause);
  double y__d = f2double__d(y, cause);
  double z__d = f2double__d(z, cause);
  raw__opengl__glRasterPos3f(cause, x__d, y__d, z__d);
}

GLfloat funk2_glwindow__get_render_font_width(funk2_glwindow_t* this, f2ptr cause, f2ptr text) {
  u64 text__length = f2string__length(text, cause);
  char* temp_str = alloca(text__length + 1);
  f2string__str_copy(text, cause, (u8*)temp_str);
  temp_str[text__length] = (char)0;
  
  raw__opengl__glDisable(cause, GL_TEXTURE_2D);
  
  raw__gl_set_material_color(cause, 1, 0, 0, 0);
  raw__opengl__glPushMatrix(cause);
  raw__opengl__glRasterPos3f(cause, 0, 0, 0);
  
  GLfloat start_raster_position[4];
  raw__opengl__glGetFloatv(cause, GL_CURRENT_RASTER_POSITION, start_raster_position);
  
  funk2_opengl_font__printf(&(this->fixed_font), cause, "%s", temp_str);
  raw__opengl__glPopMatrix(cause);
  
  GLfloat end_raster_position[4];
  raw__opengl__glGetFloatv(cause, GL_CURRENT_RASTER_POSITION, end_raster_position);
  
  return 2.0 * ((GLfloat)(end_raster_position[0] - start_raster_position[0]) / (GLfloat)(this->width));
}

void funk2_glwindow__render_outlined_font(funk2_glwindow_t* this, f2ptr cause, f2ptr text, double x, double y) {
  GLfloat raster_width = funk2_glwindow__get_render_font_width(this, cause, text);
  
  x -= (0.5 * raster_width);
  
  u64 text__length = f2string__length(text, cause);
  char* temp_str = alloca(text__length + 1);
  f2string__str_copy(text, cause, (u8*)temp_str);
  temp_str[text__length] = (char)0;
  
  raw__opengl__glDisable(cause, GL_TEXTURE_2D);
  
  raw__gl_set_material_color(cause, 1, 1, 1, 1);
  raw__opengl__glPushMatrix(cause);
  raw__opengl__glRasterPos3f(cause, x - (2.0 / (GLfloat)(this->width)), y, 0);
  funk2_opengl_font__printf(&(this->fixed_font), cause, "%s", temp_str);
  raw__opengl__glPopMatrix(cause);
  
  raw__gl_set_material_color(cause, 1, 1, 1, 1);
  raw__opengl__glPushMatrix(cause);
  raw__opengl__glRasterPos3f(cause, x + (2.0 / (GLfloat)(this->width)), y, 0);
  funk2_opengl_font__printf(&(this->fixed_font), cause, "%s", temp_str);
  raw__opengl__glPopMatrix(cause);
  
  raw__gl_set_material_color(cause, 1, 1, 1, 1);
  raw__opengl__glPushMatrix(cause);
  raw__opengl__glRasterPos3f(cause, x, y - (2.0 / (GLfloat)(this->width)), 0);
  funk2_opengl_font__printf(&(this->fixed_font), cause, "%s", temp_str);
  raw__opengl__glPopMatrix(cause);
  
  raw__gl_set_material_color(cause, 1, 1, 1, 1);
  raw__opengl__glPushMatrix(cause);
  raw__opengl__glRasterPos3f(cause, x, y + (2.0 / (GLfloat)(this->width)), 0);
  funk2_opengl_font__printf(&(this->fixed_font), cause, "%s", temp_str);
  raw__opengl__glPopMatrix(cause);
  
  raw__gl_set_material_color(cause, 0, 0, 0, 1);
  raw__opengl__glPushMatrix(cause);
  raw__opengl__glRasterPos3f(cause, x, y, 0);
  funk2_opengl_font__printf(&(this->fixed_font), cause, "%s", temp_str);
  raw__opengl__glPopMatrix(cause);
}


void funk2_glwindow__render_relative_physical_object(funk2_glwindow_t* this, f2ptr cause, f2ptr relative_object, f2ptr physical_object) {
  f2ptr relative_position = nil;
  f2ptr relative_size     = nil;
  if (relative_object) {
    relative_position = f2__physical_object__position(cause, relative_object);
    relative_size     = f2__physical_object__size(    cause, relative_object);
  }
  f2ptr position     = f2__physical_object__position(    cause, physical_object);
  f2ptr rotation     = f2__physical_object__rotation(    cause, physical_object);
  f2ptr text         = f2__physical_object__text(        cause, physical_object);
  f2ptr texture_name = f2__physical_object__texture_name(cause, physical_object);
  f2ptr size         = f2__physical_object__size(        cause, physical_object);
  
  f2ptr position__x = f2__physical_position__x(cause, position);
  f2ptr position__y = f2__physical_position__y(cause, position);
  double position__x__d = f2double__d(position__x, cause);
  double position__y__d = f2double__d(position__y, cause);
  
  double size__d = 1.0;
  if (raw__double__is_type(cause, size)) {
    size__d = f2double__d(size, cause);
  } else if (raw__integer__is_type(cause, size)) {
    size__d = (double)f2integer__i(size, cause);
  }
  
  raw__opengl__glEnable(cause, GL_TEXTURE_2D);
  
  raw__gl_set_material_color(cause, 1, 1, 1, 1);
  
  raw__opengl__glPushMatrix(cause);
  funk2_opengl_texture_t* texture = funk2_glwindow__lookup_texture(this, cause, texture_name);
  double height_over_width = ((double)(texture->height) / (double)(texture->width));
  funk2_opengl_texture__bind(texture, cause);
  
  if (relative_position) {
    f2ptr relative_position__x = f2__physical_position__x(cause, relative_position);
    f2ptr relative_position__y = f2__physical_position__y(cause, relative_position);
    double relative_position__x__d = f2double__d(relative_position__x, cause);
    double relative_position__y__d = f2double__d(relative_position__y, cause);
    raw__opengl__glTranslatef(cause, relative_position__x__d, relative_position__y__d, 0);
  }
  
  if (relative_size) {
    double relative_size__d = 1.0;
    if (raw__double__is_type(cause, relative_size)) {
      relative_size__d = f2double__d(relative_size, cause);
    } else if (raw__integer__is_type(cause, relative_size)) {
      relative_size__d = (double)f2integer__i(relative_size, cause);
    }
    raw__opengl__glScalef(cause, 1.0 * relative_size__d, 1.0 * relative_size__d, 1);
  }
  
  raw__opengl__glTranslatef(cause, position__x__d, position__y__d + (size__d * height_over_width), 0);
  if (raw__physical_rotation__is_type(cause, rotation)) {
    opengl__render_physical_rotation(cause, rotation);
  }
  raw__opengl__glScalef(cause, 1.0 * size__d, 1.0 * size__d * height_over_width, 1);
  raw__draw_xy_square(cause);
  raw__opengl__glPopMatrix(cause);
  
  if (raw__string__is_type(cause, text)) {
    GLfloat font_size = 12.0;
    funk2_glwindow__render_outlined_font(this, cause, text, position__x__d, position__y__d - (2.0 * (font_size / (GLfloat)(this->width))));
  }
}

void funk2_glwindow__render_physical_object(funk2_glwindow_t* this, f2ptr cause, f2ptr physical_object) {
  funk2_glwindow__render_relative_physical_object(this, cause, nil, physical_object);
}

void funk2_glwindow__render_background(funk2_glwindow_t* this, f2ptr cause, f2ptr background_texture_name) {
  raw__opengl__glEnable(cause, GL_TEXTURE_2D);
  
  raw__opengl__glPushMatrix(cause);
  funk2_opengl_texture_t* background_texture = funk2_glwindow__lookup_texture(this, cause, background_texture_name);
  double height_over_width = ((double)(background_texture->height) / (double)(background_texture->width));
  funk2_opengl_texture__bind(background_texture, cause);
  raw__opengl__glScalef(cause, 1, 1 * height_over_width, 1);
  raw__draw_xy_square(cause);
  raw__opengl__glPopMatrix(cause);
}

void funk2_glwindow__render_physical_scene(funk2_glwindow_t* this, f2ptr cause, f2ptr physical_scene) {
  
  raw__opengl__glDisable(cause, GL_DEPTH_TEST);
  
  f2ptr background_texture = f2__physical_scene__background_texture(cause, physical_scene);
  funk2_glwindow__render_background(this, cause, background_texture);
  
  f2ptr physical_things     = f2__physical_scene__physical_things(cause, physical_scene);
  f2ptr physical_thing_iter = physical_things;
  while (physical_thing_iter) {
    {
      f2ptr physical_thing = f2__cons__car(cause, physical_thing_iter);
      if (raw__physical_object__is_type(cause, physical_thing)) {
	f2ptr physical_object = physical_thing;
	funk2_glwindow__render_physical_object(this, cause, physical_object);
      } else if (raw__physical_person__is_type(cause, physical_thing)) {
	f2ptr physical_person = physical_thing;
	f2ptr body = f2__physical_person__body(cause, physical_person);
	if (raw__physical_object__is_type(cause, body)) {
	  funk2_glwindow__render_physical_object(this, cause, body);
	  f2ptr torso_clothing      = f2__physical_person__torso_clothing(     cause, physical_person);
	  f2ptr leg_clothing        = f2__physical_person__leg_clothing(       cause, physical_person);
	  f2ptr left_foot_clothing  = f2__physical_person__left_foot_clothing( cause, physical_person);
	  f2ptr right_foot_clothing = f2__physical_person__right_foot_clothing(cause, physical_person);
	  f2ptr left_hand_object    = f2__physical_person__left_hand_object(   cause, physical_person);
	  f2ptr right_hand_object   = f2__physical_person__right_hand_object(  cause, physical_person);
	  if (raw__physical_object__is_type(cause, torso_clothing))      {funk2_glwindow__render_relative_physical_object(this, cause, body, torso_clothing);}
	  if (raw__physical_object__is_type(cause, leg_clothing))        {funk2_glwindow__render_relative_physical_object(this, cause, body, leg_clothing);}
	  if (raw__physical_object__is_type(cause, left_foot_clothing))  {funk2_glwindow__render_relative_physical_object(this, cause, body, left_foot_clothing);}
	  if (raw__physical_object__is_type(cause, right_foot_clothing)) {funk2_glwindow__render_relative_physical_object(this, cause, body, right_foot_clothing);}
	  if (raw__physical_object__is_type(cause, left_hand_object))    {funk2_glwindow__render_relative_physical_object(this, cause, body, left_hand_object);}
	  if (raw__physical_object__is_type(cause, right_hand_object))   {funk2_glwindow__render_relative_physical_object(this, cause, body, right_hand_object);}
	}
      }
    }
    physical_thing_iter = f2__cons__cdr(cause, physical_thing_iter);
  }
  
  raw__opengl__glEnable(cause, GL_DEPTH_TEST);
  
}

// here goes our main scene drawing code
void funk2_glwindow__draw_scene(funk2_glwindow_t* this, f2ptr cause) {
  raw__opengl__glClear(cause, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  raw__opengl__glLoadIdentity(cause);
  
  f2ptr global_environment = funk2_memory__global_environment(&(__funk2.memory));
  f2ptr value = f2__environment__lookup_type_var_value(cause, global_environment, __funk2.primobject__frame.variable__symbol, new__symbol(cause, "glwindow_value"));
  if (value) {
    //raw__opengl__glTranslatef(cause, 0, 0, -20);
    raw__opengl__glRotatef(cause, this->rotate_angle, 1,1,0.5);
    if (raw__physical_scene__is_type(cause, value)) {
      f2ptr physical_scene = value;
      raw__gl_set_material_color(cause, 1,1,1,1);
      funk2_glwindow__render_physical_scene(this, cause, physical_scene);
    } else if (raw__larva__is_type(cause, value)) {
      raw__gl_set_material_color(cause, 1,0,0,1);
      raw__draw_gl_cube(cause);
    } else {
      raw__gl_set_material_color(cause, 1,0,1,1);
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
  f2string__str_copy(title, cause, (u8*)title__str);
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





// **

void f2__glwindow__reinitialize_globalvars() {
  //f2ptr cause = initial_cause();
  
}

void f2__glwindow__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "glwindow", "", &f2__glwindow__reinitialize_globalvars);
  
  f2__glwindow__reinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  if (raw__glwindow__supported(cause)) {
    status("glwindow is supported in this funk2 build!");
  } else {
    status("glwindow is not supported in this funk2 build.");
  }
  
  f2__primcfunk__init__0(glwindow__supported, "glwindow cfunk declared in f2_glwindow.c");
  f2__primcfunk__init__5(glwindow__create, title, width, height, depth, fullscreen, "glwindow cfunk declared in f2_glwindow.c");
  f2__primcfunk__init__0(glwindow__handle_events, "glwindow cfunk declared in f2_glwindow.c");
  f2__primcfunk__init__0(glwindow__destroy, "glwindow cfunk declared in f2_glwindow.c");
}

