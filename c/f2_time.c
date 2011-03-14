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



// time

def_primobject_1_slot(time, nanoseconds_since_1970);

f2ptr f2__time__new(f2ptr cause, f2ptr nanoseconds_since_1970) {return f2time__new(cause, nanoseconds_since_1970);}
def_pcfunk1(time__new, nanoseconds_since_1970, return f2__time__new(this_cause, nanoseconds_since_1970));

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
def_pcfunk2(time__equals, this, that, return f2__time__equals(this_cause, this, that));

u64 raw__time__years(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.years;
}

f2ptr f2__time__years(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__years(cause, this));}
def_pcfunk1(time__years, this, return f2__time__years(this_cause, this));

u64 raw__time__months(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.months;
}

f2ptr f2__time__months(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__months(cause, this));}
def_pcfunk1(time__months, this, return f2__time__months(this_cause, this));

u64 raw__time__days(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.days;
}

f2ptr f2__time__days(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__days(cause, this));}
def_pcfunk1(time__days, this, return f2__time__days(this_cause, this));

u64 raw__time__hours(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.hours;
}

f2ptr f2__time__hours(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__hours(cause, this));}
def_pcfunk1(time__hours, this, return f2__time__hours(this_cause, this));

u64 raw__time__minutes(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.minutes;
}

f2ptr f2__time__minutes(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__minutes(cause, this));}
def_pcfunk1(time__minutes, this, return f2__time__minutes(this_cause, this));

u64 raw__time__seconds(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.seconds;
}

f2ptr f2__time__seconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__seconds(cause, this));}
def_pcfunk1(time__seconds, this, return f2__time__seconds(this_cause, this));

u64 raw__time__nanoseconds(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.nanoseconds;
}

f2ptr f2__time__nanoseconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__nanoseconds(cause, this));}
def_pcfunk1(time__nanoseconds, this, return f2__time__nanoseconds(this_cause, this));

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
def_pcfunk2(time__is_less_than, this, that, return f2__time__is_less_than(this_cause, this, that));

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
def_pcfunk2(time__is_greater_than, this, that, return f2__time__is_greater_than(this_cause, this, that));

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
def_pcfunk2(time__is_numerically_equal_to, this, that, return f2__time__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__time__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list16__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "time"),
						new__symbol(cause, "years"),       f2__time__years(      cause, this),
						new__symbol(cause, "months"),      f2__time__months(     cause, this),
						new__symbol(cause, "days"),        f2__time__days(       cause, this),
						new__symbol(cause, "hours"),       f2__time__hours(      cause, this),
						new__symbol(cause, "minutes"),     f2__time__minutes(    cause, this),
						new__symbol(cause, "seconds"),     f2__time__seconds(    cause, this),
						new__symbol(cause, "nanoseconds"), f2__time__nanoseconds(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__time__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(time,                 this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__time__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(time__terminal_print_with_frame, this, terminal_print_frame, return f2__time__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2time__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2time__primobject_type__new(cause);
  {char* slot_name = "equals";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.equals__funk);}
  {char* slot_name = "years";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.years__funk);}
  {char* slot_name = "months";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.months__funk);}
  {char* slot_name = "days";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.days__funk);}
  {char* slot_name = "hours";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.hours__funk);}
  {char* slot_name = "minutes";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.minutes__funk);}
  {char* slot_name = "seconds";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.seconds__funk);}
  {char* slot_name = "nanoseconds";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds__funk);}
  {char* slot_name = "is_less_than";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.is_less_than__funk);}
  {char* slot_name = "is_greater_than";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.is_greater_than__funk);}
  {char* slot_name = "is_numerically_equal_to";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.is_numerically_equal_to__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.terminal_print_with_frame__funk);}
  return this;
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


  // time
  
  initialize_primobject_1_slot(time, nanoseconds_since_1970);
  initialize_primobject_funk__0_arg(time, equals,                        "The time represented by this and that time object are the same even if the objects themselves are different objects.");
  initialize_primobject_funk__0_arg(time, years,                         "The number of years since the monk Dionysius Exiguus thought Jesus Christ was born.");
  initialize_primobject_funk__0_arg(time, months,                        "The number of months since the beginning of the year.");
  initialize_primobject_funk__0_arg(time, days,                          "The number of days since the beginning of the month.");
  initialize_primobject_funk__0_arg(time, hours,                         "The number of hours since the beginning of the day.");
  initialize_primobject_funk__0_arg(time, minutes,                       "The number of minutes since the beginning of the hour.");
  initialize_primobject_funk__0_arg(time, seconds,                       "The number of seconds since the beginning of the minute.");
  initialize_primobject_funk__0_arg(time, nanoseconds,                   "The number of nanoseconds since the beginning of the second.");
  initialize_primobject_funk__1_arg(time, is_less_than,            that, "Returns t if this time is further in the past than that time.");
  initialize_primobject_funk__1_arg(time, is_greater_than,         that, "Returns t if this time is further in the future than that time.");
  initialize_primobject_funk__1_arg(time, is_numerically_equal_to, that, "Returns t if the nanoseconds_since_1970 of this time is numerically equal to those of that time.");
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_time.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(time__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
}

