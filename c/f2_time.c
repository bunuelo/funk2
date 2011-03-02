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

#include "funk2.h"


#ifdef F2__APPLE

// **
// * This copyright notice is for the clock_gettime function below,
// * which is a hack that is needed on Macintosh systems that don't
// * supply these clock functions. --Bo Morgan
//
// Copyright (c), MM Weiss
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
// 1. Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//     
// 2. Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//     
// 3. Neither the name of the MM Weiss nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

typedef enum {
  CLOCK_REALTIME,
  CLOCK_MONOTONIC,
  CLOCK_PROCESS_CPUTIME_ID,
  CLOCK_THREAD_CPUTIME_ID
} clockid_t;

static mach_timebase_info_data_t __clock_gettime_inf;

int clock_gettime(clockid_t clk_id, struct timespec *tp) {
  kern_return_t   ret;
  clock_serv_t    clk;
  clock_id_t      clk_serv_id;
  mach_timespec_t tm;
  
  uint64_t start, end, delta, nano;
  
  int retval = -1;
  switch (clk_id) {
  case CLOCK_REALTIME:
  case CLOCK_MONOTONIC:
    clk_serv_id = clk_id == CLOCK_REALTIME ? CALENDAR_CLOCK : SYSTEM_CLOCK;
    if (KERN_SUCCESS == (ret = host_get_clock_service(mach_host_self(), clk_serv_id, &clk))) {
      if (KERN_SUCCESS == (ret = clock_get_time(clk, &tm))) {
	tp->tv_sec  = tm.tv_sec;
	tp->tv_nsec = tm.tv_nsec;
	retval = 0;
      }
    }
    if (KERN_SUCCESS != ret) {
      errno = EINVAL;
      retval = -1;
    }
    break;
  case CLOCK_PROCESS_CPUTIME_ID:
  case CLOCK_THREAD_CPUTIME_ID:
    start = mach_absolute_time();
    if (clk_id == CLOCK_PROCESS_CPUTIME_ID) {
      getpid();
    } else {
      sched_yield();
    }
    end = mach_absolute_time();
    delta = end - start;	
    if (0 == __clock_gettime_inf.denom) {
      mach_timebase_info(&__clock_gettime_inf);
    }
    nano = delta * __clock_gettime_inf.numer / __clock_gettime_inf.denom;
    tp->tv_sec = nano * 1e-9;  
    tp->tv_nsec = nano - (tp->tv_sec * 1e9);
    retval = 0;
    break;
  default:
    errno = EINVAL;
    retval = -1;
  }
  return retval;
}

#endif // F2__APPLE



void f2__nanosleep(u64 nanoseconds) {
  struct timespec sleepTime;
  struct timespec remainingSleepTime;
  sleepTime.tv_sec  = nanoseconds / nanoseconds_per_second;
  sleepTime.tv_nsec = nanoseconds - ((nanoseconds / nanoseconds_per_second) * nanoseconds_per_second);
  nanosleep(&sleepTime, &remainingSleepTime);
}


//void f2__sleep(int microseconds) {
//  usleep(microseconds);
//}

void raw__spin_sleep_yield() {
  sched_yield();
  //f2__sleep(10000);
  f2__nanosleep(10000);
}

void raw__fast_spin_sleep_yield() {
  sched_yield();
  //f2__sleep(1000);
  //f2__nanosleep(1000);
}

u64 raw__nanoseconds_since_1970() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return (((u64)ts.tv_sec) * nanoseconds_per_second) + ((u64)ts.tv_nsec);
}


f2ptr f2__nanoseconds_since_1970(f2ptr cause) {
  return f2integer__new(cause, raw__nanoseconds_since_1970());
}
def_pcfunk0(nanoseconds_since_1970, return f2__nanoseconds_since_1970(this_cause));

#ifndef F2__CYGWIN
u64 raw__processor_thread__execution_nanoseconds(f2ptr cause) {
  struct timespec ts;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
  return (((u64)ts.tv_sec) * nanoseconds_per_second) + ((u64)ts.tv_nsec);
}

f2ptr f2__processor_thread__execution_nanoseconds(f2ptr cause) {
  return f2integer__new(cause, raw__processor_thread__execution_nanoseconds(cause));
}
def_pcfunk0(processor_thread__execution_nanoseconds, return f2__processor_thread__execution_nanoseconds(this_cause));

u64 raw__funk2__execution_nanoseconds(f2ptr cause) {
  struct timespec ts;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
  return (((u64)ts.tv_sec) * nanoseconds_per_second) + ((u64)ts.tv_nsec);
}

f2ptr f2__funk2__execution_nanoseconds(f2ptr cause) {
  return f2integer__new(cause, raw__funk2__execution_nanoseconds(cause));
}
def_pcfunk0(funk2__execution_nanoseconds, return f2__funk2__execution_nanoseconds(this_cause));
#endif // F2__CYGWIN

time_t nanoseconds_since_1970__to_unix_time(u64 nanoseconds_since_1970) {
  return (nanoseconds_since_1970 / nanoseconds_per_second);
}

u64 unix_time__to_nanoseconds_since_1970(time_t unix_time) {
  return ((u64)unix_time) * nanoseconds_per_second;
}

void nanoseconds_since_1970__to_funk2_date(u64 nanoseconds_since_1970, funk2_date_t* funk2_date) {
  u64    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  u64    nanoseconds            = nanoseconds_since_1970 - (seconds_since_1970 * nanoseconds_per_second);
  time_t unix_time              = nanoseconds_since_1970__to_unix_time(nanoseconds_since_1970);
  struct tm unix_tm;
  gmtime_r(&unix_time, &unix_tm);
  funk2_date->years       = unix_tm.tm_year + 1900;
  funk2_date->months      = unix_tm.tm_mon + 1;
  funk2_date->days        = unix_tm.tm_mday;
  funk2_date->hours       = unix_tm.tm_hour;
  funk2_date->minutes     = unix_tm.tm_min;
  funk2_date->seconds     = unix_tm.tm_sec;
  funk2_date->nanoseconds = nanoseconds;
}

f2ptr raw__time__new_from_unix_time(f2ptr cause, time_t unix_time) {
  u64 nanoseconds_since_1970 = unix_time__to_nanoseconds_since_1970(unix_time);
  return f2__time__new(cause, f2integer__new(cause, nanoseconds_since_1970));
}

// **

void f2__time__reinitialize_globalvars() {
}

void f2__time__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "time", "", &f2__time__reinitialize_globalvars);
  
  f2__time__reinitialize_globalvars();
  
  f2__primcfunk__init__0(nanoseconds_since_1970, "");

#ifndef F2__CYGWIN
  f2__primcfunk__init__0(processor_thread__execution_nanoseconds, "");
  f2__primcfunk__init__0(funk2__execution_nanoseconds, "");
#endif // F2__CYGWIN
}

