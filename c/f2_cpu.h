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

#ifndef F2__CPU__H
#define F2__CPU__H

typedef struct funk2_cpu_s funk2_cpu_t;

struct funk2_cpu_s {
  u64    last_user_clock_ticks;
  u64    last_system_clock_ticks;
  u64    last_nanoseconds_since_1970;
  double user_cpu_usage;
  double system_cpu_usage;
  double total_cpu_usage;
};

void funk2_cpu__init(funk2_cpu_t* this);
void funk2_cpu__destroy(funk2_cpu_t* this);
void funk2_cpu__handle(funk2_cpu_t* this);

// **

void f2__cpu__reinitialize_globalvars();
void f2__cpu__initialize();

#endif // F2__CPU__H


