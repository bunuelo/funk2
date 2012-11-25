// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#define nanoseconds_per_microsecond ((s64)1000)
#define nanoseconds_per_millisecond (nanoseconds_per_microsecond * 1000)
#define nanoseconds_per_second      (nanoseconds_per_millisecond * 1000)
#define nanoseconds_per_minute      (nanoseconds_per_second      * 60)
#define nanoseconds_per_hour        (nanoseconds_per_minute      * 60)
#define nanoseconds_per_day         (nanoseconds_per_hour        * 24)

//void   f2__sleep(int microseconds);
void   f2__nanosleep(u64 nanoseconds);
void  raw__spin_sleep_yield();
void  raw__fast_spin_sleep_yield();
void  raw__user_spin_sleep_yield();
void  raw__user_fast_spin_sleep_yield();
u64   raw__nanoseconds_since_1970();
f2ptr  f2__nanoseconds_since_1970(f2ptr cause);
void       nanoseconds_since_1970__to_funk2_date(u64 nanoseconds_since_1970, funk2_date_t* funk2_date);
f2ptr raw__time__new_from_unix_time(f2ptr cause, time_t unix_time);


// time

declare_primobject_1_slot(time, nanoseconds_since_1970);

f2ptr f2__time__new(f2ptr cause, f2ptr nanoseconds_since_1970);
f2ptr f2time__primobject_type__new_aux(f2ptr cause);


// relative_time

declare_primobject_1_slot(relative_time, total_nanoseconds);

f2ptr f2__relative_time__new(f2ptr cause, f2ptr total_nanoseconds);
f2ptr f2relative_time__primobject_type__new_aux(f2ptr cause);


// time

typedef struct funk2_object_type__time__slot_s funk2_object_type__time__slot_t;
declare_object_type_1_slot(time, nanoseconds_since_1970,
			   f2ptr equals__symbol;
			   f2ptr equals__funk;
			   f2ptr years__symbol;
			   f2ptr years__funk;
			   f2ptr months__symbol;
			   f2ptr months__funk;
			   f2ptr days__symbol;
			   f2ptr days__funk;
			   f2ptr hours__symbol;
			   f2ptr hours__funk;
			   f2ptr minutes__symbol;
			   f2ptr minutes__funk;
			   f2ptr seconds__symbol;
			   f2ptr seconds__funk;
			   f2ptr milliseconds__symbol;
			   f2ptr milliseconds__funk;
			   f2ptr microseconds__symbol;
			   f2ptr microseconds__funk;
			   f2ptr nanoseconds__symbol;
			   f2ptr nanoseconds__funk;
			   f2ptr is_less_than__symbol;
			   f2ptr is_less_than__funk;
			   f2ptr is_greater_than__symbol;
			   f2ptr is_greater_than__funk;
			   f2ptr is_numerically_equal_to__symbol;
			   f2ptr is_numerically_equal_to__funk;
			   f2ptr minus__symbol;
			   f2ptr minus__funk;
			   f2ptr plus__symbol;
			   f2ptr plus__funk;
			   f2ptr abbreviated_weekday_name__symbol;
			   f2ptr abbreviated_weekday_name__funk;
			   f2ptr weekday_name__symbol;
			   f2ptr weekday_name__funk;
			   f2ptr abbreviated_month_name__symbol;
			   f2ptr abbreviated_month_name__funk;
			   f2ptr month_name__symbol;
			   f2ptr month_name__funk;
			   f2ptr date_and_time_string__symbol;
			   f2ptr date_and_time_string__funk;
			   f2ptr day_of_week__symbol;
			   f2ptr day_of_week__funk;
			   f2ptr day_of_year__symbol;
			   f2ptr day_of_year__funk;
			   f2ptr is_daylight_savings_time__symbol;
			   f2ptr is_daylight_savings_time__funk;
			   f2ptr timezone__symbol;
			   f2ptr timezone__funk;
			   f2ptr as__graphviz_label__symbol;
			   f2ptr as__graphviz_label__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

boolean_t raw__time__equals     (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__time__equals     (f2ptr cause, f2ptr this, f2ptr that);
u64       raw__time__years      (f2ptr cause, f2ptr this);
f2ptr      f2__time__years      (f2ptr cause, f2ptr this);
u64       raw__time__months     (f2ptr cause, f2ptr this);
f2ptr      f2__time__months     (f2ptr cause, f2ptr this);
u64       raw__time__days       (f2ptr cause, f2ptr this);
f2ptr      f2__time__days       (f2ptr cause, f2ptr this);
u64       raw__time__hours      (f2ptr cause, f2ptr this);
f2ptr      f2__time__hours      (f2ptr cause, f2ptr this);
u64       raw__time__minutes    (f2ptr cause, f2ptr this);
f2ptr      f2__time__minutes    (f2ptr cause, f2ptr this);
u64       raw__time__seconds    (f2ptr cause, f2ptr this);
f2ptr      f2__time__seconds    (f2ptr cause, f2ptr this);
u64       raw__time__nanoseconds(f2ptr cause, f2ptr this);
f2ptr      f2__time__nanoseconds(f2ptr cause, f2ptr this);



// relative_time

typedef struct funk2_object_type__relative_time__slot_s funk2_object_type__relative_time__slot_t;
declare_object_type_1_slot(relative_time, total_nanoseconds,
			   f2ptr equals__symbol;
			   f2ptr equals__funk;
			   f2ptr is_past__symbol;
			   f2ptr is_past__funk;
			   f2ptr days__symbol;
			   f2ptr days__funk;
			   f2ptr hours__symbol;
			   f2ptr hours__funk;
			   f2ptr minutes__symbol;
			   f2ptr minutes__funk;
			   f2ptr seconds__symbol;
			   f2ptr seconds__funk;
			   f2ptr milliseconds__symbol;
			   f2ptr milliseconds__funk;
			   f2ptr microseconds__symbol;
			   f2ptr microseconds__funk;
			   f2ptr nanoseconds__symbol;
			   f2ptr nanoseconds__funk;
			   f2ptr is_less_than__symbol;
			   f2ptr is_less_than__funk;
			   f2ptr is_greater_than__symbol;
			   f2ptr is_greater_than__funk;
			   f2ptr is_numerically_equal_to__symbol;
			   f2ptr is_numerically_equal_to__funk;
			   f2ptr plus__symbol;
			   f2ptr plus__funk;
			   f2ptr minus__symbol;
			   f2ptr minus__funk;
			   f2ptr as__graphviz_label__symbol;
			   f2ptr as__graphviz_label__funk;
			   f2ptr as__string__symbol;
			   f2ptr as__string__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

s64       raw__relative_time__total_nanoseconds(f2ptr cause, f2ptr this);
boolean_t raw__relative_time__equals           (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__relative_time__equals           (f2ptr cause, f2ptr this, f2ptr that);
boolean_t raw__relative_time__is_past          (f2ptr cause, f2ptr this);
f2ptr      f2__relative_time__is_past          (f2ptr cause, f2ptr this);
s64       raw__relative_time__days             (f2ptr cause, f2ptr this);
f2ptr      f2__relative_time__days             (f2ptr cause, f2ptr this);
s64       raw__relative_time__hours            (f2ptr cause, f2ptr this);
f2ptr      f2__relative_time__hours            (f2ptr cause, f2ptr this);
s64       raw__relative_time__minutes          (f2ptr cause, f2ptr this);
f2ptr      f2__relative_time__minutes          (f2ptr cause, f2ptr this);
s64       raw__relative_time__seconds          (f2ptr cause, f2ptr this);
f2ptr      f2__relative_time__seconds          (f2ptr cause, f2ptr this);
s64       raw__relative_time__milliseconds     (f2ptr cause, f2ptr this);
f2ptr      f2__relative_time__milliseconds     (f2ptr cause, f2ptr this);
s64       raw__relative_time__microseconds     (f2ptr cause, f2ptr this);
f2ptr      f2__relative_time__microseconds     (f2ptr cause, f2ptr this);
s64       raw__relative_time__nanoseconds      (f2ptr cause, f2ptr this);
f2ptr      f2__relative_time__nanoseconds      (f2ptr cause, f2ptr this);


// **

void f2__time__reinitialize_globalvars();
void f2__time__initialize();

#endif // F2__TIME__H
