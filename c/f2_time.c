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
  f2__nanosleep(deep_sleep_nanoseconds);
}

void raw__fast_spin_sleep_yield() {
  sched_yield();
}

void raw__user_spin_sleep_yield() {
  funk2_user_thread_controller__user_check_wait_politely(&(__funk2.user_thread_controller));
  raw__spin_sleep_yield();
}
    
void raw__user_fast_spin_sleep_yield() {
  funk2_user_thread_controller__user_check_wait_politely(&(__funk2.user_thread_controller));
  raw__fast_spin_sleep_yield();
}
    

u64 raw__nanoseconds_since_1970() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return (((u64)ts.tv_sec) * nanoseconds_per_second) + ((u64)ts.tv_nsec);
}


f2ptr f2__nanoseconds_since_1970(f2ptr cause) {
  return f2integer__new(cause, raw__nanoseconds_since_1970());
}
def_pcfunk0(nanoseconds_since_1970,
	    "",
	    return f2__nanoseconds_since_1970(this_cause));

#ifndef F2__CYGWIN
u64 raw__processor_thread__execution_nanoseconds(f2ptr cause) {
  struct timespec ts;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
  return (((u64)ts.tv_sec) * nanoseconds_per_second) + ((u64)ts.tv_nsec);
}

f2ptr f2__processor_thread__execution_nanoseconds(f2ptr cause) {
  return f2integer__new(cause, raw__processor_thread__execution_nanoseconds(cause));
}
def_pcfunk0(processor_thread__execution_nanoseconds,
	    "",
	    return f2__processor_thread__execution_nanoseconds(this_cause));

u64 raw__funk2__execution_nanoseconds(f2ptr cause) {
  struct timespec ts;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
  return (((u64)ts.tv_sec) * nanoseconds_per_second) + ((u64)ts.tv_nsec);
}

f2ptr f2__funk2__execution_nanoseconds(f2ptr cause) {
  return f2integer__new(cause, raw__funk2__execution_nanoseconds(cause));
}
def_pcfunk0(funk2__execution_nanoseconds,
	    "",
	    return f2__funk2__execution_nanoseconds(this_cause));
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



// time

def_primobject_1_slot(time, nanoseconds_since_1970);

f2ptr f2__time__new(f2ptr cause, f2ptr nanoseconds_since_1970) {return f2time__new(cause, nanoseconds_since_1970);}
def_pcfunk1(time__new, nanoseconds_since_1970,
	    "",
	    return f2__time__new(this_cause, nanoseconds_since_1970));

boolean_t raw__time__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__time__is_type(cause, that)) {
    return boolean__false;
  }
  return raw__eq(cause, f2__time__nanoseconds_since_1970(cause, this), f2__time__nanoseconds_since_1970(cause, that));
}

f2ptr f2__time__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(time, this);
  return f2bool__new(raw__time__equals(cause, this, that));
}
def_pcfunk2(time__equals, this, that,
	    "The time represented by this and that time object are the same even if the objects themselves are different objects., """,
	    return f2__time__equals(this_cause, this, that));

u64 raw__time__years(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.years;
}

f2ptr f2__time__years(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__years(cause, this));}
def_pcfunk1(time__years, this,
	    "The number of years since the monk Dionysius Exiguus thought Jesus Christ was born.",
	    return f2__time__years(this_cause, this));

u64 raw__time__months(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.months;
}

f2ptr f2__time__months(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__months(cause, this));}
def_pcfunk1(time__months, this,
	    "The number of months since the beginning of the year.",
	    return f2__time__months(this_cause, this));

u64 raw__time__days(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.days;
}

f2ptr f2__time__days(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__days(cause, this));}
def_pcfunk1(time__days, this,
	    "The number of days since the beginning of the month.",
	    return f2__time__days(this_cause, this));

u64 raw__time__hours(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.hours;
}

f2ptr f2__time__hours(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__hours(cause, this));}
def_pcfunk1(time__hours, this,
	    "The number of hours since the beginning of the day.",
	    return f2__time__hours(this_cause, this));

u64 raw__time__minutes(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.minutes;
}

f2ptr f2__time__minutes(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__minutes(cause, this));}
def_pcfunk1(time__minutes, this,
	    "The number of minutes since the beginning of the hour.",
	    return f2__time__minutes(this_cause, this));

u64 raw__time__seconds(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.seconds;
}

f2ptr f2__time__seconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__seconds(cause, this));}
def_pcfunk1(time__seconds, this,
	    "The number of seconds since the beginning of the minute.",
	    return f2__time__seconds(this_cause, this));

u64 raw__time__milliseconds(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  u64 milliseconds = funk2_date.nanoseconds / nanoseconds_per_millisecond;
  return milliseconds;
}

f2ptr f2__time__milliseconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__milliseconds(cause, this));}
def_pcfunk1(time__milliseconds, this,
	    "The number of milliseconds since the beginning of the second.",
	    return f2__time__milliseconds(this_cause, this));

u64 raw__time__microseconds(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  u64 milliseconds = funk2_date.nanoseconds / nanoseconds_per_millisecond;
  u64 microseconds = (funk2_date.nanoseconds - (milliseconds * nanoseconds_per_millisecond)) / nanoseconds_per_microsecond;
  return microseconds;
}

f2ptr f2__time__microseconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__microseconds(cause, this));}
def_pcfunk1(time__microseconds, this,
	    "The number of microseconds since the beginning of the second.",
	    return f2__time__microseconds(this_cause, this));

u64 raw__time__nanoseconds(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  u64 microseconds = funk2_date.nanoseconds / nanoseconds_per_microsecond;
  u64 nanoseconds  = funk2_date.nanoseconds - (microseconds * nanoseconds_per_microsecond);
  return nanoseconds;
}

f2ptr f2__time__nanoseconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__nanoseconds(cause, this));}
def_pcfunk1(time__nanoseconds, this,
	    "The number of nanoseconds since the beginning of the second.",
	    return f2__time__nanoseconds(this_cause, this));

f2ptr raw__time__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, this);
  f2ptr that__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, that);
  s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
  s64   that__nanoseconds_since_1970__i = f2integer__i(that__nanoseconds_since_1970, cause);
  if (this__nanoseconds_since_1970__i < that__nanoseconds_since_1970__i) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__time__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(time, this);
  assert_argument_type(time, that);
  return f2bool__new(raw__time__is_less_than(cause, this, that));
}
def_pcfunk2(time__is_less_than, this, that,
	    "Returns t if this time is further in the past than that time.",
	    return f2__time__is_less_than(this_cause, this, that));

f2ptr raw__time__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, this);
  f2ptr that__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, that);
  s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
  s64   that__nanoseconds_since_1970__i = f2integer__i(that__nanoseconds_since_1970, cause);
  if (this__nanoseconds_since_1970__i > that__nanoseconds_since_1970__i) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__time__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(time, this);
  assert_argument_type(time, that);
  return f2bool__new(raw__time__is_greater_than(cause, this, that));
}
def_pcfunk2(time__is_greater_than, this, that,
	    "Returns t if this time is further in the future than that time.",
	    return f2__time__is_greater_than(this_cause, this, that));


f2ptr raw__time__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, this);
  f2ptr that__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, that);
  s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
  s64   that__nanoseconds_since_1970__i = f2integer__i(that__nanoseconds_since_1970, cause);
  if (this__nanoseconds_since_1970__i == that__nanoseconds_since_1970__i) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__time__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(time, this);
  assert_argument_type(time, that);
  return f2bool__new(raw__time__is_numerically_equal_to(cause, this, that));
}
def_pcfunk2(time__is_numerically_equal_to, this, that,
	    "Returns t if the nanoseconds_since_1970 of this time is numerically equal to those of that time.",
	    return f2__time__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__time__minus(f2ptr cause, f2ptr this, f2ptr that) {
  if (raw__time__is_type(cause, that)) {
    f2ptr this__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, this);
    f2ptr that__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, that);
    s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
    s64   that__nanoseconds_since_1970__i = f2integer__i(that__nanoseconds_since_1970, cause);
    return f2__relative_time__new(cause, f2integer__new(cause, this__nanoseconds_since_1970__i - that__nanoseconds_since_1970__i));
  } else if (raw__relative_time__is_type(cause, that)) {
    f2ptr this__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, this);
    f2ptr that__total_nanoseconds         = f2__relative_time__total_nanoseconds(cause, that);
    s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
    s64   that__total_nanoseconds__i      = f2integer__i(that__total_nanoseconds, cause);
    return f2__time__new(cause, f2integer__new(cause, this__nanoseconds_since_1970__i - that__total_nanoseconds__i));
  } else {
    return f2larva__new(cause, 34626, nil);
  }
}

f2ptr f2__time__minus(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(time, this);
  return raw__time__minus(cause, this, that);
}
def_pcfunk2(time__minus, this, that,
	    "Returns a new relative_time object that represents the difference between this and that time.",
	    return f2__time__minus(this_cause, this, that));


f2ptr raw__time__plus(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, this);
  f2ptr that__total_nanoseconds         = f2__relative_time__total_nanoseconds(cause, that);
  s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
  s64   that__total_nanoseconds__i      = f2integer__i(that__total_nanoseconds, cause);
  return f2__time__new(cause, f2integer__new(cause, this__nanoseconds_since_1970__i + that__total_nanoseconds__i));
}

f2ptr f2__time__plus(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(time,          this);
  assert_argument_type(relative_time, that);
  return raw__time__plus(cause, this, that);
}
def_pcfunk2(time__plus, this, that,
	    "Returns a new time object that represents the addition of that relative_time to this time.",
	    return f2__time__plus(this_cause, this, that));


f2ptr raw__time__abbreviated_weekday_name(f2ptr cause, f2ptr this) {
  struct tm local_time_info;
  s64       nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  time_t    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  char      time_string[1024];
  localtime_r(&seconds_since_1970, &local_time_info);
  strftime(time_string, 1023, "%a", &local_time_info);
  time_string[1023] = 0;
  return new__string(cause, time_string);
}

f2ptr f2__time__abbreviated_weekday_name(f2ptr cause, f2ptr this) {
  assert_argument_type(time, this);
  return raw__time__abbreviated_weekday_name(cause, this);
}
def_pcfunk1(time__abbreviated_weekday_name, this,
	    "Returns the abbreviated weekday name according to the current locale.",
	    return f2__time__abbreviated_weekday_name(this_cause, this));


f2ptr raw__time__weekday_name(f2ptr cause, f2ptr this) {
  struct tm local_time_info;
  s64       nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  time_t    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  char      time_string[1024];
  localtime_r(&seconds_since_1970, &local_time_info);
  strftime(time_string, 1023, "%A", &local_time_info);
  time_string[1023] = 0;
  return new__string(cause, time_string);
}

f2ptr f2__time__weekday_name(f2ptr cause, f2ptr this) {
  assert_argument_type(time, this);
  return raw__time__weekday_name(cause, this);
}
def_pcfunk1(time__weekday_name, this,
	    "Returns the full weekday name according to the current locale.",
	    return f2__time__weekday_name(this_cause, this));


f2ptr raw__time__abbreviated_month_name(f2ptr cause, f2ptr this) {
  struct tm local_time_info;
  s64       nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  time_t    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  char      time_string[1024];
  localtime_r(&seconds_since_1970, &local_time_info);
  strftime(time_string, 1023, "%b", &local_time_info);
  time_string[1023] = 0;
  return new__string(cause, time_string);
}

f2ptr f2__time__abbreviated_month_name(f2ptr cause, f2ptr this) {
  assert_argument_type(time, this);
  return raw__time__abbreviated_month_name(cause, this);
}
def_pcfunk1(time__abbreviated_month_name, this,
	    "Returns the abbreviated month name according to the current locale.",
	    return f2__time__abbreviated_month_name(this_cause, this));


f2ptr raw__time__month_name(f2ptr cause, f2ptr this) {
  struct tm local_time_info;
  s64       nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  time_t    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  char      time_string[1024];
  localtime_r(&seconds_since_1970, &local_time_info);
  strftime(time_string, 1023, "%B", &local_time_info);
  time_string[1023] = 0;
  return new__string(cause, time_string);
}

f2ptr f2__time__month_name(f2ptr cause, f2ptr this) {
  assert_argument_type(time, this);
  return raw__time__month_name(cause, this);
}
def_pcfunk1(time__month_name, this,
	    "Returns the full month name according to the current locale.",
	    return f2__time__month_name(this_cause, this));


f2ptr raw__time__date_and_time_string(f2ptr cause, f2ptr this) {
  struct tm local_time_info;
  s64       nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  time_t    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  char      time_string[1024];
  localtime_r(&seconds_since_1970, &local_time_info);
  strftime(time_string, 1023, "%c", &local_time_info);
  time_string[1023] = 0;
  return new__string(cause, time_string);
}

f2ptr f2__time__date_and_time_string(f2ptr cause, f2ptr this) {
  assert_argument_type(time, this);
  return raw__time__date_and_time_string(cause, this);
}
def_pcfunk1(time__date_and_time_string, this,
	    "Returns the preferred date and time representation for the current locale.",
	    return f2__time__date_and_time_string(this_cause, this));


f2ptr raw__time__day_of_week(f2ptr cause, f2ptr this) {
  struct tm local_time_info;
  s64       nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  time_t    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  localtime_r(&seconds_since_1970, &local_time_info);
  return f2integer__new(cause, local_time_info.tm_wday);
}

f2ptr f2__time__day_of_week(f2ptr cause, f2ptr this) {
  assert_argument_type(time, this);
  return raw__time__day_of_week(cause, this);
}
def_pcfunk1(time__day_of_week, this,
	    "Returns the number of the days of the week since Sunday (0 - 6).",
	    return f2__time__day_of_week(this_cause, this));


f2ptr raw__time__day_of_year(f2ptr cause, f2ptr this) {
  struct tm local_time_info;
  s64       nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  time_t    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  localtime_r(&seconds_since_1970, &local_time_info);
  return f2integer__new(cause, local_time_info.tm_yday);
}

f2ptr f2__time__day_of_year(f2ptr cause, f2ptr this) {
  assert_argument_type(time, this);
  return raw__time__day_of_year(cause, this);
}
def_pcfunk1(time__day_of_year, this,
	    "Returns the number of the days into the year (0 - 365).",
	    return f2__time__day_of_year(this_cause, this));


f2ptr raw__time__is_daylight_savings_time(f2ptr cause, f2ptr this) {
  struct tm local_time_info;
  s64       nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  time_t    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  localtime_r(&seconds_since_1970, &local_time_info);
  return f2bool__new(local_time_info.tm_isdst);
}

f2ptr f2__time__is_daylight_savings_time(f2ptr cause, f2ptr this) {
  assert_argument_type(time, this);
  return raw__time__is_daylight_savings_time(cause, this);
}
def_pcfunk1(time__is_daylight_savings_time, this,
	    "Returns a boolean depicting whether or not the time is daylight savings or not.",
	    return f2__time__is_daylight_savings_time(this_cause, this));


f2ptr raw__time__timezone(f2ptr cause, f2ptr this) {
  struct tm local_time_info;
  s64       nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  time_t    seconds_since_1970     = nanoseconds_since_1970 / nanoseconds_per_second;
  char      time_string[1024];
  localtime_r(&seconds_since_1970, &local_time_info);
  strftime(time_string, 1023, "%Z", &local_time_info);
  time_string[1023] = 0;
  return new__string(cause, time_string);
}

f2ptr f2__time__timezone(f2ptr cause, f2ptr this) {
  assert_argument_type(time, this);
  return raw__time__timezone(cause, this);
}
def_pcfunk1(time__timezone, this,
	    "Returns the timezone or name or abbreviation.",
	    return f2__time__timezone(this_cause, this));



//       %Z     

//       %+     The date and time in date(1) format. (TZ) (Not supported in glibc2.)


f2ptr raw__time__as__graphviz_label(f2ptr cause, f2ptr this) {
  return raw__time__date_and_time_string(cause, this);
}

f2ptr f2__time__as__graphviz_label(f2ptr cause, f2ptr this) {
  assert_argument_type(time, this);
  return raw__time__as__graphviz_label(cause, this);
}
def_pcfunk1(time__as__graphviz_label, this,
	    "Returns a string representation of this time for rendering in graphviz.",
	    return f2__time__as__graphviz_label(this_cause, this));


f2ptr raw__time__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list22__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "time"),
						new__symbol(cause, "print_object_slot_order"), f2list9__new(cause,
													    new__symbol(cause, "years"),
													    new__symbol(cause, "months"),
													    new__symbol(cause, "days"),
													    new__symbol(cause, "hours"),
													    new__symbol(cause, "minutes"),
													    new__symbol(cause, "seconds"),
													    new__symbol(cause, "milliseconds"),
													    new__symbol(cause, "microseconds"),
													    new__symbol(cause, "nanoseconds")),
						new__symbol(cause, "years"),        f2__time__years(       cause, this),
						new__symbol(cause, "months"),       f2__time__months(      cause, this),
						new__symbol(cause, "days"),         f2__time__days(        cause, this),
						new__symbol(cause, "hours"),        f2__time__hours(       cause, this),
						new__symbol(cause, "minutes"),      f2__time__minutes(     cause, this),
						new__symbol(cause, "seconds"),      f2__time__seconds(     cause, this),
						new__symbol(cause, "milliseconds"), f2__time__milliseconds(cause, this),
						new__symbol(cause, "microseconds"), f2__time__microseconds(cause, this),
						new__symbol(cause, "nanoseconds"),  f2__time__nanoseconds( cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__time__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(time,                 this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__time__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(time__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__time__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2time__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2time__primobject_type__new(cause);
  {char* slot_name = "equals";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.equals__funk);}
  {char* slot_name = "years";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.years__funk);}
  {char* slot_name = "months";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.months__funk);}
  {char* slot_name = "days";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.days__funk);}
  {char* slot_name = "hours";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.hours__funk);}
  {char* slot_name = "minutes";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.minutes__funk);}
  {char* slot_name = "seconds";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.seconds__funk);}
  {char* slot_name = "milliseconds";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.milliseconds__funk);}
  {char* slot_name = "microseconds";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.microseconds__funk);}
  {char* slot_name = "nanoseconds";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds__funk);}
  {char* slot_name = "is_less_than";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.is_less_than__funk);}
  {char* slot_name = "is_greater_than";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.is_greater_than__funk);}
  {char* slot_name = "is_numerically_equal_to";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.is_numerically_equal_to__funk);}
  {char* slot_name = "minus";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.minus__funk);}
  {char* slot_name = "plus";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.plus__funk);}
  {char* slot_name = "abbreviated_weekday_name";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.abbreviated_weekday_name__funk);}
  {char* slot_name = "weekday_name";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.weekday_name__funk);}
  {char* slot_name = "abbreviated_month_name";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.abbreviated_month_name__funk);}
  {char* slot_name = "month_name";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.month_name__funk);}
  {char* slot_name = "date_and_time_string";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.date_and_time_string__funk);}
  {char* slot_name = "day_of_week";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.day_of_week__funk);}
  {char* slot_name = "day_of_year";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.day_of_year__funk);}
  {char* slot_name = "is_daylight_savings_time";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.is_daylight_savings_time__funk);}
  {char* slot_name = "timezone";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.timezone__funk);}
  {char* slot_name = "as-graphviz_label";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.as__graphviz_label__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.terminal_print_with_frame__funk);}
  return this;
}



// relative_time

def_primobject_1_slot(relative_time, total_nanoseconds);

f2ptr f2__relative_time__new(f2ptr cause, f2ptr total_nanoseconds) {
  assert_argument_type(integer, total_nanoseconds);
  return f2relative_time__new(cause, total_nanoseconds);
}
def_pcfunk1(relative_time__new, total_nanoseconds,
	    "",
	    return f2__relative_time__new(this_cause, total_nanoseconds));

s64 raw__relative_time__total_nanoseconds(f2ptr cause, f2ptr this) {
  f2ptr total_nanoseconds = f2__relative_time__total_nanoseconds(cause, this);
  return f2integer__i(total_nanoseconds, cause);
}

boolean_t raw__relative_time__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__relative_time__is_type(cause, that)) {
    return boolean__false;
  }
  return raw__eq(cause, f2__relative_time__total_nanoseconds(cause, this), f2__relative_time__total_nanoseconds(cause, that));
}

f2ptr f2__relative_time__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(relative_time, this);
  return f2bool__new(raw__relative_time__equals(cause, this, that));
}
def_pcfunk2(relative_time__equals, this, that,
	    "The relative_time represented by this and that relative_time object are the same even if the objects themselves are different objects., """,
	    return f2__relative_time__equals(this_cause, this, that));

boolean_t raw__relative_time__is_past(f2ptr cause, f2ptr this) {
  s64 total_nanoseconds__i = f2integer__i(f2relative_time__total_nanoseconds(this, cause), cause);
  return (total_nanoseconds__i < 0);
}

f2ptr f2__relative_time__is_past(f2ptr cause, f2ptr this) {return f2bool__new(raw__relative_time__is_past(cause, this));}
def_pcfunk1(relative_time__is_past, this,
	    "Whether or not this relative_time is_past.",
	    return f2__relative_time__is_past(this_cause, this));

s64 raw__relative_time__days(f2ptr cause, f2ptr this) {
  s64 total_nanoseconds__i = f2integer__i(f2relative_time__total_nanoseconds(this, cause), cause);
  if (total_nanoseconds__i < 0) {
    total_nanoseconds__i = -total_nanoseconds__i;
  }
  return total_nanoseconds__i / nanoseconds_per_day;
}

f2ptr f2__relative_time__days(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__relative_time__days(cause, this));}
def_pcfunk1(relative_time__days, this,
	    "The number of days since the beginning of the month.",
	    return f2__relative_time__days(this_cause, this));

s64 raw__relative_time__hours(f2ptr cause, f2ptr this) {
  s64 total_nanoseconds__i = f2integer__i(f2relative_time__total_nanoseconds(this, cause), cause);
  if (total_nanoseconds__i < 0) {
    total_nanoseconds__i = -total_nanoseconds__i;
  }
  s64 total_days           = total_nanoseconds__i / nanoseconds_per_day;
  return (total_nanoseconds__i - (total_days * nanoseconds_per_day)) / nanoseconds_per_hour;
}

f2ptr f2__relative_time__hours(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__relative_time__hours(cause, this));}
def_pcfunk1(relative_time__hours, this,
	    "The number of hours since the beginning of the day.",
	    return f2__relative_time__hours(this_cause, this));

s64 raw__relative_time__minutes(f2ptr cause, f2ptr this) {
  s64 total_nanoseconds__i = f2integer__i(f2relative_time__total_nanoseconds(this, cause), cause);
  if (total_nanoseconds__i < 0) {
    total_nanoseconds__i = -total_nanoseconds__i;
  }
  s64 total_hours          = total_nanoseconds__i / nanoseconds_per_hour;
  return (total_nanoseconds__i - (total_hours * nanoseconds_per_hour)) / nanoseconds_per_minute;
}

f2ptr f2__relative_time__minutes(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__relative_time__minutes(cause, this));}
def_pcfunk1(relative_time__minutes, this,
	    "The number of minutes since the beginning of the hour.",
	    return f2__relative_time__minutes(this_cause, this));

s64 raw__relative_time__seconds(f2ptr cause, f2ptr this) {
  s64 total_nanoseconds__i = f2integer__i(f2relative_time__total_nanoseconds(this, cause), cause);
  if (total_nanoseconds__i < 0) {
    total_nanoseconds__i = -total_nanoseconds__i;
  }
  s64 total_minutes        = total_nanoseconds__i / nanoseconds_per_minute;
  return (total_nanoseconds__i - (total_minutes * nanoseconds_per_minute)) / nanoseconds_per_second;
}

f2ptr f2__relative_time__seconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__relative_time__seconds(cause, this));}
def_pcfunk1(relative_time__seconds, this,
	    "The number of seconds since the beginning of the minute.",
	    return f2__relative_time__seconds(this_cause, this));

s64 raw__relative_time__milliseconds(f2ptr cause, f2ptr this) {
  s64 total_nanoseconds__i = f2integer__i(f2relative_time__total_nanoseconds(this, cause), cause);
  if (total_nanoseconds__i < 0) {
    total_nanoseconds__i = -total_nanoseconds__i;
  }
  s64 total_seconds        = total_nanoseconds__i / nanoseconds_per_second;
  return (total_nanoseconds__i - (total_seconds * nanoseconds_per_second)) / nanoseconds_per_millisecond;
}

f2ptr f2__relative_time__milliseconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__relative_time__milliseconds(cause, this));}
def_pcfunk1(relative_time__milliseconds, this,
	    "The number of milliseconds since the beginning of the minute.",
	    return f2__relative_time__milliseconds(this_cause, this));

s64 raw__relative_time__microseconds(f2ptr cause, f2ptr this) {
  s64 total_nanoseconds__i = f2integer__i(f2relative_time__total_nanoseconds(this, cause), cause);
  if (total_nanoseconds__i < 0) {
    total_nanoseconds__i = -total_nanoseconds__i;
  }
  s64 total_milliseconds   = total_nanoseconds__i / nanoseconds_per_millisecond;
  return (total_nanoseconds__i - (total_milliseconds * nanoseconds_per_millisecond)) / nanoseconds_per_microsecond;
}

f2ptr f2__relative_time__microseconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__relative_time__microseconds(cause, this));}
def_pcfunk1(relative_time__microseconds, this,
	    "The number of microseconds since the beginning of the minute.",
	    return f2__relative_time__microseconds(this_cause, this));

s64 raw__relative_time__nanoseconds(f2ptr cause, f2ptr this) {
  s64 total_nanoseconds__i = f2integer__i(f2relative_time__total_nanoseconds(this, cause), cause);
  if (total_nanoseconds__i < 0) {
    total_nanoseconds__i = -total_nanoseconds__i;
  }
  s64 total_microseconds   = total_nanoseconds__i / nanoseconds_per_microsecond;
  return (total_nanoseconds__i - (total_microseconds * nanoseconds_per_microsecond));
}

f2ptr f2__relative_time__nanoseconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__relative_time__nanoseconds(cause, this));}
def_pcfunk1(relative_time__nanoseconds, this,
	    "The number of nanoseconds since the beginning of the second.",
	    return f2__relative_time__nanoseconds(this_cause, this));

f2ptr raw__relative_time__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__total_nanoseconds = f2__relative_time__total_nanoseconds(cause, this);
  f2ptr that__total_nanoseconds = f2__relative_time__total_nanoseconds(cause, that);
  s64   this__total_nanoseconds__i = f2integer__i(this__total_nanoseconds, cause);
  s64   that__total_nanoseconds__i = f2integer__i(that__total_nanoseconds, cause);
  if (this__total_nanoseconds__i < that__total_nanoseconds__i) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__relative_time__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(relative_time, this);
  assert_argument_type(relative_time, that);
  return f2bool__new(raw__relative_time__is_less_than(cause, this, that));
}
def_pcfunk2(relative_time__is_less_than, this, that,
	    "Returns t if this relative_time is further in the past than that relative_time.",
	    return f2__relative_time__is_less_than(this_cause, this, that));

f2ptr raw__relative_time__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__total_nanoseconds = f2__relative_time__total_nanoseconds(cause, this);
  f2ptr that__total_nanoseconds = f2__relative_time__total_nanoseconds(cause, that);
  s64   this__total_nanoseconds__i = f2integer__i(this__total_nanoseconds, cause);
  s64   that__total_nanoseconds__i = f2integer__i(that__total_nanoseconds, cause);
  if (this__total_nanoseconds__i > that__total_nanoseconds__i) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__relative_time__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(relative_time, this);
  assert_argument_type(relative_time, that);
  return f2bool__new(raw__relative_time__is_greater_than(cause, this, that));
}
def_pcfunk2(relative_time__is_greater_than, this, that,
	    "Returns t if this relative_time is further in the future than that relative_time.",
	    return f2__relative_time__is_greater_than(this_cause, this, that));

f2ptr raw__relative_time__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__total_nanoseconds = f2__relative_time__total_nanoseconds(cause, this);
  f2ptr that__total_nanoseconds = f2__relative_time__total_nanoseconds(cause, that);
  s64   this__total_nanoseconds__i = f2integer__i(this__total_nanoseconds, cause);
  s64   that__total_nanoseconds__i = f2integer__i(that__total_nanoseconds, cause);
  if (this__total_nanoseconds__i == that__total_nanoseconds__i) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__relative_time__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(relative_time, this);
  assert_argument_type(relative_time, that);
  return f2bool__new(raw__relative_time__is_numerically_equal_to(cause, this, that));
}
def_pcfunk2(relative_time__is_numerically_equal_to, this, that,
	    "Returns t if the total_nanoseconds of this relative_time is numerically equal to those of that relative_time.",
	    return f2__relative_time__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__relative_time__plus(f2ptr cause, f2ptr this, f2ptr that) {
  if (raw__relative_time__is_type(cause, that)) {
    f2ptr this__total_nanoseconds    = f2__relative_time__total_nanoseconds(cause, this);
    f2ptr that__total_nanoseconds    = f2__relative_time__total_nanoseconds(cause, that);
    s64   this__total_nanoseconds__i = f2integer__i(this__total_nanoseconds, cause);
    s64   that__total_nanoseconds__i = f2integer__i(that__total_nanoseconds, cause);
    return f2__relative_time__new(cause, f2integer__new(cause, this__total_nanoseconds__i + that__total_nanoseconds__i));
  } else if (raw__time__is_type(cause, that)) {
    return raw__time__plus(cause, that, this);
  } else {
    return f2larva__new(cause, 43425, nil);
  }
}

f2ptr f2__relative_time__plus(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(relative_time, this);
  return raw__relative_time__plus(cause, this, that);
}
def_pcfunk2(relative_time__plus, this, that,
	    "Returns t if this relative_time is further in the past than that relative_time.",
	    return f2__relative_time__plus(this_cause, this, that));


f2ptr raw__relative_time__minus(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__total_nanoseconds    = f2__relative_time__total_nanoseconds(cause, this);
  f2ptr that__total_nanoseconds    = f2__relative_time__total_nanoseconds(cause, that);
  s64   this__total_nanoseconds__i = f2integer__i(this__total_nanoseconds, cause);
  s64   that__total_nanoseconds__i = f2integer__i(that__total_nanoseconds, cause);
  return f2__relative_time__new(cause, f2integer__new(cause, this__total_nanoseconds__i - that__total_nanoseconds__i));
}

f2ptr f2__relative_time__minus(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(relative_time, this);
  assert_argument_type(relative_time, that);
  return raw__relative_time__minus(cause, this, that);
}
def_pcfunk2(relative_time__minus, this, that,
	    "Returns t if this relative_time is further in the past than that relative_time.",
	    return f2__relative_time__minus(this_cause, this, that));


f2ptr raw__relative_time__as__string(f2ptr cause, f2ptr this) {
  f2ptr total_nanoseconds    = f2__relative_time__total_nanoseconds(cause, this);
  s64   total_nanoseconds__i = f2integer__i(total_nanoseconds, cause);
  if (total_nanoseconds__i == 0) {
    return new__string(cause, "now");
  } else {
    s64       days                = raw__relative_time__days(        cause, this);
    s64       hours               = raw__relative_time__hours(       cause, this);
    s64       minutes             = raw__relative_time__minutes(     cause, this);
    s64       seconds             = raw__relative_time__seconds(     cause, this);
    s64       milliseconds        = raw__relative_time__milliseconds(cause, this);
    s64       microseconds        = raw__relative_time__microseconds(cause, this);
    s64       nanoseconds         = raw__relative_time__nanoseconds( cause, this);
    boolean_t is_past             = raw__relative_time__is_past(     cause, this);
    f2ptr     days_string         = (days         == 0) ? new__string(cause, "") : f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2integer__new(cause, days)),         (days         == 1) ? new__string(cause, " day ")         : new__string(cause, " days ")));
    f2ptr     hours_string        = (hours        == 0) ? new__string(cause, "") : f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2integer__new(cause, hours)),        (hours        == 1) ? new__string(cause, " hour ")        : new__string(cause, " hours ")));
    f2ptr     minutes_string      = (minutes      == 0) ? new__string(cause, "") : f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2integer__new(cause, minutes)),      (minutes      == 1) ? new__string(cause, " minute ")      : new__string(cause, " minutes ")));
    f2ptr     seconds_string      = (seconds      == 0) ? new__string(cause, "") : f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2integer__new(cause, seconds)),      (seconds      == 1) ? new__string(cause, " second ")      : new__string(cause, " seconds ")));
    f2ptr     milliseconds_string = (milliseconds == 0) ? new__string(cause, "") : f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2integer__new(cause, milliseconds)), (milliseconds == 1) ? new__string(cause, " millisecond ") : new__string(cause, " milliseconds ")));
    f2ptr     microseconds_string = (microseconds == 0) ? new__string(cause, "") : f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2integer__new(cause, microseconds)), (microseconds == 1) ? new__string(cause, " microsecond ") : new__string(cause, " microseconds ")));
    f2ptr     nanoseconds_string  = (nanoseconds  == 0) ? new__string(cause, "") : f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2integer__new(cause, nanoseconds)),  (nanoseconds  == 1) ? new__string(cause, " nanosecond ")  : new__string(cause, " nanoseconds ")));
    f2ptr     is_past_string      = is_past             ? new__string(cause, "before") : new__string(cause, "after");
    return f2__stringlist__concat(cause, f2list8__new(cause,
						      days_string,
						      hours_string,
						      minutes_string,
						      seconds_string,
						      milliseconds_string,
						      microseconds_string,
						      nanoseconds_string,
						      is_past_string));
  }
}

f2ptr f2__relative_time__as__string(f2ptr cause, f2ptr this) {
  assert_argument_type(relative_time, this);
  return raw__relative_time__as__string(cause, this);
}
def_pcfunk1(relative_time__as__string, this,
	    "Returns a string representation of this relative_time.",
	    return f2__relative_time__as__string(this_cause, this));


f2ptr raw__relative_time__as__graphviz_label(f2ptr cause, f2ptr this) {
  return raw__relative_time__as__string(cause, this);
}

f2ptr f2__relative_time__as__graphviz_label(f2ptr cause, f2ptr this) {
  assert_argument_type(relative_time, this);
  return raw__relative_time__as__graphviz_label(cause, this);
}
def_pcfunk1(relative_time__as__graphviz_label, this,
	    "Returns a string representation of this relative_time for rendering in graphviz.",
    return f2__relative_time__as__graphviz_label(this_cause, this));


f2ptr raw__relative_time__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list2__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "relative_time")));
    f2ptr print_object_slot_order = nil;
    boolean_t printed_is_past = boolean__false;
    {
      f2ptr is_past = f2__relative_time__is_past(cause, this);
      if (is_past != nil) {
	printed_is_past = boolean__true;
	f2__frame__add_var_value(cause, frame, new__symbol(cause, "is_past"), is_past);
      }
    }
    boolean_t printed_days = boolean__false;
    {
      f2ptr days = f2__relative_time__days(cause, this);
      if (f2integer__i(days, cause) != 0) {
	printed_days = boolean__true;
	f2__frame__add_var_value(cause, frame, new__symbol(cause, "days"), days);
      }
    }
    boolean_t printed_hours = boolean__false;
    {
      f2ptr hours = f2__relative_time__hours(cause, this);
      if (printed_days ||
	  (f2integer__i(hours, cause) != 0)) {
	printed_hours = boolean__true;
	f2__frame__add_var_value(cause, frame, new__symbol(cause, "hours"), hours);
      }
    }
    boolean_t printed_minutes = boolean__false;
    {
      f2ptr minutes = f2__relative_time__minutes(cause, this);
      if (printed_hours ||
	  (f2integer__i(minutes, cause) != 0)) {
	printed_minutes = boolean__true;
	f2__frame__add_var_value(cause, frame, new__symbol(cause, "minutes"), minutes);
      }
    }
    boolean_t printed_seconds = boolean__false;
    {
      f2ptr seconds = f2__relative_time__seconds(cause, this);
      if (printed_minutes ||
	  (f2integer__i(seconds, cause) != 0)) {
	printed_seconds = boolean__true;
	f2__frame__add_var_value(cause, frame, new__symbol(cause, "seconds"), seconds);
      }
    }
    boolean_t printed_milliseconds = boolean__false;
    {
      f2ptr milliseconds = f2__relative_time__milliseconds(cause, this);
      if (printed_seconds ||
	  (f2integer__i(milliseconds, cause) != 0)) {
	printed_milliseconds = boolean__true;
	f2__frame__add_var_value(cause, frame, new__symbol(cause, "milliseconds"), milliseconds);
      }
    }
    boolean_t printed_microseconds = boolean__false;
    {
      f2ptr microseconds = f2__relative_time__microseconds(cause, this);
      if (printed_milliseconds ||
	  (f2integer__i(microseconds, cause) != 0)) {
	printed_microseconds = boolean__true;
	f2__frame__add_var_value(cause, frame, new__symbol(cause, "microseconds"), microseconds);
      }
    }
    boolean_t printed_nanoseconds = boolean__false;
    {
      f2ptr nanoseconds = f2__relative_time__nanoseconds(cause, this);
      printed_nanoseconds = boolean__true;
      f2__frame__add_var_value(cause, frame, new__symbol(cause, "nanoseconds"), nanoseconds);
    }
    if (printed_nanoseconds) {
      print_object_slot_order = raw__cons__new(cause, new__symbol(cause, "nanoseconds"), print_object_slot_order);
    }
    if (printed_microseconds) {
      print_object_slot_order = raw__cons__new(cause, new__symbol(cause, "microseconds"), print_object_slot_order);
    }
    if (printed_milliseconds) {
      print_object_slot_order = raw__cons__new(cause, new__symbol(cause, "milliseconds"), print_object_slot_order);
    }
    if (printed_seconds) {
      print_object_slot_order = raw__cons__new(cause, new__symbol(cause, "seconds"), print_object_slot_order);
    }
    if (printed_minutes) {
      print_object_slot_order = raw__cons__new(cause, new__symbol(cause, "minutes"), print_object_slot_order);
    }
    if (printed_hours) {
      print_object_slot_order = raw__cons__new(cause, new__symbol(cause, "hours"), print_object_slot_order);
    }
    if (printed_days) {
      print_object_slot_order = raw__cons__new(cause, new__symbol(cause, "days"), print_object_slot_order);
    }
    if (printed_is_past) {
      print_object_slot_order = raw__cons__new(cause, new__symbol(cause, "is_past"), print_object_slot_order);
    }
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_slot_order"), print_object_slot_order);
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__relative_time__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(relative_time,                 this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__relative_time__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(relative_time__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__relative_time__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2relative_time__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2relative_time__primobject_type__new(cause);
  {char* slot_name = "equals";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.equals__funk);}
  {char* slot_name = "is_past";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.is_past__funk);}
  {char* slot_name = "days";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.days__funk);}
  {char* slot_name = "hours";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.hours__funk);}
  {char* slot_name = "minutes";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.minutes__funk);}
  {char* slot_name = "seconds";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.seconds__funk);}
  {char* slot_name = "milliseconds";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.milliseconds__funk);}
  {char* slot_name = "microseconds";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.microseconds__funk);}
  {char* slot_name = "nanoseconds";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.nanoseconds__funk);}
  {char* slot_name = "is_less_than";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.is_less_than__funk);}
  {char* slot_name = "is_greater_than";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.is_greater_than__funk);}
  {char* slot_name = "is_numerically_equal_to";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.is_numerically_equal_to__funk);}
  {char* slot_name = "plus";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.plus__funk);}
  {char* slot_name = "minus";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.minus__funk);}
  {char* slot_name = "as-string";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.as__string__funk);}
  {char* slot_name = "as-graphviz_label";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.as__graphviz_label__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_relative_time.terminal_print_with_frame__funk);}
  return this;
}



// **

void f2__time__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --

  f2__primcfunk__init__defragment__fix_pointers(nanoseconds_since_1970);

#ifndef F2__CYGWIN
  f2__primcfunk__init__defragment__fix_pointers(processor_thread__execution_nanoseconds);
  f2__primcfunk__init__defragment__fix_pointers(funk2__execution_nanoseconds);
#endif // F2__CYGWIN


  // time
  
  initialize_primobject_1_slot__defragment__fix_pointers(time, nanoseconds_since_1970);
  initialize_primobject_funk__defragment__fix_pointers(time, equals);
  initialize_primobject_funk__defragment__fix_pointers(time, years);
  initialize_primobject_funk__defragment__fix_pointers(time, months);
  initialize_primobject_funk__defragment__fix_pointers(time, days);
  initialize_primobject_funk__defragment__fix_pointers(time, hours);
  initialize_primobject_funk__defragment__fix_pointers(time, minutes);
  initialize_primobject_funk__defragment__fix_pointers(time, seconds);
  initialize_primobject_funk__defragment__fix_pointers(time, milliseconds);
  initialize_primobject_funk__defragment__fix_pointers(time, microseconds);
  initialize_primobject_funk__defragment__fix_pointers(time, nanoseconds);
  initialize_primobject_funk__defragment__fix_pointers(time, is_less_than);
  initialize_primobject_funk__defragment__fix_pointers(time, is_greater_than);
  initialize_primobject_funk__defragment__fix_pointers(time, is_numerically_equal_to);
  initialize_primobject_funk__defragment__fix_pointers(time, minus);
  initialize_primobject_funk__defragment__fix_pointers(time, plus);
  initialize_primobject_funk__defragment__fix_pointers(time, abbreviated_weekday_name);
  initialize_primobject_funk__defragment__fix_pointers(time, weekday_name);
  initialize_primobject_funk__defragment__fix_pointers(time, abbreviated_month_name);
  initialize_primobject_funk__defragment__fix_pointers(time, month_name);
  initialize_primobject_funk__defragment__fix_pointers(time, date_and_time_string);
  initialize_primobject_funk__defragment__fix_pointers(time, day_of_week);
  initialize_primobject_funk__defragment__fix_pointers(time, day_of_year);
  initialize_primobject_funk__defragment__fix_pointers(time, is_daylight_savings_time);
  initialize_primobject_funk__defragment__fix_pointers(time, timezone);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_time.as__graphviz_label__symbol);
  f2__primcfunk__init__defragment__fix_pointers(time__as__graphviz_label);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_time.as__graphviz_label__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_time.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(time__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_time.terminal_print_with_frame__funk);
  
  
  // relative_time
  
  initialize_primobject_1_slot__defragment__fix_pointers(relative_time, total_nanoseconds);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, equals);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, is_past);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, days);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, hours);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, minutes);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, seconds);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, milliseconds);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, microseconds);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, nanoseconds);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, is_less_than);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, is_greater_than);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, is_numerically_equal_to);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, plus);
  initialize_primobject_funk__defragment__fix_pointers(relative_time, minus);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_relative_time.as__string__symbol);
  f2__primcfunk__init__defragment__fix_pointers(relative_time__as__string);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_relative_time.as__string__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_relative_time.as__graphviz_label__symbol);
  f2__primcfunk__init__defragment__fix_pointers(relative_time__as__graphviz_label);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_relative_time.as__graphviz_label__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_relative_time.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(relative_time__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_relative_time.terminal_print_with_frame__funk);
}

void f2__time__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  f2__primcfunk__init__0(nanoseconds_since_1970);

#ifndef F2__CYGWIN
  f2__primcfunk__init__0(processor_thread__execution_nanoseconds);
  f2__primcfunk__init__0(funk2__execution_nanoseconds);
#endif // F2__CYGWIN


  // time
  
  initialize_primobject_1_slot(time, nanoseconds_since_1970);
  initialize_primobject_funk__0_arg(time, equals);
  initialize_primobject_funk__0_arg(time, years);
  initialize_primobject_funk__0_arg(time, months);
  initialize_primobject_funk__0_arg(time, days);
  initialize_primobject_funk__0_arg(time, hours);
  initialize_primobject_funk__0_arg(time, minutes);
  initialize_primobject_funk__0_arg(time, seconds);
  initialize_primobject_funk__0_arg(time, milliseconds);
  initialize_primobject_funk__0_arg(time, microseconds);
  initialize_primobject_funk__0_arg(time, nanoseconds);
  initialize_primobject_funk__1_arg(time, is_less_than,            that);
  initialize_primobject_funk__1_arg(time, is_greater_than,         that);
  initialize_primobject_funk__1_arg(time, is_numerically_equal_to, that);
  initialize_primobject_funk__1_arg(time, minus,                   that);
  initialize_primobject_funk__1_arg(time, plus,                    that);
  initialize_primobject_funk__0_arg(time, abbreviated_weekday_name);
  initialize_primobject_funk__0_arg(time, weekday_name);
  initialize_primobject_funk__0_arg(time, abbreviated_month_name);
  initialize_primobject_funk__0_arg(time, month_name);
  initialize_primobject_funk__0_arg(time, date_and_time_string);
  initialize_primobject_funk__0_arg(time, day_of_week);
  initialize_primobject_funk__0_arg(time, day_of_year);
  initialize_primobject_funk__0_arg(time, is_daylight_savings_time);
  initialize_primobject_funk__0_arg(time, timezone);
  
  {char* symbol_str = "as-graphviz_label"; __funk2.globalenv.object_type.primobject.primobject_type_time.as__graphviz_label__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__as__graphviz_label, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_time.as__graphviz_label__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_time.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(time__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_time.terminal_print_with_frame__funk = never_gc(cfunk);}
  

  // relative_time
  
  initialize_primobject_1_slot(relative_time, total_nanoseconds);
  initialize_primobject_funk__0_arg(relative_time, equals);
  initialize_primobject_funk__0_arg(relative_time, is_past);
  initialize_primobject_funk__0_arg(relative_time, days);
  initialize_primobject_funk__0_arg(relative_time, hours);
  initialize_primobject_funk__0_arg(relative_time, minutes);
  initialize_primobject_funk__0_arg(relative_time, seconds);
  initialize_primobject_funk__0_arg(relative_time, milliseconds);
  initialize_primobject_funk__0_arg(relative_time, microseconds);
  initialize_primobject_funk__0_arg(relative_time, nanoseconds);
  initialize_primobject_funk__1_arg(relative_time, is_less_than,             that);
  initialize_primobject_funk__1_arg(relative_time, is_greater_than,          that);
  initialize_primobject_funk__1_arg(relative_time, is_numerically_equal_to,  that);
  initialize_primobject_funk__1_arg(relative_time, plus,                     that);
  initialize_primobject_funk__1_arg(relative_time, minus,                    that);
  
  {char* symbol_str = "as-string"; __funk2.globalenv.object_type.primobject.primobject_type_relative_time.as__string__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(relative_time__as__string, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_relative_time.as__string__funk = never_gc(cfunk);}
  {char* symbol_str = "as-graphviz_label"; __funk2.globalenv.object_type.primobject.primobject_type_relative_time.as__graphviz_label__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(relative_time__as__graphviz_label, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_relative_time.as__graphviz_label__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_relative_time.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(relative_time__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_relative_time.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__time__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "time", "", &f2__time__reinitialize_globalvars, &f2__time__defragment__fix_pointers);
  
  f2__time__reinitialize_globalvars();
}

