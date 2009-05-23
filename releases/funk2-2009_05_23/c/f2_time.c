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

void f2__sleep(int microseconds) {
  usleep(microseconds);
}

u64 raw__system_microseconds_since_1970() {
  struct timeval tv;
  if(gettimeofday(&tv, NULL)) {printf("\nsystem_microseconds_since_1970 error: returning nil."); return 0;}
  return ((((u64)tv.tv_sec) * 1000000) + ((u64)tv.tv_usec));
}

f2ptr f2__system_microseconds_since_1970(f2ptr cause) {
  return f2integer__new(cause, raw__system_microseconds_since_1970());
}

