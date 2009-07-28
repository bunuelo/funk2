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

//#define __USE_GNU
//#define __USE_LARGEFILE64
//#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>

f2ptr f2__fcntl(f2ptr cause, f2ptr fd, f2ptr cmd, f2ptr value) {return f2integer__new(cause, fcntl(f2integer__i(fd, cause), f2integer__i(cmd, cause), f2integer__i(value, cause)));}
def_pcfunk3(f2__fcntl, fd, cmd, value, return f2__fcntl(this_cause, fd, cmd, value));

f2ptr f2__fcntl__getfd(f2ptr cause, f2ptr fd, f2ptr value) {return f2integer__new(cause, fcntl(f2integer__i(fd, cause), F_GETFD, f2integer__i(value, cause)));}
def_pcfunk2(f2__fcntl__getfd, fd, value, return f2__fcntl__getfd(this_cause, fd, value));

f2ptr f2__fcntl__setfd(f2ptr cause, f2ptr fd, f2ptr value) {return f2integer__new(cause, fcntl(f2integer__i(fd, cause), F_SETFD, f2integer__i(value, cause)));}
def_pcfunk2(f2__fcntl__setfd, fd, value, return f2__fcntl__setfd(this_cause, fd, value));

f2ptr f2__fcntl__getfl(f2ptr cause, f2ptr fd, f2ptr value) {return f2integer__new(cause, fcntl(f2integer__i(fd, cause), F_GETFL, f2integer__i(value, cause)));}
def_pcfunk2(f2__fcntl__getfl, fd, value, return f2__fcntl__getfl(this_cause, fd, value));

f2ptr f2__fcntl__setfl(f2ptr cause, f2ptr fd, f2ptr value) {return f2integer__new(cause, fcntl(f2integer__i(fd, cause), F_SETFL, f2integer__i(value, cause)));}
def_pcfunk2(f2__fcntl__setfl, fd, value, return f2__fcntl__setfl(this_cause, fd, value));


f2ptr f2__fcntl__f_dupfd(f2ptr cause)  {return f2integer__new(cause, F_DUPFD);}  def_pcfunk0(f2__fcntl__f_dupfd,  return f2__fcntl__f_dupfd(this_cause));
f2ptr f2__fcntl__f_getfd(f2ptr cause)  {return f2integer__new(cause, F_GETFD);}  def_pcfunk0(f2__fcntl__f_getfd,  return f2__fcntl__f_getfd(this_cause));
f2ptr f2__fcntl__f_setfd(f2ptr cause)  {return f2integer__new(cause, F_SETFD);}  def_pcfunk0(f2__fcntl__f_setfd,  return f2__fcntl__f_setfd(this_cause));
f2ptr f2__fcntl__f_getfl(f2ptr cause)  {return f2integer__new(cause, F_GETFL);}  def_pcfunk0(f2__fcntl__f_getfl,  return f2__fcntl__f_getfl(this_cause));
f2ptr f2__fcntl__f_setfl(f2ptr cause)  {return f2integer__new(cause, F_SETFL);}  def_pcfunk0(f2__fcntl__f_setfl,  return f2__fcntl__f_setfl(this_cause));
f2ptr f2__fcntl__f_getown(f2ptr cause) {return f2integer__new(cause, F_GETOWN);} def_pcfunk0(f2__fcntl__f_getown, return f2__fcntl__f_getown(this_cause));
f2ptr f2__fcntl__f_setown(f2ptr cause) {return f2integer__new(cause, F_SETOWN);} def_pcfunk0(f2__fcntl__f_setown, return f2__fcntl__f_setown(this_cause));
f2ptr f2__fcntl__f_getlk(f2ptr cause)  {return f2integer__new(cause, F_GETLK);}  def_pcfunk0(f2__fcntl__f_getlk,  return f2__fcntl__f_getlk(this_cause));
f2ptr f2__fcntl__f_setlk(f2ptr cause)  {return f2integer__new(cause, F_SETLK);}  def_pcfunk0(f2__fcntl__f_setlk,  return f2__fcntl__f_setlk(this_cause));
f2ptr f2__fcntl__f_setlkw(f2ptr cause) {return f2integer__new(cause, F_SETLKW);} def_pcfunk0(f2__fcntl__f_setlkw, return f2__fcntl__f_setlkw(this_cause));

f2ptr f2__fcntl__o_append(f2ptr cause)    {return f2integer__new(cause, O_APPEND);}    def_pcfunk0(f2__fcntl__o_append,    return f2__fcntl__o_append(this_cause));
f2ptr f2__fcntl__o_async(f2ptr cause)     {return f2integer__new(cause, O_ASYNC);}     def_pcfunk0(f2__fcntl__o_async,     return f2__fcntl__o_async(this_cause));
f2ptr f2__fcntl__o_creat(f2ptr cause)     {return f2integer__new(cause, O_CREAT);}     def_pcfunk0(f2__fcntl__o_creat,     return f2__fcntl__o_creat(this_cause));

#ifdef __APPLE__

#else
f2ptr f2__fcntl__o_direct(f2ptr cause)    {return f2integer__new(cause, O_DIRECT);}    def_pcfunk0(f2__fcntl__o_direct,    return f2__fcntl__o_direct(this_cause));
f2ptr f2__fcntl__o_largefile(f2ptr cause) {return f2integer__new(cause, O_LARGEFILE);} def_pcfunk0(f2__fcntl__o_largefile, return f2__fcntl__o_largefile(this_cause));
f2ptr f2__fcntl__o_noatime(f2ptr cause)   {return f2integer__new(cause, O_NOATIME);}   def_pcfunk0(f2__fcntl__o_noatime,   return f2__fcntl__o_noatime(this_cause));
#endif

f2ptr f2__fcntl__o_directory(f2ptr cause) {return f2integer__new(cause, O_DIRECTORY);} def_pcfunk0(f2__fcntl__o_directory, return f2__fcntl__o_directory(this_cause));
f2ptr f2__fcntl__o_excl(f2ptr cause)      {return f2integer__new(cause, O_EXCL);}      def_pcfunk0(f2__fcntl__o_excl,      return f2__fcntl__o_excl(this_cause));
f2ptr f2__fcntl__o_noctty(f2ptr cause)    {return f2integer__new(cause, O_NOCTTY);}    def_pcfunk0(f2__fcntl__o_noctty,    return f2__fcntl__o_noctty(this_cause));
f2ptr f2__fcntl__o_nofollow(f2ptr cause)  {return f2integer__new(cause, O_NOFOLLOW);}  def_pcfunk0(f2__fcntl__o_nofollow,  return f2__fcntl__o_nofollow(this_cause));
f2ptr f2__fcntl__o_nonblock(f2ptr cause)  {return f2integer__new(cause, O_NONBLOCK);}  def_pcfunk0(f2__fcntl__o_nonblock,  return f2__fcntl__o_nonblock(this_cause));
f2ptr f2__fcntl__o_sync(f2ptr cause)      {return f2integer__new(cause, O_SYNC);}      def_pcfunk0(f2__fcntl__o_sync,      return f2__fcntl__o_sync(this_cause));
f2ptr f2__fcntl__o_trunc(f2ptr cause)     {return f2integer__new(cause, O_TRUNC);}     def_pcfunk0(f2__fcntl__o_trunc,     return f2__fcntl__o_trunc(this_cause));
f2ptr f2__fcntl__o_rdonly(f2ptr cause)    {return f2integer__new(cause, O_RDONLY);}    def_pcfunk0(f2__fcntl__o_rdonly,    return f2__fcntl__o_rdonly(this_cause));
f2ptr f2__fcntl__o_wronly(f2ptr cause)    {return f2integer__new(cause, O_WRONLY);}    def_pcfunk0(f2__fcntl__o_wronly,    return f2__fcntl__o_wronly(this_cause));
f2ptr f2__fcntl__o_rdwr(f2ptr cause)      {return f2integer__new(cause, O_RDWR);}      def_pcfunk0(f2__fcntl__o_rdwr,      return f2__fcntl__o_rdwr(this_cause));


void f2__primfunks__fcntl__reinitialize_globalvars() {
  //f2ptr cause = f2_primfunks__fcntl_c__cause__new(initial_cause(), nil, nil);
}

void f2__primfunks__fcntl__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primfunks__fcntl", "", &f2__primfunks__fcntl__reinitialize_globalvars);
  
  f2__primfunks__fcntl__reinitialize_globalvars();
  
  f2__primcfunk__init(f2__fcntl, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__getfd, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__setfd, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__getfl, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__setfl, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__f_dupfd, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__f_getfd, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__f_setfd, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__f_getfl, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__f_setfl, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__f_getown, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__f_setown, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__f_getlk, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__f_setlk, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__f_setlkw, "(as defined in fcntl.h)");
  
  f2__primcfunk__init(f2__fcntl__o_append, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_async, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_creat, "(as defined in fcntl.h)");

#ifdef __APPLE__

#else
  f2__primcfunk__init(f2__fcntl__o_direct, "(as defined in fcntl.h)");	
  f2__primcfunk__init(f2__fcntl__o_largefile, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_noatime, "(as defined in fcntl.h)");
#endif

  f2__primcfunk__init(f2__fcntl__o_directory, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_excl, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_noctty, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_nofollow, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_nonblock, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_sync, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_trunc, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_rdonly, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_wronly, "(as defined in fcntl.h)");
  f2__primcfunk__init(f2__fcntl__o_rdwr, "(as defined in fcntl.h)");
}

  

