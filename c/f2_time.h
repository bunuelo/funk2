// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#ifndef F2__TIME__H
#define F2__TIME__H

#include "f2_global.h"
#include "f2_memory.h"
#include "f2_ptypes.h"
#include "f2_primfunks.h"

typedef struct funk2_date_s {
  u64 years;
  u64 months;
  u64 days;
  u64 hours;
  u64 minutes;
  u64 seconds;
  u64 nanoseconds;
} funk2_date_t;

#define nanoseconds_per_second ((s64)1000000000)

//void   f2__sleep(int microseconds);
void   f2__nanosleep(u64 nanoseconds);
void  raw__spin_sleep_yield();
void  raw__fast_spin_sleep_yield();
u64   raw__nanoseconds_since_1970();
f2ptr  f2__nanoseconds_since_1970(f2ptr cause);
void       nanoseconds_since_1970__to_funk2_date(u64 nanoseconds_since_1970, funk2_date_t* funk2_date);
f2ptr raw__time__new_from_unix_time(f2ptr cause, time_t unix_time);

// **

void f2__time__reinitialize_globalvars();
void f2__time__initialize();

#endif // F2__TIME__H
