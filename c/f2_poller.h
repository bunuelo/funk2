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

typedef struct funk2_poller_global_helper_s funk2_poller_global_helper_t;
typedef struct funk2_poller_s               funk2_poller_t;

#endif // F2__POLLER__TYPES__H


#ifndef F2__POLLER__H
#define F2__POLLER__H

#include "f2_atomic_u64.h"

// funk2_poller_global_helper

struct funk2_poller_global_helper_s {
  u64                initialized_magic;
  double             target_cpu_usage;
  u64                average_count;
  funk2_atomic_u64_t optimal_sleep_nanoseconds;
};

void funk2_poller_global_helper__init           (funk2_poller_global_helper_t* this,
						 double                        target_cpu_usage,
						 u64                           average_count,
						 u64                           optimal_sleep_nanoseconds);
void funk2_poller_global_helper__init_deep_sleep(funk2_poller_global_helper_t* this);
void funk2_poller_global_helper__destroy        (funk2_poller_global_helper_t* this);


// funk2_poller

struct funk2_poller_s {
  funk2_poller_global_helper_t* global_helper;
  double                        target_cpu_usage;
  double                        target_cpu_usage_lower_boundary;
  double                        target_cpu_usage_upper_boundary;
  u64                           average_count;
  double                        sleep_nanoseconds;
  double                        sleep_nanoseconds_multiplier;
  u64                           current_index;
  boolean_t                     buffer_full;
  u64                           last_real_nanoseconds;
  u64                           last_execution_nanoseconds;
  u64*                          elapsed_real_nanoseconds_array;
  u64*                          elapsed_execution_nanoseconds_array;
  u64                           total_elapsed_real_nanoseconds;
  u64                           total_elapsed_execution_nanoseconds;
  double                        average_cpu_usage;
  // debugging variables
  u64                           last_reset_nanoseconds_since_1970;
  u64                           last_print_debug_nanoseconds_since_1970;
  u64                           total_sleep_cycle_count;
};

void funk2_poller__init                   (funk2_poller_t* this,
					   double          target_cpu_usage,
					   u64             average_count,
					   u64             initial_sleep_nanoseconds);
void funk2_poller__init_deep_sleep        (funk2_poller_t* this);
void funk2_poller__init_from_global_helper(funk2_poller_t* this, funk2_poller_global_helper_t* global_helper);
void funk2_poller__destroy                (funk2_poller_t* this);
void funk2_poller__reset                  (funk2_poller_t* this);
void funk2_poller__sleep                  (funk2_poller_t* this);
void funk2_poller__test                   ();

#endif // F2__POLLER__H
