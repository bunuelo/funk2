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

// architecture specific defines

#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif

// Bug in gcc prevents from using CPP_DEMANGLE in pure "C"
#if !defined(__cplusplus) && !defined(NO_CPP_DEMANGLE)
#define NO_CPP_DEMANGLE
#endif

#ifdef F2__APPLE
#  define MAP_ANONYMOUS MAP_ANON
// see: http://www.osxfaq.com/man/4/tty.ws
#  define SIOCOUTQ TIOCOUTQ
#  define SIOCINQ  TIOCSTI
#endif // F2__APPLE

#if defined(F2__XMLRPC_SUPPORTED)
#  ifndef _XOPEN_SOURCE
#    define _XOPEN_SOURCE 600
#  endif
#endif

#include "f2_archconfig.h"

// architecture specific includes

#if defined(HAVE_MACH_MACH_H)
#  include <mach/mach.h>
#endif // HAVE_MACH_MACH_H

#if defined(HAVE_MACH_CLOCK_H)
#  include <mach/clock.h>
#endif // HAVE_MACH_CLOCK_H

#if defined(HAVE_MACH_MACH_TIME_h)
#  include <mach/mach_time.h>
#endif // HAVE_MACH_MACH_TIME_h

#if defined(HAVE_SYS_RESOURCE_H)
#  include <sys/resource.h>
#endif // HAVE_SYS_RESOURCE_H

#if defined(HAVE_SYS_SOCKIO_H)
#  include <sys/sockio.h>
#endif // HAVE_SYS_SOCKIO_H

#if defined(HAVE_LINUX_SOCKIOS_H)
#  include <linux/sockios.h>
#endif

#if defined(HAVE_XMLRPC_C_BASE_H)
#  include <xmlrpc-c/base.h>
#endif // HAVE_XMLRPC_C_BASE_H

#if defined(HAVE_XMLRPC_C_ABYSS_H)
#  include <xmlrpc-c/abyss.h>
#endif // HAVE_XMLRPC_C_ABYSS_H

#if defined(HAVE_XMLRPC_C_CLIENT_H)
#  include <xmlrpc-c/client.h>
#endif // HAVE_XMLRPC_C_CLIENT_H

#if defined(HAVE_XMLRPC_C_SERVER_H)
#  include <xmlrpc-c/server.h>
#endif // HAVE_XMLRPC_C_SERVER_H

#if defined(HAVE_XMLRPC_C_SERVER_ABYSS_H)
#  include <xmlrpc-c/server_abyss.h>
#endif // HAVE_XMLRPC_C_SERVER_ABYSS_H

#if defined(HAVE_ASSERT_H)
#  include <assert.h>
#endif // HAVE_ASSERT_H

#if defined(HAVE_ARPA_INET_H)
#include <arpa/inet.h>
#endif // HAVE_ARPA_INET_H

#if defined(HAVE_CXXABI_H)
#  ifndef NO_CPP_DEMANGLE
#    include <cxxabi.h>
#    ifdef __cplusplus
using __cxxabiv1::__cxa_demangle;
#    endif
#  endif
#endif // HAVE_CXXABI_H

#if defined(HAVE_DIRENT_H)
#  include <dirent.h>
#endif // HAVE_DIRENT_H

#if defined(HAVE_DLFCN_H)
#  include <dlfcn.h>
#endif // HAVE_DLFCN_H

#if defined(HAVE_ERRNO_H)
#  include <errno.h>
#endif // HAVE_ERRNO_H

#if defined(HAVE_EXECINFO_H)
#  include <execinfo.h>
#endif // HAVE_EXECINFO_H

#if defined(HAVE_FCNTL_H)
#  include <fcntl.h>
#endif // HAVE_FCNTL_H

#ifdef F2__GMODULE__SUPPORTED
#  include <gmodule.h>
#endif

#if defined(HAVE_LIMITS_H)
#  include <limits.h>
#endif // HAVE_LIMITS_H

#if defined(HAVE_LOCALE_H)
#  include <locale.h>
#endif // HAVE_LOCALE_H

#if defined(HAVE_MATH_H)
#  include <math.h>
#endif // HAVE_MATH_H

#if defined(HAVE_NET_IF_H)
#  include <net/if.h>
#endif // HAVE_NET_IF_H

#if defined(HAVE_NETDB_H)
#  include <netdb.h>
#endif // HAVE_NETDB_H

#if defined(HAVE_NETINET_IN_H)
#  include <netinet/in.h>
#endif // HAVE_NETINET_IN_H

#if defined(HAVE_NETINET_TCP_H)
#  include <netinet/tcp.h>
#endif // HAVE_NETINET_TCP_H

#if defined(HAVE_PTHREAD_H)
#  include <pthread.h>
#endif // HAVE_PTHREAD_H

#if defined(HAVE_SCHED_H)
#  include <sched.h>
#endif // HAVE_SCHED_H

#if defined(HAVE_SIGNAL_H)
#  include <signal.h>
#endif // HAVE_SIGNAL_H

#if defined(HAVE_STDARG_H)
#  include <stdarg.h>
#endif // HAVE_STDARG_H

#if defined(HAVE_STRING_H)
#  include <string.h>
#endif // HAVE_STRING_H

#if defined(HAVE_SYS_IOCTL_H)
#  include <sys/ioctl.h>
#endif // HAVE_SYS_IOCTL_H

#if defined(HAVE_SYS_MMAN_H)
#  include <sys/mman.h>
#endif // HAVE_SYS_MMAN_H

#if defined(HAVE_SYS_SOCKET_H)
#  include <sys/socket.h>
#endif // HAVE_SYS_SOCKET_H

#if defined(HAVE_SYS_STAT_H)
#  include <sys/stat.h>
#endif // HAVE_SYS_STAT_H

#if defined(HAVE_SYS_SYSCALL_H)
#  include <sys/syscall.h>
#endif // HAVE_SYS_SYSCALL_H

#if defined(HAVE_SYS_TIME_H)
#  include <sys/time.h>
#endif // HAVE_SYS_TIME_H

#if defined(HAVE_SYS_TIMES_H)
#  include <sys/times.h>
#endif // HAVE_SYS_TIMES_H

#if defined(HAVE_SYS_TYPES_H)
#  include <sys/types.h>
#endif // HAVE_SYS_TYPES_H

#if defined(HAVE_SYS_WAIT_H)
#  include <sys/wait.h>
#endif // HAVE_SYS_WAIT_H

#if defined(HAVE_TERMIOS_H)
#  include <termios.h>
#endif // HAVE_TERMIOS_H

#if defined(HAVE_TIME_H)
#  include <time.h>
#endif // HAVE_TIME_H

#if defined(HAVE_UCONTEXT_H)
#  include <ucontext.h>
#endif // HAVE_UCONTEXT_H

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


// define fake file permissions in case they are not defined.

#ifndef S_IRGRP
#  define S_IRGRP 0
#endif

#ifndef S_IWGRP
#  define S_IWGRP 0
#endif

#ifndef S_IROTH
#  define S_IROTH 0
#endif

#ifndef S_IWOTH
#  define S_IWOTH 0
#endif


// define dlfcn constants in case they are not defined

#ifndef RTLD_LAZY
#  define RTLD_LAZY 1 // lazy function call binding
#endif

#ifndef RTLD_NOW
#  define RTLD_NOW 2 // immediate function call binding
#endif

#ifndef RTLD_GLOBAL
#  define RTLD_GLOBAL 4 // symbols in this dlopen'ed obj are visible to other dlopen'ed objs
#endif


#endif // F2__SYSTEM_HEADERS__H

