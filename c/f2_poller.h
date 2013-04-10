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

#ifndef F2__POLLER__TYPES__H
#define F2__POLLER__TYPES__H

typedef struct funk2_poller_s funk2_poller_t;

#endif // F2__POLLER__TYPES__H


#ifndef F2__POLLER__H
#define F2__POLLER__H

#define poller__deep_sleep_percentage     0.02
#define poller__deep_sleep_average_length 10

struct funk2_poller_s {
  double    target_cpu_usage;
  double    target_cpu_usage_lower_boundary;
  double    target_cpu_usage_upper_boundary;
  u64       average_count;
  double    sleep_nanoseconds;
  double    sleep_nanoseconds_multiplier;
  u64       current_index;
  boolean_t buffer_full;
  u64       last_real_nanoseconds;
  u64       last_execution_nanoseconds;
  u64*      elapsed_real_nanoseconds_array;
  u64*      elapsed_execution_nanoseconds_array;
  u64       total_elapsed_real_nanoseconds;
  u64       total_elapsed_execution_nanoseconds;
  double    average_cpu_usage;
};

void funk2_poller__init   (funk2_poller_t* this, double target_cpu_usage, u64 average_count);
void funk2_poller__destroy(funk2_poller_t* this);
void funk2_poller__reset  (funk2_poller_t* this);
void funk2_poller__sleep  (funk2_poller_t* this);
void funk2_poller__test   ();

#endif // F2__POLLER__H
