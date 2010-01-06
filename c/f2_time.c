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

void raw__spin_sleep_yield() {
  sched_yield();
  f2__sleep(100000);
}

void raw__fast_spin_sleep_yield() {
  sched_yield();
  f2__sleep(1000);
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

time_t nanoseconds_since_1970__to_time(u64 nanoseconds_since_1970) {
  return (nanoseconds_since_1970 / nanoseconds_per_second);
}

void nanoseconds_since_1970__to_funk2_date(u64 nanoseconds_since_1970, funk2_date_t* funk2_date) {
  u64    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  u64    nanoseconds            = nanoseconds_since_1970 - (seconds_since_1970 * nanoseconds_per_second);
  time_t unix_time              = nanoseconds_since_1970__to_time(nanoseconds_since_1970) - (4 * 60 * 60);
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

// **

void f2__time__reinitialize_globalvars() {
}

void f2__time__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "time", "", &f2__time__reinitialize_globalvars);
  
  f2__time__reinitialize_globalvars();
  
  f2__primcfunk__init__0(nanoseconds_since_1970, "");
  f2__primcfunk__init__0(processor_thread__execution_nanoseconds, "");
  f2__primcfunk__init__0(funk2__execution_nanoseconds, "");
}

