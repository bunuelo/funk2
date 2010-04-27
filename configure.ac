#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([funk2], [2.11], [bo@mit.edu])
AC_CONFIG_SRCDIR([c/funk2.c])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# initialize automake
AM_INIT_AUTOMAKE([subdir-objects])

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h fcntl.h locale.h netdb.h netinet/in.h stdlib.h string.h sys/ioctl.h sys/socket.h sys/time.h termios.h unistd.h math.h])
AC_CHECK_HEADERS([GL/glx.h X11/extensions/xf86vmode.h], [], [],
[[
#ifdef HAVE_GL_GLX_H
#  include <GL/glx.h>
#endif
]])
AC_CHECK_LIB(rt,clock_gettime)

AC_CHECK_HEADERS([X11/Xlib.h X11/keysym.h])

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

AX_CHECK_GL
AX_CHECK_GLU
ACX_PTHREAD

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
