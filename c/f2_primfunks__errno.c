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

#include "funk2.h"

f2ptr f2__errno__errno(f2ptr cause) {
  return f2integer__new(cause, errno);
}
def_pcfunk0(errno__errno, 
	    "",
	    return f2__errno__errno(this_cause));

// E2BIG "Argument list too long."
f2ptr f2__errno__e2big(f2ptr cause) {
  return f2integer__new(cause, E2BIG);
}
def_pcfunk0(errno__e2big,
	    "",
	    return f2__errno__e2big(this_cause));

// EACCES "Permission denied."
f2ptr f2__errno__eacces(f2ptr cause) {
  return f2integer__new(cause, EACCES);
}
def_pcfunk0(errno__eacces,
	    "",
	    return f2__errno__eacces(this_cause));

// EADDRINUSE "Address in use."
f2ptr f2__errno__eaddrinuse(f2ptr cause) {
  return f2integer__new(cause, EADDRINUSE);
}
def_pcfunk0(errno__eaddrinuse,
	    "",
	    return f2__errno__eaddrinuse(this_cause));

// EADDRNOTAVAIL "Address not available."
f2ptr f2__errno__eaddrnotavail(f2ptr cause) {
  return f2integer__new(cause, EADDRNOTAVAIL);
}
def_pcfunk0(errno__eaddrnotavail,
	    "",
	    return f2__errno__eaddrnotavail(this_cause));

// EAFNOSUPPORT "Address family not supported."
f2ptr f2__errno__eafnosupport(f2ptr cause) {
  return f2integer__new(cause, EAFNOSUPPORT);
}
def_pcfunk0(errno__eafnosupport,
	    "",
	    return f2__errno__eafnosupport(this_cause));

// EAGAIN "Resource unavailable, try again (may be the same value as [EWOULDBLOCK])."
f2ptr f2__errno__eagain(f2ptr cause) {
  return f2integer__new(cause, EAGAIN);
}
def_pcfunk0(errno__eagain,
	    "",
	    return f2__errno__eagain(this_cause));

// EALREADY "Connection already in progress."
f2ptr f2__errno__ealready(f2ptr cause) {
  return f2integer__new(cause, EALREADY);
}
def_pcfunk0(errno__ealready,
	    "",
	    return f2__errno__ealready(this_cause));

// EBADF  "Bad file descriptor."
f2ptr f2__errno__ebadf(f2ptr cause) {
  return f2integer__new(cause, EBADF);
}
def_pcfunk0(errno__ebadf,
	    "",
	    return f2__errno__ebadf(this_cause));

// EBADMSG "Bad message."
f2ptr f2__errno__ebadmsg(f2ptr cause) {
  return f2integer__new(cause, EBADMSG);
}
def_pcfunk0(errno__ebadmsg,
	    "",
	    return f2__errno__ebadmsg(this_cause));

// EBUSY  "Device or resource busy."
f2ptr f2__errno__ebusy(f2ptr cause) {
  return f2integer__new(cause, EBUSY);
}
def_pcfunk0(errno__ebusy,
	    "",
	    return f2__errno__ebusy(this_cause));

// ECANCELED "Operation canceled."
f2ptr f2__errno__ecanceled(f2ptr cause) {
  return f2integer__new(cause, ECANCELED);
}
def_pcfunk0(errno__ecanceled,
	    "",
	    return f2__errno__ecanceled(this_cause));

// ECHILD "No child processes."
f2ptr f2__errno__echild(f2ptr cause) {
  return f2integer__new(cause, ECHILD);
}
def_pcfunk0(errno__echild,
	    "",
	    return f2__errno__echild(this_cause));

// ECONNABORTED "Connection aborted."
f2ptr f2__errno__econnaborted(f2ptr cause) {
  return f2integer__new(cause, ECONNABORTED);
}
def_pcfunk0(errno__econnaborted,
	    "",
	    return f2__errno__econnaborted(this_cause));

// ECONNREFUSED "Connection refused."
f2ptr f2__errno__econnrefused(f2ptr cause) {
  return f2integer__new(cause, ECONNREFUSED);
}
def_pcfunk0(errno__econnrefused,
	    "",
	    return f2__errno__econnrefused(this_cause));

// ECONNRESET "Connection reset."
f2ptr f2__errno__econnreset(f2ptr cause) {
  return f2integer__new(cause, ECONNRESET);
}
def_pcfunk0(errno__econnreset,
	    "",
	    return f2__errno__econnreset(this_cause));

// EDEADLK "Resource deadlock would occur."
f2ptr f2__errno__edeadlk(f2ptr cause) {
  return f2integer__new(cause, EDEADLK);
}
def_pcfunk0(errno__edeadlk,
	    "",
	    return f2__errno__edeadlk(this_cause));

// EDESTADDRREQ "Destination address required."
f2ptr f2__errno__edestaddrreq(f2ptr cause) {
  return f2integer__new(cause, EDESTADDRREQ);
}
def_pcfunk0(errno__edestaddrreq,
	    "",
	    return f2__errno__edestaddrreq(this_cause));

// EDOM   "Mathematics argument out of domain of function."
f2ptr f2__errno__edom(f2ptr cause) {
  return f2integer__new(cause, EDOM);
}
def_pcfunk0(errno__edom,
	    "",
	    return f2__errno__edom(this_cause));

// EDQUOT "Reserved."
f2ptr f2__errno__edquot(f2ptr cause) {
  return f2integer__new(cause, EDQUOT);
}
def_pcfunk0(errno__edquot,
	    "",
	    return f2__errno__edquot(this_cause));

// EEXIST "File exists."
f2ptr f2__errno__eexist(f2ptr cause) {
  return f2integer__new(cause, EEXIST);
}
def_pcfunk0(errno__eexist,
	    "",
	    return f2__errno__eexist(this_cause));

// EFAULT "Bad address."
f2ptr f2__errno__efault(f2ptr cause) {
  return f2integer__new(cause, EFAULT);
}
def_pcfunk0(errno__efault,
	    "",
	    return f2__errno__efault(this_cause));

// EFBIG  "File too large."
f2ptr f2__errno__efbig(f2ptr cause) {
  return f2integer__new(cause, EFBIG);
}
def_pcfunk0(errno__efbig,
	    "",
	    return f2__errno__efbig(this_cause));

// EHOSTUNREACH "Host is unreachable."
f2ptr f2__errno__ehostunreach(f2ptr cause) {
  return f2integer__new(cause, EHOSTUNREACH);
}
def_pcfunk0(errno__ehostunreach,
	    "",
	    return f2__errno__ehostunreach(this_cause));

// EIDRM  "Identifier removed."
f2ptr f2__errno__eidrm(f2ptr cause) {
  return f2integer__new(cause, EIDRM);
}
def_pcfunk0(errno__eidrm,
	    "",
	    return f2__errno__eidrm(this_cause));

// EILSEQ "Illegal byte sequence."
f2ptr f2__errno__eilseq(f2ptr cause) {
  return f2integer__new(cause, EILSEQ);
}
def_pcfunk0(errno__eilseq,
	    "",
	    return f2__errno__eilseq(this_cause));

// EINPROGRESS "Operation in progress."
f2ptr f2__errno__einprogress(f2ptr cause) {
  return f2integer__new(cause, EINPROGRESS);
}
def_pcfunk0(errno__einprogress,
	    "",
	    return f2__errno__einprogress(this_cause));

// EINTR  "Interrupted function."
f2ptr f2__errno__eintr(f2ptr cause) {
  return f2integer__new(cause, EINTR);
}
def_pcfunk0(errno__eintr,
	    "",
	    return f2__errno__eintr(this_cause));

// EINVAL "Invalid argument."
f2ptr f2__errno__einval(f2ptr cause) {
  return f2integer__new(cause, EINVAL);
}
def_pcfunk0(errno__einval,
	    "",
	    return f2__errno__einval(this_cause));

// EIO    "I/O error."
f2ptr f2__errno__eio(f2ptr cause) {
  return f2integer__new(cause, EIO);
}
def_pcfunk0(errno__eio,
	    "",
	    return f2__errno__eio(this_cause));

// EISCONN "Socket is connected."
f2ptr f2__errno__eisconn(f2ptr cause) {
  return f2integer__new(cause, EISCONN);
}
def_pcfunk0(errno__eisconn,
	    "",
	    return f2__errno__eisconn(this_cause));

// EISDIR "Is a directory."
f2ptr f2__errno__eisdir(f2ptr cause) {
  return f2integer__new(cause, EISDIR);
}
def_pcfunk0(errno__eisdir,
	    "",
	    return f2__errno__eisdir(this_cause));

// ELOOP  "Too many levels of symbolic links."
f2ptr f2__errno__eloop(f2ptr cause) {
  return f2integer__new(cause, ELOOP);
}
def_pcfunk0(errno__eloop,
	    "",
	    return f2__errno__eloop(this_cause));

// EMFILE "Too many open files."
f2ptr f2__errno__emfile(f2ptr cause) {
  return f2integer__new(cause, EMFILE);
}
def_pcfunk0(errno__emfile,
	    "",
	    return f2__errno__emfile(this_cause));

// EMLINK "Too many links."
f2ptr f2__errno__emlink(f2ptr cause) {
  return f2integer__new(cause, EMLINK);
}
def_pcfunk0(errno__emlink,
	    "",
	    return f2__errno__emlink(this_cause));

// EMSGSIZE "Message too large."
f2ptr f2__errno__emsgsize(f2ptr cause) {
  return f2integer__new(cause, EMSGSIZE);
}
def_pcfunk0(errno__emsgsize,
	    "",
	    return f2__errno__emsgsize(this_cause));

// EMULTIHOP "Reserved."
f2ptr f2__errno__emultihop(f2ptr cause) {
  return f2integer__new(cause, EMULTIHOP);
}
def_pcfunk0(errno__emultihop,
	    "",
	    return f2__errno__emultihop(this_cause));

// ENAMETOOLONG "Filename too long."
f2ptr f2__errno__enametoolong(f2ptr cause) {
  return f2integer__new(cause, ENAMETOOLONG);
}
def_pcfunk0(errno__enametoolong,
	    "",
	    return f2__errno__enametoolong(this_cause));

// ENETDOWN "Network is down."
f2ptr f2__errno__enetdown(f2ptr cause) {
  return f2integer__new(cause, ENETDOWN);
}
def_pcfunk0(errno__enetdown,
	    "",
	    return f2__errno__enetdown(this_cause));

// ENETRESET "Connection aborted by network."
f2ptr f2__errno__enetreset(f2ptr cause) {
  return f2integer__new(cause, ENETRESET);
}
def_pcfunk0(errno__enetreset,
	    "",
	    return f2__errno__enetreset(this_cause));

// ENETUNREACH "Network unreachable."
f2ptr f2__errno__enetunreach(f2ptr cause) {
  return f2integer__new(cause, ENETUNREACH);
}
def_pcfunk0(errno__enetunreach,
	    "",
	    return f2__errno__enetunreach(this_cause));

// ENFILE "Too many files open in system."
f2ptr f2__errno__enfile(f2ptr cause) {
  return f2integer__new(cause, ENFILE);
}
def_pcfunk0(errno__enfile,
	    "",
	    return f2__errno__enfile(this_cause));

// ENOBUFS "No buffer space available."
f2ptr f2__errno__enobufs(f2ptr cause) {
  return f2integer__new(cause, ENOBUFS);
}
def_pcfunk0(errno__enobufs,
	    "",
	    return f2__errno__enobufs(this_cause));

// ENODATA "No message is available on the STREAM head read queue."
f2ptr f2__errno__enodata(f2ptr cause) {
  return f2integer__new(cause, ENODATA);
}
def_pcfunk0(errno__enodata,
	    "",
	    return f2__errno__enodata(this_cause));

// ENODEV "No such device."
f2ptr f2__errno__enodev(f2ptr cause) {
  return f2integer__new(cause, ENODEV);
}
def_pcfunk0(errno__enodev,
	    "",
	    return f2__errno__enodev(this_cause));

// ENOENT "No such file or directory."
f2ptr f2__errno__enoent(f2ptr cause) {
  return f2integer__new(cause, ENOENT);
}
def_pcfunk0(errno__enoent,
	    "",
	    return f2__errno__enoent(this_cause));

// ENOEXEC "Executable file format error."
f2ptr f2__errno__enoexec(f2ptr cause) {
  return f2integer__new(cause, ENOEXEC);
}
def_pcfunk0(errno__enoexec,
	    "",
	    return f2__errno__enoexec(this_cause));

// ENOLCK "No locks available."
f2ptr f2__errno__enolock(f2ptr cause) {
  return f2integer__new(cause, ENOLCK);
}
def_pcfunk0(errno__enolock,
	    "",
	    return f2__errno__enolock(this_cause));

// ENOLINK "Reserved."
f2ptr f2__errno__enolink(f2ptr cause) {
  return f2integer__new(cause, ENOLINK);
}
def_pcfunk0(errno__enolink,
	    "",
	    return f2__errno__enolink(this_cause));

// ENOMEM "Not enough space."
f2ptr f2__errno__enomem(f2ptr cause) {
  return f2integer__new(cause, ENOMEM);
}
def_pcfunk0(errno__enomem,
	    "",
	    return f2__errno__enomem(this_cause));

// ENOMSG "No message of the desired type."
f2ptr f2__errno__enomsg(f2ptr cause) {
  return f2integer__new(cause, ENOMSG);
}
def_pcfunk0(errno__enomsg,
	    "",
	    return f2__errno__enomsg(this_cause));

// ENOPROTOOPT "Protocol not available."
f2ptr f2__errno__enoprotoopt(f2ptr cause) {
  return f2integer__new(cause, ENOPROTOOPT);
}
def_pcfunk0(errno__enoprotoopt,
	    "",
	    return f2__errno__enoprotoopt(this_cause));

// ENOSPC "No space left on device."
f2ptr f2__errno__enospc(f2ptr cause) {
  return f2integer__new(cause, ENOSPC);
}
def_pcfunk0(errno__enospc,
	    "",
	    return f2__errno__enospc(this_cause));

// ENOSR  "No STREAM resources."
f2ptr f2__errno__enosr(f2ptr cause) {
  return f2integer__new(cause, ENOSR);
}
def_pcfunk0(errno__enosr,
	    "",
	    return f2__errno__enosr(this_cause));

// ENOSTR "Not a STREAM."
f2ptr f2__errno__enostr(f2ptr cause) {
  return f2integer__new(cause, ENOSTR);
}
def_pcfunk0(errno__enostr,
	    "",
	    return f2__errno__enostr(this_cause));

// ENOSYS "Function not supported."
f2ptr f2__errno__enosys(f2ptr cause) {
  return f2integer__new(cause, ENOSYS);
}
def_pcfunk0(errno__enosys,
	    "",
	    return f2__errno__enosys(this_cause));

// ENOTCONN "The socket is not connected."
f2ptr f2__errno__enotconn(f2ptr cause) {
  return f2integer__new(cause, ENOTCONN);
}
def_pcfunk0(errno__enotconn,
	    "",
	    return f2__errno__enotconn(this_cause));

// ENOTDIR "Not a directory."
f2ptr f2__errno__enotdir(f2ptr cause) {
  return f2integer__new(cause, ENOTDIR);
}
def_pcfunk0(errno__enotdir,
	    "",
	    return f2__errno__enotdir(this_cause));

// ENOTEMPTY "Directory not empty."
f2ptr f2__errno__enotempty(f2ptr cause) {
  return f2integer__new(cause, ENOTEMPTY);
}
def_pcfunk0(errno__enotempty,
	    "",
	    return f2__errno__enotempty(this_cause));

// ENOTSOCK "Not a socket."
f2ptr f2__errno__enotsock(f2ptr cause) {
  return f2integer__new(cause, ENOTSOCK);
}
def_pcfunk0(errno__enotsock,
	    "",
	    return f2__errno__enotsock(this_cause));

// ENOTSUP "Not supported."
f2ptr f2__errno__enotsup(f2ptr cause) {
  return f2integer__new(cause, ENOTSUP);
}
def_pcfunk0(errno__enotsup,
	    "",
	    return f2__errno__enotsup(this_cause));

// ENOTTY "Inappropriate I/O control operation."
f2ptr f2__errno__enotty(f2ptr cause) {
  return f2integer__new(cause, ENOTTY);
}
def_pcfunk0(errno__enotty,
	    "",
	    return f2__errno__enotty(this_cause));

// ENXIO  "No such device or address."
f2ptr f2__errno__enxio(f2ptr cause) {
  return f2integer__new(cause, ENXIO);
}
def_pcfunk0(errno__enxio,
	    "",
	    return f2__errno__enxio(this_cause));

// EOPNOTSUPP "Operation not supported on socket."
f2ptr f2__errno__eopnotsupp(f2ptr cause) {
  return f2integer__new(cause, EOPNOTSUPP);
}
def_pcfunk0(errno__eopnotsupp,
	    "",
	    return f2__errno__eopnotsupp(this_cause));

// EOVERFLOW "Value too large to be stored in data type."
f2ptr f2__errno__eoverflow(f2ptr cause) {
  return f2integer__new(cause, EOVERFLOW);
}
def_pcfunk0(errno__eoverflow,
	    "",
	    return f2__errno__eoverflow(this_cause));

// EPERM  "Operation not permitted."
f2ptr f2__errno__eperm(f2ptr cause) {
  return f2integer__new(cause, EPERM);
}
def_pcfunk0(errno__eperm,
	    "",
	    return f2__errno__eperm(this_cause));

// EPIPE  "Broken pipe."
f2ptr f2__errno__epipe(f2ptr cause) {
  return f2integer__new(cause, EPIPE);
}
def_pcfunk0(errno__epipe,
	    "",
	    return f2__errno__epipe(this_cause));

// EPROTO "Protocol error."
f2ptr f2__errno__eproto(f2ptr cause) {
  return f2integer__new(cause, EPROTO);
}
def_pcfunk0(errno__eproto,
	    "",
	    return f2__errno__eproto(this_cause));

// EPROTONOSUPPORT "Protocol not supported."
f2ptr f2__errno__eprotonosupport(f2ptr cause) {
  return f2integer__new(cause, EPROTONOSUPPORT);
}
def_pcfunk0(errno__eprotonosupport,
	    "",
	    return f2__errno__eprotonosupport(this_cause));

// EPROTOTYPE "Protocol wrong type for socket."
f2ptr f2__errno__eprototype(f2ptr cause) {
  return f2integer__new(cause, EPROTOTYPE);
}
def_pcfunk0(errno__eprototype,
	    "",
	    return f2__errno__eprototype(this_cause));

// ERANGE "Result too large."
f2ptr f2__errno__erange(f2ptr cause) {
  return f2integer__new(cause, ERANGE);
}
def_pcfunk0(errno__erange,
	    "",
	    return f2__errno__erange(this_cause));

// EROFS  "Read-only file system."
f2ptr f2__errno__erofs(f2ptr cause) {
  return f2integer__new(cause, EROFS);
}
def_pcfunk0(errno__erofs,
	    "",
	    return f2__errno__erofs(this_cause));

// ESPIPE "Invalid seek."
f2ptr f2__errno__espipe(f2ptr cause) {
  return f2integer__new(cause, ESPIPE);
}
def_pcfunk0(errno__espipe,
	    "",
	    return f2__errno__espipe(this_cause));

// ESRCH  "No such process."
f2ptr f2__errno__esrch(f2ptr cause) {
  return f2integer__new(cause, ESRCH);
}
def_pcfunk0(errno__esrch,
	    "",
	    return f2__errno__esrch(this_cause));

// ESTALE "Reserved."
f2ptr f2__errno__estale(f2ptr cause) {
  return f2integer__new(cause, ESTALE);
}
def_pcfunk0(errno__estale,
	    "",
	    return f2__errno__estale(this_cause));

// ETIME  "Stream ioctl() timeout."
f2ptr f2__errno__etime(f2ptr cause) {
  return f2integer__new(cause, ETIME);
}
def_pcfunk0(errno__etime,
	    "",
	    return f2__errno__etime(this_cause));

// ETIMEDOUT "Connection timed out."
f2ptr f2__errno__etimeout(f2ptr cause) {
  return f2integer__new(cause, ETIMEDOUT);
}
def_pcfunk0(errno__etimeout,
	    "",
	    return f2__errno__etimeout(this_cause));

// ETXTBSY "Text file busy."
f2ptr f2__errno__etxtbsy(f2ptr cause) {
  return f2integer__new(cause, ETXTBSY);
}
def_pcfunk0(errno__etxtbsy,
	    "",
	    return f2__errno__etxtbsy(this_cause));

// EWOULDBLOCK "Operation would block (may be the same value as [EAGAIN])."
f2ptr f2__errno__ewouldblock(f2ptr cause) {
  return f2integer__new(cause, EWOULDBLOCK);
}
def_pcfunk0(errno__ewouldblock,
	    "",
	    return f2__errno__ewouldblock(this_cause));

// EXDEV  "Cross-device link."
f2ptr f2__errno__exdev(f2ptr cause) {
  return f2integer__new(cause, EXDEV);
}
def_pcfunk0(errno__exdev,
	    "",
	    return f2__errno__exdev(this_cause));

void f2__primfunks__errno__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(errno__errno);
  
  f2__primcfunk__init__defragment__fix_pointers(errno__e2big);
  f2__primcfunk__init__defragment__fix_pointers(errno__eacces);
  f2__primcfunk__init__defragment__fix_pointers(errno__eaddrinuse);
  f2__primcfunk__init__defragment__fix_pointers(errno__eaddrnotavail);
  f2__primcfunk__init__defragment__fix_pointers(errno__eafnosupport);
  f2__primcfunk__init__defragment__fix_pointers(errno__eagain);
  f2__primcfunk__init__defragment__fix_pointers(errno__ealready);
  f2__primcfunk__init__defragment__fix_pointers(errno__ebadf);
  f2__primcfunk__init__defragment__fix_pointers(errno__ebadmsg);
  f2__primcfunk__init__defragment__fix_pointers(errno__ebusy);
  f2__primcfunk__init__defragment__fix_pointers(errno__ecanceled);
  f2__primcfunk__init__defragment__fix_pointers(errno__echild);
  f2__primcfunk__init__defragment__fix_pointers(errno__econnaborted);
  f2__primcfunk__init__defragment__fix_pointers(errno__econnrefused);
  f2__primcfunk__init__defragment__fix_pointers(errno__econnreset);
  f2__primcfunk__init__defragment__fix_pointers(errno__edeadlk);
  f2__primcfunk__init__defragment__fix_pointers(errno__edestaddrreq);
  f2__primcfunk__init__defragment__fix_pointers(errno__edom);
  f2__primcfunk__init__defragment__fix_pointers(errno__edquot);
  f2__primcfunk__init__defragment__fix_pointers(errno__eexist);
  f2__primcfunk__init__defragment__fix_pointers(errno__efault);
  f2__primcfunk__init__defragment__fix_pointers(errno__efbig);
  f2__primcfunk__init__defragment__fix_pointers(errno__ehostunreach);
  f2__primcfunk__init__defragment__fix_pointers(errno__eidrm);
  f2__primcfunk__init__defragment__fix_pointers(errno__eilseq);
  f2__primcfunk__init__defragment__fix_pointers(errno__einprogress);
  f2__primcfunk__init__defragment__fix_pointers(errno__eintr);
  f2__primcfunk__init__defragment__fix_pointers(errno__einval);
  f2__primcfunk__init__defragment__fix_pointers(errno__eio);
  f2__primcfunk__init__defragment__fix_pointers(errno__eisconn);
  f2__primcfunk__init__defragment__fix_pointers(errno__eisdir);
  f2__primcfunk__init__defragment__fix_pointers(errno__eloop);
  f2__primcfunk__init__defragment__fix_pointers(errno__emfile);
  f2__primcfunk__init__defragment__fix_pointers(errno__emlink);
  f2__primcfunk__init__defragment__fix_pointers(errno__emsgsize);
  f2__primcfunk__init__defragment__fix_pointers(errno__emultihop);
  f2__primcfunk__init__defragment__fix_pointers(errno__enametoolong);
  f2__primcfunk__init__defragment__fix_pointers(errno__enetdown);
  f2__primcfunk__init__defragment__fix_pointers(errno__enetreset);
  f2__primcfunk__init__defragment__fix_pointers(errno__enetunreach);
  f2__primcfunk__init__defragment__fix_pointers(errno__enfile);
  f2__primcfunk__init__defragment__fix_pointers(errno__enobufs);
  f2__primcfunk__init__defragment__fix_pointers(errno__enodata);
  f2__primcfunk__init__defragment__fix_pointers(errno__enodev);
  f2__primcfunk__init__defragment__fix_pointers(errno__enoent);
  f2__primcfunk__init__defragment__fix_pointers(errno__enoexec);
  f2__primcfunk__init__defragment__fix_pointers(errno__enolock);
  f2__primcfunk__init__defragment__fix_pointers(errno__enolink);
  f2__primcfunk__init__defragment__fix_pointers(errno__enomem);
  f2__primcfunk__init__defragment__fix_pointers(errno__enomsg);
  f2__primcfunk__init__defragment__fix_pointers(errno__enoprotoopt);
  f2__primcfunk__init__defragment__fix_pointers(errno__enospc);
  f2__primcfunk__init__defragment__fix_pointers(errno__enosr);
  f2__primcfunk__init__defragment__fix_pointers(errno__enostr);
  f2__primcfunk__init__defragment__fix_pointers(errno__enosys);
  f2__primcfunk__init__defragment__fix_pointers(errno__enotconn);
  f2__primcfunk__init__defragment__fix_pointers(errno__enotdir);
  f2__primcfunk__init__defragment__fix_pointers(errno__enotempty);
  f2__primcfunk__init__defragment__fix_pointers(errno__enotsock);
  f2__primcfunk__init__defragment__fix_pointers(errno__enotsup);
  f2__primcfunk__init__defragment__fix_pointers(errno__enotty);
  f2__primcfunk__init__defragment__fix_pointers(errno__enxio);
  f2__primcfunk__init__defragment__fix_pointers(errno__eopnotsupp);
  f2__primcfunk__init__defragment__fix_pointers(errno__eoverflow);
  f2__primcfunk__init__defragment__fix_pointers(errno__eperm);
  f2__primcfunk__init__defragment__fix_pointers(errno__epipe);
  f2__primcfunk__init__defragment__fix_pointers(errno__eproto);
  f2__primcfunk__init__defragment__fix_pointers(errno__eprotonosupport);
  f2__primcfunk__init__defragment__fix_pointers(errno__eprototype);
  f2__primcfunk__init__defragment__fix_pointers(errno__erange);
  f2__primcfunk__init__defragment__fix_pointers(errno__erofs);
  f2__primcfunk__init__defragment__fix_pointers(errno__espipe);
  f2__primcfunk__init__defragment__fix_pointers(errno__esrch);
  f2__primcfunk__init__defragment__fix_pointers(errno__estale);
  f2__primcfunk__init__defragment__fix_pointers(errno__etime);
  f2__primcfunk__init__defragment__fix_pointers(errno__etimeout);
  f2__primcfunk__init__defragment__fix_pointers(errno__etxtbsy);
  f2__primcfunk__init__defragment__fix_pointers(errno__ewouldblock);
  f2__primcfunk__init__defragment__fix_pointers(errno__exdev);
}

void f2__primfunks__errno__reinitialize_globalvars() {
  f2__primcfunk__init(errno__errno);
  
  f2__primcfunk__init(errno__e2big);
  f2__primcfunk__init(errno__eacces);
  f2__primcfunk__init(errno__eaddrinuse);
  f2__primcfunk__init(errno__eaddrnotavail);
  f2__primcfunk__init(errno__eafnosupport);
  f2__primcfunk__init(errno__eagain);
  f2__primcfunk__init(errno__ealready);
  f2__primcfunk__init(errno__ebadf);
  f2__primcfunk__init(errno__ebadmsg);
  f2__primcfunk__init(errno__ebusy);
  f2__primcfunk__init(errno__ecanceled);
  f2__primcfunk__init(errno__echild);
  f2__primcfunk__init(errno__econnaborted);
  f2__primcfunk__init(errno__econnrefused);
  f2__primcfunk__init(errno__econnreset);
  f2__primcfunk__init(errno__edeadlk);
  f2__primcfunk__init(errno__edestaddrreq);
  f2__primcfunk__init(errno__edom);
  f2__primcfunk__init(errno__edquot);
  f2__primcfunk__init(errno__eexist);
  f2__primcfunk__init(errno__efault);
  f2__primcfunk__init(errno__efbig);
  f2__primcfunk__init(errno__ehostunreach);
  f2__primcfunk__init(errno__eidrm);
  f2__primcfunk__init(errno__eilseq);
  f2__primcfunk__init(errno__einprogress);
  f2__primcfunk__init(errno__eintr);
  f2__primcfunk__init(errno__einval);
  f2__primcfunk__init(errno__eio);
  f2__primcfunk__init(errno__eisconn);
  f2__primcfunk__init(errno__eisdir);
  f2__primcfunk__init(errno__eloop);
  f2__primcfunk__init(errno__emfile);
  f2__primcfunk__init(errno__emlink);
  f2__primcfunk__init(errno__emsgsize);
  f2__primcfunk__init(errno__emultihop);
  f2__primcfunk__init(errno__enametoolong);
  f2__primcfunk__init(errno__enetdown);
  f2__primcfunk__init(errno__enetreset);
  f2__primcfunk__init(errno__enetunreach);
  f2__primcfunk__init(errno__enfile);
  f2__primcfunk__init(errno__enobufs);
  f2__primcfunk__init(errno__enodata);
  f2__primcfunk__init(errno__enodev);
  f2__primcfunk__init(errno__enoent);
  f2__primcfunk__init(errno__enoexec);
  f2__primcfunk__init(errno__enolock);
  f2__primcfunk__init(errno__enolink);
  f2__primcfunk__init(errno__enomem);
  f2__primcfunk__init(errno__enomsg);
  f2__primcfunk__init(errno__enoprotoopt);
  f2__primcfunk__init(errno__enospc);
  f2__primcfunk__init(errno__enosr);
  f2__primcfunk__init(errno__enostr);
  f2__primcfunk__init(errno__enosys);
  f2__primcfunk__init(errno__enotconn);
  f2__primcfunk__init(errno__enotdir);
  f2__primcfunk__init(errno__enotempty);
  f2__primcfunk__init(errno__enotsock);
  f2__primcfunk__init(errno__enotsup);
  f2__primcfunk__init(errno__enotty);
  f2__primcfunk__init(errno__enxio);
  f2__primcfunk__init(errno__eopnotsupp);
  f2__primcfunk__init(errno__eoverflow);
  f2__primcfunk__init(errno__eperm);
  f2__primcfunk__init(errno__epipe);
  f2__primcfunk__init(errno__eproto);
  f2__primcfunk__init(errno__eprotonosupport);
  f2__primcfunk__init(errno__eprototype);
  f2__primcfunk__init(errno__erange);
  f2__primcfunk__init(errno__erofs);
  f2__primcfunk__init(errno__espipe);
  f2__primcfunk__init(errno__esrch);
  f2__primcfunk__init(errno__estale);
  f2__primcfunk__init(errno__etime);
  f2__primcfunk__init(errno__etimeout);
  f2__primcfunk__init(errno__etxtbsy);
  f2__primcfunk__init(errno__ewouldblock);
  f2__primcfunk__init(errno__exdev);
}

void f2__primfunks__errno__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primfunks-errno", "", &f2__primfunks__errno__reinitialize_globalvars, &f2__primfunks__errno__defragment__fix_pointers);
  
  f2__primfunks__errno__reinitialize_globalvars();
}

  

