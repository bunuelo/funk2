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

#ifndef F2__SYSTEM_HEADERS__H
#define F2__SYSTEM_HEADERS__H

#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif

#include "f2_archconfig.h"

#ifdef F2__APPLE
#  define MAP_ANONYMOUS MAP_ANON
// see: http://www.osxfaq.com/man/4/tty.ws
#  define SIOCOUTQ TIOCOUTQ
#  define SIOCINQ  TIOCSTI

#  include <mach/mach.h>
#  include <mach/clock.h>
#  include <mach/mach_time.h>
#  include <sys/resource.h>
#  include <sys/sockio.h>
#endif // F2__APPLE

#if defined(HAVE_LINUX_SOCKIOS_H)
#  include <linux/sockios.h>
#endif

#if defined(F2__XMLRPC_SUPPORTED)
#  ifndef _XOPEN_SOURCE
#    define _XOPEN_SOURCE 600
#  endif
#  include <xmlrpc-c/base.h>
#  include <xmlrpc-c/abyss.h>
#  include <xmlrpc-c/client.h>
#  include <xmlrpc-c/server.h>
#  include <xmlrpc-c/server_abyss.h>
#endif

#include <assert.h>
#include <arpa/inet.h>
#include <dirent.h>
#ifdef F2__DLFCN__SUPPORTED
#  include <dlfcn.h>
#endif
#include <errno.h>
#include <fcntl.h>
#ifdef F2__GMODULE__SUPPORTED
#  include <gmodule.h>
#endif
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdarg.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#if defined(HAVE_ZLIB_H)
#  include "zlib.h"
#else
#  error Funk2 requires zlib for compressing and decompressing otherwise very large disk images.
#endif

#if defined(HAVE_GL_GL_H)
#  define  F2__GL__H
#  include <GL/gl.h>
#elif defined(HAVE_OPENGL_GL_H)
#  define  F2__GL__H
#  include <OpenGL/gl.h>
#endif

#if defined(HAVE_GL_GLX_H)
#  define  F2__GLX__H
#  include <GL/glx.h>
#endif

#if defined(HAVE_GL_GLU_H)
#  define  F2__GLU__H
#  include <GL/glu.h>
#elif defined(HAVE_OPENGL_GLU_H)
#  define  F2__GLU__H
#  include <OpenGL/glu.h>
#endif

#ifdef HAVE_X11_EXTENSIONS_XF86VMODE_H
#  define  F2__XF86VMODE__H
#  include <X11/extensions/xf86vmode.h>
#endif

#ifdef HAVE_X11_XLIB_H
#  define  F2__XLIB__H
#  include <X11/Xlib.h>
#  include <X11/Xutil.h>
#endif

#ifdef HAVE_X11_KEYSYM_H
#  define  F2__KEYSYM__H
#  include <X11/keysym.h>
#endif

#ifdef F2__GTHREAD_SUPPORTED
#  ifndef F2__GTHREAD__SUPPORTED
#    define F2__GTHREAD__SUPPORTED
#  endif
#endif

// only define F2__GTK__SUPPORTED if F2__GTHREAD__SUPPORTED because GTHREAD is needed for threading.
#ifdef F2__GTHREAD__SUPPORTED
#  ifdef F2__GTK_SUPPORTED
#    ifndef F2__GTK__SUPPORTED
#      define F2__GTK__SUPPORTED
#    endif
#  endif
#endif

#ifdef F2__GTK__SUPPORTED
#  include <gtk/gtk.h>
#  include <gdk/gdkkeysyms.h>
#endif

#ifdef F2__LIBAVCODEC_SUPPORTED
#  ifdef HAVE_AV_CONFIG_H
#    undef HAVE_AV_CONFIG_H
#  endif
#  include <libavcodec/avcodec.h>
#  include <libavutil/mathematics.h>
#endif // F2__LIBAVCODEC_SUPPORTED

#ifdef F2__LIBSWSCALE_SUPPORTED
#  include <libswscale/swscale.h>
#endif // F2__LIBSWSCALE_SUPPORTED

#ifdef F2__CAIRO_SUPPORTED
#  include <cairo.h>
#  include <cairo-svg.h>
#  include <cairo-pdf.h>
#  include <cairo-ps.h>
#endif // F2__CAIRO_SUPPORTED

#endif // F2__SYSTEM_HEADERS__H

