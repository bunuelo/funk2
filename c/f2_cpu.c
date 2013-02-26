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

void funk2_cpu__init(funk2_cpu_t* this) {
  this->last_user_clock_ticks       = 0;
  this->last_system_clock_ticks     = 0;
  this->last_nanoseconds_since_1970 = 0;
  this->user_cpu_usage              = 0.0;
  this->system_cpu_usage            = 0.0;
}

void funk2_cpu__destroy(funk2_cpu_t* this) {
}

void funk2_cpu__handle(funk2_cpu_t* this) {
  u64 nanoseconds_since_1970 = raw__nanoseconds_since_1970();
  if (nanoseconds_since_1970 > this->last_nanoseconds_since_1970 + nanoseconds_per_second) {
    u64 elapsed_nanoseconds = nanoseconds_since_1970 - this->last_nanoseconds_since_1970;
    u64 clock_ticks_per_second = sysconf(_SC_CLK_TCK);
    struct tms times_data;
    times(&times_data);
    u64    user_clock_ticks           = times_data.tms_utime;
    u64    system_clock_ticks         = times_data.tms_stime;
    u64    elapsed_user_clock_ticks   = user_clock_ticks   - this->last_user_clock_ticks;
    u64    elapsed_system_clock_ticks = system_clock_ticks - this->last_system_clock_ticks;
    u64    elapsed_user_nanoseconds   = (elapsed_user_clock_ticks   * nanoseconds_per_second) / clock_ticks_per_second;
    u64    elapsed_system_nanoseconds = (elapsed_system_clock_ticks * nanoseconds_per_second) / clock_ticks_per_second;
    double user_cpu_usage             = ((double)elapsed_user_nanoseconds)   / ((double)elapsed_nanoseconds);
    double system_cpu_usage           = ((double)elapsed_system_nanoseconds) / ((double)elapsed_nanoseconds);
    double total_cpu_usage            = user_cpu_usage + system_cpu_usage;
    
    this->last_user_clock_ticks       = user_clock_ticks;
    this->last_system_clock_ticks     = system_clock_ticks;
    this->last_nanoseconds_since_1970 = nanoseconds_since_1970;
    this->user_cpu_usage              = user_cpu_usage;
    this->system_cpu_usage            = system_cpu_usage;
    this->total_cpu_usage             = total_cpu_usage;
  }
}

double raw__cpu__user_cpu_usage(f2ptr cause) {
  return __funk2.cpu.user_cpu_usage;
}

f2ptr f2__cpu__user_cpu_usage(f2ptr cause) {
  return f2double__new(cause, raw__cpu__user_cpu_usage(cause));
}
def_pcfunk0(cpu__user_cpu_usage,
	    "",
	    return f2__cpu__user_cpu_usage(this_cause));

double raw__cpu__system_cpu_usage(f2ptr cause) {
  return __funk2.cpu.system_cpu_usage;
}

f2ptr f2__cpu__system_cpu_usage(f2ptr cause) {
  return f2double__new(cause, raw__cpu__system_cpu_usage(cause));
}
def_pcfunk0(cpu__system_cpu_usage,
	    "",
	    return f2__cpu__system_cpu_usage(this_cause));

double raw__cpu__total_cpu_usage(f2ptr cause) {
  return __funk2.cpu.total_cpu_usage;
}

f2ptr f2__cpu__total_cpu_usage(f2ptr cause) {
  return f2double__new(cause, raw__cpu__total_cpu_usage(cause));
}
def_pcfunk0(cpu__total_cpu_usage,
	    "",
	    return f2__cpu__total_cpu_usage(this_cause));

// **

void f2__cpu__defragment__fix_pointers() {
  // -- reinitialize --

  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(cpu__user_cpu_usage);
  f2__primcfunk__init__defragment__fix_pointers(cpu__system_cpu_usage);
  f2__primcfunk__init__defragment__fix_pointers(cpu__total_cpu_usage);
  
}

void f2__cpu__reinitialize_globalvars() {
  f2__primcfunk__init__0(cpu__user_cpu_usage);
  f2__primcfunk__init__0(cpu__system_cpu_usage);
  f2__primcfunk__init__0(cpu__total_cpu_usage);
}

void f2__cpu__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "cpu", "", &f2__cpu__reinitialize_globalvars, &f2__cpu__defragment__fix_pointers);
  
  f2__cpu__reinitialize_globalvars();
}

