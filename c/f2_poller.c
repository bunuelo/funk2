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

#define poller__deep_sleep_percentage        0.02
#define poller__deep_sleep_average_length    10
#define poller__deep_sleep_sleep_nanoseconds (nanoseconds_per_second / 1000)

#define poller__minimum_sleep_nanoseconds (((double)nanoseconds_per_second) / 64.0)


#define POLLER_GLOBAL_HELPER_MAGIC ((u64)0xFEEDDEAD)


// funk2_poller_global_helper

void funk2_poller_global_helper__init(funk2_poller_global_helper_t* this,
				      double                        target_cpu_usage,
				      u64                           average_count,
				      u64                           optimal_sleep_nanoseconds) {
  this->target_cpu_usage = target_cpu_usage;
  this->average_count    = average_count;
  funk2_atomic_u64__init(&(this->optimal_sleep_nanoseconds), optimal_sleep_nanoseconds);
  this->initialized_magic = POLLER_GLOBAL_HELPER_MAGIC;
}

void funk2_poller_global_helper__init_deep_sleep(funk2_poller_global_helper_t* this) {
  funk2_poller_global_helper__init(this,
				   poller__deep_sleep_percentage,
				   poller__deep_sleep_average_length,
				   poller__deep_sleep_sleep_nanoseconds);
}

void funk2_poller_global_helper__destroy(funk2_poller_global_helper_t* this) {
  funk2_atomic_u64__destroy(&(this->optimal_sleep_nanoseconds));
}

// funk2_poller

void funk2_poller__init(funk2_poller_t* this, double target_cpu_usage, u64 average_count, u64 initial_sleep_nanoseconds) {
  double range_factor = 1.1;
  this->global_helper                           = NULL;
  this->target_cpu_usage                        = target_cpu_usage;
  this->target_cpu_usage_lower_boundary         = target_cpu_usage / range_factor;
  this->target_cpu_usage_upper_boundary         = target_cpu_usage * range_factor;
  this->average_count                           = average_count;
  this->sleep_nanoseconds                       = (((double)initial_sleep_nanoseconds) >= poller__minimum_sleep_nanoseconds) ? ((double)initial_sleep_nanoseconds) : poller__minimum_sleep_nanoseconds;
  this->sleep_nanoseconds_multiplier            = pow(range_factor, 1.0 / (double)average_count);
  this->current_index                           = 0;
  this->buffer_full                             = boolean__false;
  this->last_real_nanoseconds                   = 0;
  this->last_execution_nanoseconds              = 0;
  this->elapsed_real_nanoseconds_array          = (u64*)from_ptr(f2__malloc(sizeof(u64) * (this->average_count)));
  this->elapsed_execution_nanoseconds_array     = (u64*)from_ptr(f2__malloc(sizeof(u64) * (this->average_count)));
  this->total_elapsed_real_nanoseconds          = 0;
  this->total_elapsed_execution_nanoseconds     = 0;
  this->average_cpu_usage                       = 0.0;
#if defined(FUNK2_POLLER_DEBUG)
  // debug variables
  u64 nanoseconds_since_1970 = raw__nanoseconds_since_1970();
  this->last_reset_nanoseconds_since_1970       = nanoseconds_since_1970;
  this->last_print_debug_nanoseconds_since_1970 = nanoseconds_since_1970; // don't want to print immediately
  this->total_sleep_cycle_count                 = 0;
#endif // FUNK2_POLLER_DEBUG
}

void funk2_poller__init_from_global_helper(funk2_poller_t* this, funk2_poller_global_helper_t* global_helper) {
  if (global_helper->initialized_magic != POLLER_GLOBAL_HELPER_MAGIC) {
    error(nil, "funk2_poller__init_from_global_helper error: (global_helper->initialized_magic != POLLER_GLOBAL_HELPER_MAGIC)");
  }
  double target_cpu_usage          = global_helper->target_cpu_usage;
  u64    average_count             = global_helper->average_count;
  u64    initial_sleep_nanoseconds = funk2_atomic_u64__value(&(global_helper->optimal_sleep_nanoseconds));
  funk2_poller__init(this, target_cpu_usage, average_count, initial_sleep_nanoseconds);
  this->global_helper = global_helper;
}

void funk2_poller__init_deep_sleep(funk2_poller_t* this) {
  funk2_poller__init_from_global_helper(this, &(__funk2.global_poller_helper));
}

void funk2_poller__destroy(funk2_poller_t* this) {
  f2__free(to_ptr(this->elapsed_real_nanoseconds_array));
  f2__free(to_ptr(this->elapsed_execution_nanoseconds_array));
}

void funk2_poller__reset(funk2_poller_t* this) {
  this->current_index                           = 0;
  this->buffer_full                             = boolean__false;
  this->total_elapsed_real_nanoseconds          = 0;
  this->total_elapsed_execution_nanoseconds     = 0;
  this->last_real_nanoseconds                   = raw__nanoseconds_since_1970();
  this->last_execution_nanoseconds              = raw__processor_thread__execution_nanoseconds();
#if defined(FUNK2_POLLER_DEBUG)
  // debug variables
  u64 nanoseconds_since_1970 = raw__nanoseconds_since_1970();
  this->last_reset_nanoseconds_since_1970       = nanoseconds_since_1970;
  this->last_print_debug_nanoseconds_since_1970 = nanoseconds_since_1970; // don't want to print immediately
  this->total_sleep_cycle_count                 = 0;
#endif // FUNK2_POLLER_DEBUG
}

void funk2_poller__sleep(funk2_poller_t* this) {
  u64 real_nanoseconds              = raw__nanoseconds_since_1970();
  u64 execution_nanoseconds         = raw__processor_thread__execution_nanoseconds();
  u64 elapsed_real_nanoseconds      = real_nanoseconds      - this->last_real_nanoseconds;
  u64 elapsed_execution_nanoseconds = execution_nanoseconds - this->last_execution_nanoseconds;
  if (! this->buffer_full) {
    this->elapsed_real_nanoseconds_array[this->current_index]      = elapsed_real_nanoseconds;
    this->elapsed_execution_nanoseconds_array[this->current_index] = elapsed_execution_nanoseconds;
    this->total_elapsed_real_nanoseconds      += elapsed_real_nanoseconds;
    this->total_elapsed_execution_nanoseconds += elapsed_execution_nanoseconds;
    this->current_index ++;
    if (this->current_index == this->average_count) {
      this->buffer_full   = boolean__true;
      this->current_index = 0;
    }
  } else {
    this->total_elapsed_real_nanoseconds      -= this->elapsed_real_nanoseconds_array[this->current_index];
    this->total_elapsed_execution_nanoseconds -= this->elapsed_execution_nanoseconds_array[this->current_index];
    this->elapsed_real_nanoseconds_array[this->current_index]      = elapsed_real_nanoseconds;
    this->elapsed_execution_nanoseconds_array[this->current_index] = elapsed_execution_nanoseconds;
    this->total_elapsed_real_nanoseconds      += elapsed_real_nanoseconds;
    this->total_elapsed_execution_nanoseconds += elapsed_execution_nanoseconds;
    this->current_index ++;
    if (this->current_index == this->average_count) {
      this->current_index = 0;
    }
  }
  if (this->total_elapsed_real_nanoseconds != 0) {
    this->average_cpu_usage = ((double)this->total_elapsed_execution_nanoseconds) / ((double)this->total_elapsed_real_nanoseconds);
  } else {
    this->average_cpu_usage = 1.0;
  }
  if (this->buffer_full) {
#if defined(FUNK2_POLLER_DEBUG)
    if ((this->average_cpu_usage > 1.0) ||
	(this->average_cpu_usage < 0.0)) {
      status("funk2_poller average CPU usage out of range.  this->average_cpu_usage=%g", this->average_cpu_usage);
      error(nil, "funk2_poller average CPU usage out of range.");
    }
#endif // FUNK2_POLLER_DEBUG
    if (this->average_cpu_usage < this->target_cpu_usage_lower_boundary) {
      this->sleep_nanoseconds /= this->sleep_nanoseconds_multiplier;
      if (this->sleep_nanoseconds < poller__minimum_sleep_nanoseconds) {
	this->sleep_nanoseconds = poller__minimum_sleep_nanoseconds;
      }
    } else if (this->average_cpu_usage > this->target_cpu_usage_upper_boundary) {
      this->sleep_nanoseconds *= this->sleep_nanoseconds_multiplier;
    }
    if (this->global_helper != NULL) {
      funk2_atomic_u64__set_value(&(this->global_helper->optimal_sleep_nanoseconds), (u64)(this->sleep_nanoseconds));
    }
#if defined(FUNK2_POLLER_DEBUG)
    if ((real_nanoseconds - this->last_print_debug_nanoseconds_since_1970) >= 3 * nanoseconds_per_second) {
      this->last_print_debug_nanoseconds_since_1970 = real_nanoseconds;
      if (this->average_cpu_usage > (3 * this->target_cpu_usage)) {
	status("funk2_poller vvv *** debug info *** vvv  WARNING CPU USAGE IS OVER 3 TIMES HIGHER THAN TARGET");
	status("funk2_poller total_sleep_cycle_count=" u64__fstr, this->total_sleep_cycle_count);
	status("funk2_poller last_reset_seconds     =%g", ((double)(real_nanoseconds - this->last_reset_nanoseconds_since_1970)) / (double)nanoseconds_per_second);
	status("funk2_poller sleep_seconds          =%g", (double)(this->sleep_nanoseconds) / (double)nanoseconds_per_second);
	status("funk2_poller target_cpu_usage       =%g", (double)(this->target_cpu_usage));
	status("funk2_poller average_cpu_usage      =%g", (double)(this->average_cpu_usage));
	status_backtrace();
	status("funk2_poller ^^^ *** debug info *** ^^^");
      }
    }
#endif // FUNK2_POLLER_DEBUG
  }
  raw__nanosleep((u64)(this->sleep_nanoseconds));
  this->last_real_nanoseconds      = real_nanoseconds;
  this->last_execution_nanoseconds = execution_nanoseconds;
#if defined(FUNK2_POLLER_DEBUG)
  // debug code
  this->total_sleep_cycle_count ++;
#endif // FUNK2_POLLER_DEBUG
}

void funk2_poller__test() {
  funk2_poller_t poller;
  funk2_poller__init(&poller, 0.01, 1000, 1);
  printf("\nfunk2_poller__test: poller.target_cpu_usage=%g", poller.target_cpu_usage);
  funk2_poller__reset(&poller);
  double temp = 10.0;
  {
    s64 i;
    for (i = 0; i < 1000; i ++) {
      {
	s64 j;
	for (j = 0; j < 100; j ++) {
	  {
	    s64 k;
	    for (k = 0; k < 1000; k ++) {
	      temp += temp;
	      temp *= temp;
	    }
	  }
	  funk2_poller__sleep(&poller);
	}
      }
      printf("\nfunk2_poller__test: i=" s64__fstr " poller.average_cpu_usage=%g temp=%g", i, poller.average_cpu_usage, temp);
    }
  }
  printf("\nfunk2_poller__test: done.");
  printf("\n");
}
