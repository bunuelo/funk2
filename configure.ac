#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([funk2], [2.11], [bo@mit.edu])
AC_CONFIG_SRCDIR([c/funk2.c])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

#checks for operating system
AC_CANONICAL_SYSTEM

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Check if rpath is disabled
AC_MSG_CHECKING(whether to use rpath)
AC_ARG_ENABLE(rpath,
	[AC_HELP_STRING([--disable-rpath],
			[Patches libtool to not use rpath in the libraries produced.])],
	[funk2_cv_rpath="$enable_rpath"], [funk2_cv_rpath="yes"])
AC_MSG_RESULT($funk2_cv_rpath)

# Patch libtool to not use rpath if requested.
#
AC_CONFIG_COMMANDS([libtool-rpath-patch],
[if test "$libtool_patch_use_rpath" = "no"; then
   echo config.status: patching libtool to not use rpath
   sed < libtool > libtool-2 's/^hardcode_libdir_flag_spec.*$'/'hardcode_libdir_flag_spec=" -D__LIBTOOL_NO_RPATH__ "/'
   mv libtool-2 libtool
   chmod 755 libtool
fi],
[libtool_patch_use_rpath=$funk2_cv_rpath])

# initialize automake
AM_INIT_AUTOMAKE([subdir-objects])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h fcntl.h linux/sockios.h locale.h math.h netdb.h netinet/in.h stdlib.h string.h sys/ioctl.h sys/socket.h sys/time.h termios.h unistd.h])
AC_CHECK_HEADERS([GL/glx.h X11/extensions/xf86vmode.h], [], [],
[[
#ifdef HAVE_GL_GLX_H
#  include <GL/glx.h>
#endif
]])
AC_CHECK_LIB(clock_gettime)
AC_CHECK_LIB(gmon,_mcount)

AC_CHECK_HEADERS([X11/Xlib.h X11/keysym.h])
AC_CHECK_HEADERS([zlib.h], [], [AC_MSG_ERROR([*** Funk2 requires the zlib library in order to compress and decompress disk images.])])

# Checking for xmlrpc-c and its requirements.
have_xmlrpc_requirements=1
AC_MSG_NOTICE([Checking for xmlrpc-c and its requirements.])
AC_CHECK_LIB(curl,curl_easy_init, [],[have_xmlrpc_requirements=0])
AC_CHECK_HEADERS([xmlrpc-c/base.h xmlrpc-c/abyss.h xmlrpc-c/client.h xmlrpc-c/server.h xmlrpc-c/server_abyss.h],[],[have_xmlrpc_requirements=0])
AM_CONDITIONAL(XMLRPC_SUPPORTED, test $have_xmlrpc_requirements == 1)
if test $have_xmlrpc_requirements == 1
then
  AC_MSG_NOTICE([Feature xmlrpc-c is fully supported.])
  AC_DEFINE(F2__XMLRPC_SUPPORTED, 1, Build XML-RPC support into Funk2)
else
  AC_MSG_NOTICE([
*** XMLRPC-C is not required to build Funk2, but the xmlrpc-c development headers
*** are not installed, so XMLRPC-C support will not be compiled into Funk2.  The
*** latest version of xmlrpc-c is always available at http://xmlrpc-c.sourceforge.net])
fi

## Checking for ncurses.
#have_ncurses_requirements=1
#AC_MSG_NOTICE([Checking for ncurses and its requirements.])
#AC_CHECK_LIB(ncurses,initscr, [],[have_ncurses_requirements=0])
#AC_CHECK_HEADERS([ncurses.h],[],[have_ncurses_requirements=0])
#AM_CONDITIONAL(NCURSES_SUPPORTED, test $have_ncurses_requirements == 1)
#if test $have_ncurses_requirements == 1
#then
#  AC_MSG_NOTICE([Feature ncurses is fully supported.])
#  AC_DEFINE(F2__NCURSES_SUPPORTED, 1, Build ncurses support into Funk2)
#else
#  AC_MSG_NOTICE([
#*** ncurses is not required to build Funk2, but the ncurses development headers
#*** are not installed, so ncurses support will not be compiled into Funk2.  The
#*** latest version of ncurses is available at http://invisible-island.net/ncurses/ncurses.html])
#fi

PKG_CHECK_MODULES(GTK, gtk+-2.0, AC_DEFINE(F2__GTK_SUPPORTED, 1, [Define if we have support for GTK+]), [AC_MSG_NOTICE([
*** GTK+ 2.0 is not required to build Funk2, but the GLib development headers
*** are not installed, so GTK support will not be compiled into Funk2.  The
*** latest version of GLib is always available at http://www.gtk.org])])
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

PKG_CHECK_MODULES(GTHREAD, gthread-2.0, AC_DEFINE(F2__GTHREAD_SUPPORTED, 1, [Define if we have support for GTHREAD]), [AC_MSG_NOTICE([
*** GTHREAD 2.0 is not required to build Funk2, but the Gthread development headers
*** are not installed, so GTHREAD support will not be compiled into Funk2.  The
*** latest version of Gthread is always available at http://www.gtk.org])])
AC_SUBST(GTHREAD_CFLAGS)
AC_SUBST(GTHREAD_LIBS)

PKG_CHECK_MODULES(LIBAVCODEC, libavcodec, AC_DEFINE(F2__LIBAVCODEC_SUPPORTED, 1, [Define if we have support for LIBAVCODEC]), [AC_MSG_NOTICE([
*** LIBAVCODEC is not required to build Funk2, but the libavcodec development headers
*** are not installed, so LIBAVCODEC support will not be compiled into Funk2.  The
*** latest version of libavcodec is always available at http://www.ffmpeg.org])])
AC_SUBST(LIBAVCODEC_CFLAGS)
AC_SUBST(LIBAVCODEC_LIBS)

PKG_CHECK_MODULES(LIBSWSCALE, libswscale, AC_DEFINE(F2__LIBSWSCALE_SUPPORTED, 1, [Define if we have support for LIBSWSCALE]), [AC_MSG_NOTICE([
*** LIBSWSCALE is not required to build Funk2, but the libswscale development headers
*** are not installed, so LIBSWSCALE support will not be compiled into Funk2.  The
*** latest version of libswscale is always available at http://www.ffmpeg.org])])
AC_SUBST(LIBSWSCALE_CFLAGS)
AC_SUBST(LIBSWSCALE_LIBS)

PKG_CHECK_MODULES(CAIRO, cairo, AC_DEFINE(F2__CAIRO_SUPPORTED, 1, [Define if we have support for CAIRO]), [AC_MSG_NOTICE([
*** CAIRO is not required to build Funk2, but the cairo development headers
*** are not installed, so CAIRO support will not be compiled into Funk2.  The
*** latest version of cairo is always available at http://www.cairographics.org])])
AC_SUBST(CAIRO_CFLAGS)
AC_SUBST(CAIRO_LIBS)


# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_C_VOLATILE

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([bzero clock_gettime gethostbyname gethostname getpagesize inet_ntoa memset munmap select setlocale socket strerror strtol])

AC_CHECK_LIB(rt,clock_gettime, [need_realtime_link_in_makefile=1], [need_realtime_link_in_makefile=0])
AM_CONDITIONAL(NEED_REALTIME_LINK, test $need_realtime_link_in_makefile == 1)
if test $need_realtime_link_in_makefile == 1
then
  AC_MSG_NOTICE([Need to Link to RealTime Library to use clock_gettime.])
  AC_DEFINE(F2__HAVE_CLOCK_GETTIME, 1, Have clock_gettime support)
else
  AC_MSG_ERROR([*** Funk2 requires the clock_gettime function in order to measure process and thread execution times.])
fi

# checks for opengl
#AX_CHECK_GL
#AX_CHECK_GLU

# Check to see if -pthread or -lpthread is needed.  Prefer the former.
# In case the pthread.h system header is not found, this test will fail.
XPCFLAGS=""
CFLAGS="$CFLAGS -pthread"
AC_LINK_IFELSE(
 [AC_LANG_PROGRAM(
  [#include <pthread.h>
   void *g(void *d) { return NULL; }],
  [pthread_t t; pthread_create(&t,NULL,g,NULL);])],
 [XPCFLAGS=" -Wc,-pthread"],
 [CFLAGS="$save_CFLAGS" LIBS="-lpthread $LIBS"
  AC_LINK_IFELSE(
   [AC_LANG_PROGRAM(
    [#include <pthread.h>
     void *g(void *d) { return NULL; }],
    [pthread_t t; pthread_create(&t,NULL,g,NULL);])],
   [],
   [AC_MSG_ERROR([Pthreads are required to build funk2])])])

# atomic builtins are required for threading support.
AC_MSG_CHECKING(for GCC atomic builtins)
AC_LINK_IFELSE(
  AC_LANG_SOURCE(
    [[int main() {
        volatile unsigned long val = 1;
        __sync_synchronize();
        __sync_val_compare_and_swap(&val, 1, 0);
        __sync_add_and_fetch(&val, 1);
        __sync_sub_and_fetch(&val, 1);
        return 0;
      }
    ]]),
  AC_MSG_RESULT(yes)
  AC_DEFINE(GCC_ATOMIC_BUILTINS, 1, Build multithreading support into Funk2),
  AC_MSG_RESULT(no)
  AC_DEFINE(GCC_ATOMIC_BUILTINS, 0, Build multithreading support into Funk2)
  AC_MSG_WARN([Funk2 will be built thread-unsafe because atomic builtins are missing]))

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
