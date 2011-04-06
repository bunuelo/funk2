// 
// Copyright (c) 2007-2008 Bo Morgan.
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

def_pcfunk0(f2__errno, 
	    "",
	    return f2integer__new(this_cause, errno));

// E2BIG "Argument list too long."
def_pcfunk0(f2__errno__e2big,
	    "",
	    return f2integer__new(this_cause, E2BIG));

// EACCES "Permission denied."
def_pcfunk0(f2__errno__eacces,
	    "",
	    return f2integer__new(this_cause, EACCES));

// EADDRINUSE "Address in use."
def_pcfunk0(f2__errno__eaddrinuse,
	    "",
	    return f2integer__new(this_cause, EADDRINUSE));

// EADDRNOTAVAIL "Address not available."
def_pcfunk0(f2__errno__eaddrnotavail,
	    "",
	    return f2integer__new(this_cause, EADDRNOTAVAIL));

// EAFNOSUPPORT "Address family not supported."
def_pcfunk0(f2__errno__eafnosupport,
	    "",
	    return f2integer__new(this_cause, EAFNOSUPPORT));

// EAGAIN "Resource unavailable, try again (may be the same value as [EWOULDBLOCK])."
def_pcfunk0(f2__errno__eagain,
	    "",
	    return f2integer__new(this_cause, EAGAIN));

// EALREADY "Connection already in progress."
def_pcfunk0(f2__errno__ealready,
	    "",
	    return f2integer__new(this_cause, EALREADY));

// EBADF  "Bad file descriptor."
def_pcfunk0(f2__errno__ebadf,
	    "",
	    return f2integer__new(this_cause, EBADF));

// EBADMSG "Bad message."
def_pcfunk0(f2__errno__ebadmsg,
	    "",
	    return f2integer__new(this_cause, EBADMSG));

// EBUSY  "Device or resource busy."
def_pcfunk0(f2__errno__ebusy,
	    "",
	    return f2integer__new(this_cause, EBUSY));

// ECANCELED "Operation canceled."
def_pcfunk0(f2__errno__ecanceled,
	    "",
	    return f2integer__new(this_cause, ECANCELED));

// ECHILD "No child processes."
def_pcfunk0(f2__errno__echild,
	    "",
	    return f2integer__new(this_cause, ECHILD));

// ECONNABORTED "Connection aborted."
def_pcfunk0(f2__errno__econnaborted,
	    "",
	    return f2integer__new(this_cause, ECONNABORTED));

// ECONNREFUSED "Connection refused."
def_pcfunk0(f2__errno__econnrefused,
	    "",
	    return f2integer__new(this_cause, ECONNREFUSED));

// ECONNRESET "Connection reset."
def_pcfunk0(f2__errno__econnreset,
	    "",
	    return f2integer__new(this_cause, ECONNRESET));

// EDEADLK "Resource deadlock would occur."
def_pcfunk0(f2__errno__edeadlk,
	    "",
	    return f2integer__new(this_cause, EDEADLK));

// EDESTADDRREQ "Destination address required."
def_pcfunk0(f2__errno__edestaddrreq,
	    "",
	    return f2integer__new(this_cause, EDESTADDRREQ));

// EDOM   "Mathematics argument out of domain of function."
def_pcfunk0(f2__errno__edom,
	    "",
	    return f2integer__new(this_cause, EDOM));

// EDQUOT "Reserved."
def_pcfunk0(f2__errno__edquot,
	    "",
	    return f2integer__new(this_cause, EDQUOT));

// EEXIST "File exists."
def_pcfunk0(f2__errno__eexist,
	    "",
	    return f2integer__new(this_cause, EEXIST));

// EFAULT "Bad address."
def_pcfunk0(f2__errno__efault,
	    "",
	    return f2integer__new(this_cause, EFAULT));

// EFBIG  "File too large."
def_pcfunk0(f2__errno__efbig,
	    "",
	    return f2integer__new(this_cause, EFBIG));

// EHOSTUNREACH "Host is unreachable."
def_pcfunk0(f2__errno__ehostunreach,
	    "",
	    return f2integer__new(this_cause, EHOSTUNREACH));

// EIDRM  "Identifier removed."
def_pcfunk0(f2__errno__eidrm,
	    "",
	    return f2integer__new(this_cause, EIDRM));

// EILSEQ "Illegal byte sequence."
def_pcfunk0(f2__errno__eilseq,
	    "",
	    return f2integer__new(this_cause, EILSEQ));

// EINPROGRESS "Operation in progress."
def_pcfunk0(f2__errno__einprogress,
	    "",
	    return f2integer__new(this_cause, EINPROGRESS));

// EINTR  "Interrupted function."
def_pcfunk0(f2__errno__eintr,
	    "",
	    return f2integer__new(this_cause, EINTR));

// EINVAL "Invalid argument."
def_pcfunk0(f2__errno__einval,
	    "",
	    return f2integer__new(this_cause, EINVAL));

// EIO    "I/O error."
def_pcfunk0(f2__errno__eio,
	    "",
	    return f2integer__new(this_cause, EIO));

// EISCONN "Socket is connected."
def_pcfunk0(f2__errno__eisconn,
	    "",
	    return f2integer__new(this_cause, EISCONN));

// EISDIR "Is a directory."
def_pcfunk0(f2__errno__eisdir,
	    "",
	    return f2integer__new(this_cause, EISDIR));

// ELOOP  "Too many levels of symbolic links."
def_pcfunk0(f2__errno__eloop,
	    "",
	    return f2integer__new(this_cause, ELOOP));

// EMFILE "Too many open files."
def_pcfunk0(f2__errno__emfile,
	    "",
	    return f2integer__new(this_cause, EMFILE));

// EMLINK "Too many links."
def_pcfunk0(f2__errno__emlink,
	    "",
	    return f2integer__new(this_cause, EMLINK));

// EMSGSIZE "Message too large."
def_pcfunk0(f2__errno__emsgsize,
	    "",
	    return f2integer__new(this_cause, EMSGSIZE));

// EMULTIHOP "Reserved."
def_pcfunk0(f2__errno__emultihop,
	    "",
	    return f2integer__new(this_cause, EMULTIHOP));

// ENAMETOOLONG "Filename too long."
def_pcfunk0(f2__errno__enametoolong,
	    "",
	    return f2integer__new(this_cause, ENAMETOOLONG));

// ENETDOWN "Network is down."
def_pcfunk0(f2__errno__enetdown,
	    "",
	    return f2integer__new(this_cause, ENETDOWN));

// ENETRESET "Connection aborted by network."
def_pcfunk0(f2__errno__enetreset,
	    "",
	    return f2integer__new(this_cause, ENETRESET));

// ENETUNREACH "Network unreachable."
def_pcfunk0(f2__errno__enetunreach,
	    "",
	    return f2integer__new(this_cause, ENETUNREACH));

// ENFILE "Too many files open in system."
def_pcfunk0(f2__errno__enfile,
	    "",
	    return f2integer__new(this_cause, ENFILE));

// ENOBUFS "No buffer space available."
def_pcfunk0(f2__errno__enobufs,
	    "",
	    return f2integer__new(this_cause, ENOBUFS));

// ENODATA "No message is available on the STREAM head read queue."
def_pcfunk0(f2__errno__enodata,
	    "",
	    return f2integer__new(this_cause, ENODATA));

// ENODEV "No such device."
def_pcfunk0(f2__errno__enodev,
	    "",
	    return f2integer__new(this_cause, ENODEV));

// ENOENT "No such file or directory."
def_pcfunk0(f2__errno__enoent,
	    "",
	    return f2integer__new(this_cause, ENOENT));

// ENOEXEC "Executable file format error."
def_pcfunk0(f2__errno__enoexec,
	    "",
	    return f2integer__new(this_cause, ENOEXEC));

// ENOLCK "No locks available."
def_pcfunk0(f2__errno__enolock,
	    "",
	    return f2integer__new(this_cause, ENOLCK));

// ENOLINK "Reserved."
def_pcfunk0(f2__errno__enolink,
	    "",
	    return f2integer__new(this_cause, ENOLINK));

// ENOMEM "Not enough space."
def_pcfunk0(f2__errno__enomem,
	    "",
	    return f2integer__new(this_cause, ENOMEM));

// ENOMSG "No message of the desired type."
def_pcfunk0(f2__errno__enomsg,
	    "",
	    return f2integer__new(this_cause, ENOMSG));

// ENOPROTOOPT "Protocol not available."
def_pcfunk0(f2__errno__enoprotoopt,
	    "",
	    return f2integer__new(this_cause, ENOPROTOOPT));

// ENOSPC "No space left on device."
def_pcfunk0(f2__errno__enospc,
	    "",
	    return f2integer__new(this_cause, ENOSPC));

// ENOSR  "No STREAM resources."
def_pcfunk0(f2__errno__enosr,
	    "",
	    return f2integer__new(this_cause, ENOSR));

// ENOSTR "Not a STREAM."
def_pcfunk0(f2__errno__enostr,
	    "",
	    return f2integer__new(this_cause, ENOSTR));

// ENOSYS "Function not supported."
def_pcfunk0(f2__errno__enosys,
	    "",
	    return f2integer__new(this_cause, ENOSYS));

// ENOTCONN "The socket is not connected."
def_pcfunk0(f2__errno__enotconn,
	    "",
	    return f2integer__new(this_cause, ENOTCONN));

// ENOTDIR "Not a directory."
def_pcfunk0(f2__errno__enotdir,
	    "",
	    return f2integer__new(this_cause, ENOTDIR));

// ENOTEMPTY "Directory not empty."
def_pcfunk0(f2__errno__enotempty,
	    "",
	    return f2integer__new(this_cause, ENOTEMPTY));

// ENOTSOCK "Not a socket."
def_pcfunk0(f2__errno__enotsock,
	    "",
	    return f2integer__new(this_cause, ENOTSOCK));

// ENOTSUP "Not supported."
def_pcfunk0(f2__errno__enotsup,
	    "",
	    return f2integer__new(this_cause, ENOTSUP));

// ENOTTY "Inappropriate I/O control operation."
def_pcfunk0(f2__errno__enotty,
	    "",
	    return f2integer__new(this_cause, ENOTTY));

// ENXIO  "No such device or address."
def_pcfunk0(f2__errno__enxio,
	    "",
	    return f2integer__new(this_cause, ENXIO));

// EOPNOTSUPP "Operation not supported on socket."
def_pcfunk0(f2__errno__eopnotsupp,
	    "",
	    return f2integer__new(this_cause, EOPNOTSUPP));

// EOVERFLOW "Value too large to be stored in data type."
def_pcfunk0(f2__errno__eoverflow,
	    "",
	    return f2integer__new(this_cause, EOVERFLOW));

// EPERM  "Operation not permitted."
def_pcfunk0(f2__errno__eperm,
	    "",
	    return f2integer__new(this_cause, EPERM));

// EPIPE  "Broken pipe."
def_pcfunk0(f2__errno__epipe,
	    "",
	    return f2integer__new(this_cause, EPIPE));

// EPROTO "Protocol error."
def_pcfunk0(f2__errno__eproto,
	    "",
	    return f2integer__new(this_cause, EPROTO));

// EPROTONOSUPPORT "Protocol not supported."
def_pcfunk0(f2__errno__eprotonosupport,
	    "",
	    return f2integer__new(this_cause, EPROTONOSUPPORT));

// EPROTOTYPE "Protocol wrong type for socket."
def_pcfunk0(f2__errno__eprototype,
	    "",
	    return f2integer__new(this_cause, EPROTOTYPE));

// ERANGE "Result too large."
def_pcfunk0(f2__errno__erange,
	    "",
	    return f2integer__new(this_cause, ERANGE));

// EROFS  "Read-only file system."
def_pcfunk0(f2__errno__erofs,
	    "",
	    return f2integer__new(this_cause, EROFS));

// ESPIPE "Invalid seek."
def_pcfunk0(f2__errno__espipe,
	    "",
	    return f2integer__new(this_cause, ESPIPE));

// ESRCH  "No such process."
def_pcfunk0(f2__errno__esrch,
	    "",
	    return f2integer__new(this_cause, ESRCH));

// ESTALE "Reserved."
def_pcfunk0(f2__errno__estale,
	    "",
	    return f2integer__new(this_cause, ESTALE));

// ETIME  "Stream ioctl() timeout."
def_pcfunk0(f2__errno__etime,
	    "",
	    return f2integer__new(this_cause, ETIME));

// ETIMEDOUT "Connection timed out."
def_pcfunk0(f2__errno__etimeout,
	    "",
	    return f2integer__new(this_cause, ETIMEDOUT));

// ETXTBSY "Text file busy."
def_pcfunk0(f2__errno__etxtbsy,
	    "",
	    return f2integer__new(this_cause, ETXTBSY));

// EWOULDBLOCK "Operation would block (may be the same value as [EAGAIN])."
def_pcfunk0(f2__errno__ewouldblock,
	    "",
	    return f2integer__new(this_cause, EWOULDBLOCK));

// EXDEV  "Cross-device link."
def_pcfunk0(f2__errno__exdev,
	    "",
	    return f2integer__new(this_cause, EXDEV));

void f2__primfunks__errno__reinitialize_globalvars() {
  //f2ptr cause = f2_primfunks__errno_c__cause__new(initial_cause(), nil, nil);
}

void f2__primfunks__errno__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primfunks__errno", "", &f2__primfunks__errno__reinitialize_globalvars);
  
  f2__primfunks__errno__reinitialize_globalvars();
  
  f2__primcfunk__init(f2__errno, "(as defined in errno.h)");
  
  f2__primcfunk__init(f2__errno__e2big, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eacces, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eaddrinuse, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eaddrnotavail, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eafnosupport, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eagain, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__ealready, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__ebadf, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__ebadmsg, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__ebusy, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__ecanceled, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__echild, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__econnaborted, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__econnrefused, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__econnreset, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__edeadlk, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__edestaddrreq, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__edom, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__edquot, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eexist, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__efault, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__efbig, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__ehostunreach, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eidrm, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eilseq, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__einprogress, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eintr, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__einval, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eio, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eisconn, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eisdir, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eloop, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__emfile, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__emlink, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__emsgsize, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__emultihop, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enametoolong, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enetdown, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enetreset, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enetunreach, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enfile, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enobufs, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enodata, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enodev, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enoent, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enoexec, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enolock, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enolink, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enomem, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enomsg, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enoprotoopt, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enospc, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enosr, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enostr, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enosys, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enotconn, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enotdir, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enotempty, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enotsock, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enotsup, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enotty, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__enxio, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eopnotsupp, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eoverflow, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eperm, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__epipe, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eproto, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eprotonosupport, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__eprototype, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__erange, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__erofs, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__espipe, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__esrch, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__estale, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__etime, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__etimeout, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__etxtbsy, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__ewouldblock, "(as defined in errno.h)");
  f2__primcfunk__init(f2__errno__exdev, "(as defined in errno.h)");
}

  

