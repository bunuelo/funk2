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

f2ptr raw__fcntl(f2ptr cause, f2ptr fd, f2ptr cmd, f2ptr value) {
#if defined(HAVE_FCNTL)
  return f2integer__new(cause, fcntl(f2integer__i(fd, cause), f2integer__i(cmd, cause), f2integer__i(value, cause)));
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-not_compiled_into_this_funk2_build")));
#endif // HAVE_FCNTL
}

f2ptr f2__fcntl(f2ptr cause, f2ptr fd, f2ptr cmd, f2ptr value) {
  assert_argument_type(integer, fd);
  assert_argument_type(integer, cmd);
  assert_argument_type(integer, value);
  return raw__fcntl(cause, fd, cmd, value);
}
def_pcfunk3(fcntl, fd, cmd, value,
	    "",
	    return f2__fcntl(this_cause, fd, cmd, value));

f2ptr raw__fcntl__getfd(f2ptr cause, f2ptr fd, f2ptr value) {
#if defined(HAVE_FCNTL)
  return f2integer__new(cause, fcntl(f2integer__i(fd, cause), F_GETFD, f2integer__i(value, cause)));
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-getfd-not_compiled_into_this_funk2_build")));
#endif // HAVE_FCNTL
}

f2ptr f2__fcntl__getfd(f2ptr cause, f2ptr fd, f2ptr value) {
  assert_argument_type(integer, fd);
  assert_argument_type(integer, value);
  return raw__fcntl__getfd(cause, fd, value);
}
def_pcfunk2(fcntl__getfd, fd, value,
	    "",
	    return f2__fcntl__getfd(this_cause, fd, value));

f2ptr raw__fcntl__setfd(f2ptr cause, f2ptr fd, f2ptr value) {
#if defined(HAVE_FCNTL)
  return f2integer__new(cause, fcntl(f2integer__i(fd, cause), F_SETFD, f2integer__i(value, cause)));
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-setfd-not_compiled_into_this_funk2_build")));
#endif // HAVE_FCNTL
}

f2ptr f2__fcntl__setfd(f2ptr cause, f2ptr fd, f2ptr value) {
  assert_argument_type(integer, fd);
  assert_argument_type(integer, value);
  return raw__fcntl__setfd(cause, fd, value);
}
def_pcfunk2(fcntl__setfd, fd, value,
	    "",
	    return f2__fcntl__setfd(this_cause, fd, value));

f2ptr raw__fcntl__getfl(f2ptr cause, f2ptr fd, f2ptr value) {
#if defined(HAVE_FCNTL)
  return f2integer__new(cause, fcntl(f2integer__i(fd, cause), F_GETFL, f2integer__i(value, cause)));
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-getfl-not_compiled_into_this_funk2_build")));
#endif // HAVE_FCNTL
}

f2ptr f2__fcntl__getfl(f2ptr cause, f2ptr fd, f2ptr value) {
  assert_argument_type(integer, fd);
  assert_argument_type(integer, value);
  return raw__fcntl__getfl(cause, fd, value);
}
def_pcfunk2(fcntl__getfl, fd, value,
	    "",
	    return f2__fcntl__getfl(this_cause, fd, value));

f2ptr raw__fcntl__setfl(f2ptr cause, f2ptr fd, f2ptr value) {
#if defined(HAVE_FCNTL)
  return f2integer__new(cause, fcntl(f2integer__i(fd, cause), F_SETFL, f2integer__i(value, cause)));
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-setfl-not_compiled_into_this_funk2_build")));
#endif // HAVE_FCNTL
}

f2ptr f2__fcntl__setfl(f2ptr cause, f2ptr fd, f2ptr value) {
  assert_argument_type(integer, fd);
  assert_argument_type(integer, value);
  return raw__fcntl__setfl(cause, fd, value);
}
def_pcfunk2(fcntl__setfl, fd, value,
	    "",
	    return f2__fcntl__setfl(this_cause, fd, value));


f2ptr f2__fcntl__f_dupfd(f2ptr cause) {
#if defined(F_DUPFD)
  return f2integer__new(cause, F_DUPFD);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // F_DUPFD
}
def_pcfunk0(fcntl__f_dupfd,
	    "",
	    return f2__fcntl__f_dupfd(this_cause));

f2ptr f2__fcntl__f_getfd(f2ptr cause) {
#if defined(F_GETFD)
  return f2integer__new(cause, F_GETFD);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // F_GETFD
}
def_pcfunk0(fcntl__f_getfd,
	    "",
	    return f2__fcntl__f_getfd(this_cause));

f2ptr f2__fcntl__f_setfd(f2ptr cause) {
#if defined(F_SETFD)
  return f2integer__new(cause, F_SETFD);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // F_SETFD
}
def_pcfunk0(fcntl__f_setfd,
	    "",
	    return f2__fcntl__f_setfd(this_cause));

f2ptr f2__fcntl__f_getfl(f2ptr cause) {
#if defined(F_GETFL)
  return f2integer__new(cause, F_GETFL);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // F_GETFL
}
def_pcfunk0(fcntl__f_getfl,
	    "",
	    return f2__fcntl__f_getfl(this_cause));

f2ptr f2__fcntl__f_setfl(f2ptr cause) {
#if defined(F_SETFL)
  return f2integer__new(cause, F_SETFL);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // F_SETFL
}
def_pcfunk0(fcntl__f_setfl,
	    "",
	    return f2__fcntl__f_setfl(this_cause));

f2ptr f2__fcntl__f_getown(f2ptr cause) {
#if defined(F_GETOWN)
  return f2integer__new(cause, F_GETOWN);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // F_GETOWN
}
def_pcfunk0(fcntl__f_getown,
	    "",
	    return f2__fcntl__f_getown(this_cause));

f2ptr f2__fcntl__f_setown(f2ptr cause) {
#if defined(F_SETOWN)
  return f2integer__new(cause, F_SETOWN);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // F_SETOWN
}
def_pcfunk0(fcntl__f_setown,
	    "",
	    return f2__fcntl__f_setown(this_cause));

f2ptr f2__fcntl__f_getlk(f2ptr cause) {
#if defined(F_GETLK)
  return f2integer__new(cause, F_GETLK);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // F_GETLK
}
def_pcfunk0(fcntl__f_getlk,
	    "",
	    return f2__fcntl__f_getlk(this_cause));

f2ptr f2__fcntl__f_setlk(f2ptr cause) {
#if defined(F_SETLK)
  return f2integer__new(cause, F_SETLK);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // F_SETLK
}
def_pcfunk0(fcntl__f_setlk,
	    "",
	    return f2__fcntl__f_setlk(this_cause));

f2ptr f2__fcntl__f_setlkw(f2ptr cause) {
#if defined(F_SETLKW)
  return f2integer__new(cause, F_SETLKW);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // F_SETLKW
}
def_pcfunk0(fcntl__f_setlkw,
	    "",
	    return f2__fcntl__f_setlkw(this_cause));

f2ptr f2__fcntl__o_append(f2ptr cause) {
#if defined(O_APPEND)
  return f2integer__new(cause, O_APPEND);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_APPEND
}
def_pcfunk0(fcntl__o_append,
	    "",
	    return f2__fcntl__o_append(this_cause));

f2ptr f2__fcntl__o_creat(f2ptr cause) {
#if defined(O_CREAT)
  return f2integer__new(cause, O_CREAT);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_CREAT
}
def_pcfunk0(fcntl__o_creat,
	    "",
	    return f2__fcntl__o_creat(this_cause));

f2ptr f2__fcntl__o_async(f2ptr cause) {
#if defined(O_ASYNC)
  return f2integer__new(cause, O_ASYNC);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_ASYNC
}
def_pcfunk0(fcntl__o_async,
	    "",
	    return f2__fcntl__o_async(this_cause));

f2ptr f2__fcntl__o_direct(f2ptr cause) {
#if defined(O_DIRECT)
  return f2integer__new(cause, O_DIRECT);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_DIRECT
}
def_pcfunk0(fcntl__o_direct,
	    "",
	    return f2__fcntl__o_direct(this_cause));

f2ptr f2__fcntl__o_largefile(f2ptr cause) {
#if defined(O_LARGEFILE)
  return f2integer__new(cause, O_LARGEFILE);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_LARGEFILE
}
def_pcfunk0(fcntl__o_largefile,
	    "",
	    return f2__fcntl__o_largefile(this_cause));

f2ptr f2__fcntl__o_noatime(f2ptr cause) {
#if defined(O_NOATIME)
  return f2integer__new(cause, O_NOATIME);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_NOATIME
}
def_pcfunk0(fcntl__o_noatime,
	    "",
	    return f2__fcntl__o_noatime(this_cause));


f2ptr f2__fcntl__o_directory(f2ptr cause) {
#if defined(O_DIRECTORY)
  return f2integer__new(cause, O_DIRECTORY);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_DIRECTORY
}
def_pcfunk0(fcntl__o_directory,
	    "",
	    return f2__fcntl__o_directory(this_cause));

f2ptr f2__fcntl__o_excl(f2ptr cause) {
#if defined(O_EXCL)
  return f2integer__new(cause, O_EXCL);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_EXCL
}
def_pcfunk0(fcntl__o_excl,
	    "",
	    return f2__fcntl__o_excl(this_cause));

f2ptr f2__fcntl__o_noctty(f2ptr cause) {
#if defined(O_NOCTTY)
  return f2integer__new(cause, O_NOCTTY);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_NOCTTY
}
def_pcfunk0(fcntl__o_noctty,
	    "",
	    return f2__fcntl__o_noctty(this_cause));

f2ptr f2__fcntl__o_nofollow(f2ptr cause) {
#if defined(O_NOFOLLOW)
  return f2integer__new(cause, O_NOFOLLOW);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_NOFOLLOW
}
def_pcfunk0(fcntl__o_nofollow,
	    "",
	    return f2__fcntl__o_nofollow(this_cause));

f2ptr f2__fcntl__o_nonblock(f2ptr cause) {
#if defined(O_NONBLOCK)
  return f2integer__new(cause, O_NONBLOCK);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_NONBLOCK
}
def_pcfunk0(fcntl__o_nonblock,
	    "",
	    return f2__fcntl__o_nonblock(this_cause));

f2ptr f2__fcntl__o_sync(f2ptr cause) {
#if defined(O_SYNC)
  return f2integer__new(cause, O_SYNC);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_SYNC
}
def_pcfunk0(fcntl__o_sync,
	    "",
	    return f2__fcntl__o_sync(this_cause));

f2ptr f2__fcntl__o_trunc(f2ptr cause) {
#if defined(O_TRUNC)
  return f2integer__new(cause, O_TRUNC);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_TRUNC
}
def_pcfunk0(fcntl__o_trunc,
	    "",
	    return f2__fcntl__o_trunc(this_cause));

f2ptr f2__fcntl__o_rdonly(f2ptr cause) {
#if defined(O_RDONLY)
  return f2integer__new(cause, O_RDONLY);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_RDONLY
}
def_pcfunk0(fcntl__o_rdonly,
	    "",
	    return f2__fcntl__o_rdonly(this_cause));

f2ptr f2__fcntl__o_wronly(f2ptr cause) {
#if defined(O_WRONLY)
  return f2integer__new(cause, O_WRONLY);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_WRONLY
}
def_pcfunk0(fcntl__o_wronly,
	    "",
	    return f2__fcntl__o_wronly(this_cause));

f2ptr f2__fcntl__o_rdwr(f2ptr cause) {
#if defined(O_RDWR)
  return f2integer__new(cause, O_RDWR);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "fcntl-constant_not_supported_in_this_funk2_build")));
#endif // O_RDWR
}
def_pcfunk0(fcntl__o_rdwr,
	    "",
	    return f2__fcntl__o_rdwr(this_cause));


// **

void f2__primfunks__fcntl__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(fcntl);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__getfd);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__setfd);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__getfl);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__setfl);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__f_dupfd);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__f_getfd);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__f_setfd);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__f_getfl);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__f_setfl);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__f_getown);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__f_setown);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__f_getlk);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__f_setlk);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__f_setlkw);
  
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_append);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_creat);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_async);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_direct);	
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_largefile);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_noatime);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_directory);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_excl);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_noctty);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_nofollow);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_nonblock);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_sync);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_trunc);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_rdonly);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_wronly);
  f2__primcfunk__init__defragment__fix_pointers(fcntl__o_rdwr);
}

void f2__primfunks__fcntl__reinitialize_globalvars() {
  f2__primcfunk__init(fcntl);
  f2__primcfunk__init(fcntl__getfd);
  f2__primcfunk__init(fcntl__setfd);
  f2__primcfunk__init(fcntl__getfl);
  f2__primcfunk__init(fcntl__setfl);
  f2__primcfunk__init(fcntl__f_dupfd);
  f2__primcfunk__init(fcntl__f_getfd);
  f2__primcfunk__init(fcntl__f_setfd);
  f2__primcfunk__init(fcntl__f_getfl);
  f2__primcfunk__init(fcntl__f_setfl);
  f2__primcfunk__init(fcntl__f_getown);
  f2__primcfunk__init(fcntl__f_setown);
  f2__primcfunk__init(fcntl__f_getlk);
  f2__primcfunk__init(fcntl__f_setlk);
  f2__primcfunk__init(fcntl__f_setlkw);
  
  f2__primcfunk__init(fcntl__o_append);
  f2__primcfunk__init(fcntl__o_creat);
  f2__primcfunk__init(fcntl__o_async);
  f2__primcfunk__init(fcntl__o_direct);	
  f2__primcfunk__init(fcntl__o_largefile);
  f2__primcfunk__init(fcntl__o_noatime);
  f2__primcfunk__init(fcntl__o_directory);
  f2__primcfunk__init(fcntl__o_excl);
  f2__primcfunk__init(fcntl__o_noctty);
  f2__primcfunk__init(fcntl__o_nofollow);
  f2__primcfunk__init(fcntl__o_nonblock);
  f2__primcfunk__init(fcntl__o_sync);
  f2__primcfunk__init(fcntl__o_trunc);
  f2__primcfunk__init(fcntl__o_rdonly);
  f2__primcfunk__init(fcntl__o_wronly);
  f2__primcfunk__init(fcntl__o_rdwr);
}

void f2__primfunks__fcntl__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primfunks-fcntl", "", &f2__primfunks__fcntl__reinitialize_globalvars, &f2__primfunks__fcntl__defragment__fix_pointers);
  
  f2__primfunks__fcntl__reinitialize_globalvars();
}

  

