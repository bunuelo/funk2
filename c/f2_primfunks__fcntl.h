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

#ifndef F2__PRIMFUNKS__FCNTL__H
#define F2__PRIMFUNKS__FCNTL__H

#include "f2_primfunks.h"

f2ptr f2__fcntl(f2ptr cause, f2ptr fd, f2ptr cmd, f2ptr value);
f2ptr f2__fcntl__getfd(f2ptr cause, f2ptr fd, f2ptr value);
f2ptr f2__fcntl__setfd(f2ptr cause, f2ptr fd, f2ptr value);
f2ptr f2__fcntl__getfl(f2ptr cause, f2ptr fd, f2ptr value);
f2ptr f2__fcntl__setfl(f2ptr cause, f2ptr fd, f2ptr value);

f2ptr f2__fcntl__f_dupfd(f2ptr cause);
f2ptr f2__fcntl__f_getfd(f2ptr cause);
f2ptr f2__fcntl__f_setfd(f2ptr cause);
f2ptr f2__fcntl__f_getfl(f2ptr cause);
f2ptr f2__fcntl__f_setfl(f2ptr cause);
f2ptr f2__fcntl__f_getown(f2ptr cause);
f2ptr f2__fcntl__f_setown(f2ptr cause);
f2ptr f2__fcntl__f_getlk(f2ptr cause);
f2ptr f2__fcntl__f_setlk(f2ptr cause);
f2ptr f2__fcntl__f_setlkw(f2ptr cause);

f2ptr f2__fcntl__o_append(f2ptr cause);
f2ptr f2__fcntl__o_async(f2ptr cause);
f2ptr f2__fcntl__o_creat(f2ptr cause);
f2ptr f2__fcntl__o_direct(f2ptr cause);
f2ptr f2__fcntl__o_directory(f2ptr cause);
f2ptr f2__fcntl__o_excl(f2ptr cause);
f2ptr f2__fcntl__o_largefile(f2ptr cause);
f2ptr f2__fcntl__o_noatime(f2ptr cause);
f2ptr f2__fcntl__o_noctty(f2ptr cause);
f2ptr f2__fcntl__o_nofollow(f2ptr cause);
f2ptr f2__fcntl__o_nonblock(f2ptr cause);
f2ptr f2__fcntl__o_sync(f2ptr cause);
f2ptr f2__fcntl__o_trunc(f2ptr cause);
f2ptr f2__fcntl__o_rdonly(f2ptr cause);
f2ptr f2__fcntl__o_wronly(f2ptr cause);
f2ptr f2__fcntl__o_rdwr(f2ptr cause);

extern void f2__primfunks__fcntl__reinitialize_globalvars();
extern void f2__primfunks__fcntl__initialize();

#endif // F2__PRIMFUNKS__FCNTL__H

