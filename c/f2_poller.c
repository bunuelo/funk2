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

void funk2_poller__init(funk2_poller_t* this, double target_cpu_usage, u64 average_count) {
  this->target_cpu_usage                    = target_cpu_usage;
  this->average_count                       = average_count;
  this->sleep_nanoseconds                   = 1;
  this->current_index                       = 0;
  this->buffer_full                         = boolean__false;
  this->last_real_nanoseconds               = 0;
  this->last_execution_nanoseconds          = 0;
  this->elapsed_real_nanoseconds_array      = (u64*)from_ptr(f2__malloc(sizeof(u64) * (this->average_count)));
  this->elapsed_execution_nanoseconds_array = (u64*)from_ptr(f2__malloc(sizeof(u64) * (this->average_count)));
  this->total_elapsed_real_nanoseconds      = 0;
  this->total_elapsed_execution_nanoseconds = 0;
}

void funk2_poller__destroy(funk2_poller_t* this) {
  f2__free(to_ptr(this->elapsed_real_nanoseconds_array));
  f2__free(to_ptr(this->elapsed_execution_nanoseconds_array));
}

void funk2_poller__reset(funk2_poller_t* this) {
  this->current_index                       = 0;
  this->buffer_full                         = boolean__false;
  this->total_elapsed_real_nanoseconds      = 0;
  this->total_elapsed_execution_nanoseconds = 0;
  this->last_real_nanoseconds               = raw__nanoseconds_since_1970();
  this->last_execution_nanoseconds          = raw__processor_thread__execution_nanoseconds();
}

void funk2_poller__sleep(funk2_poller_t* this) {
  u64 elapsed_real_nanoseconds       = raw__nanoseconds_since_1970()                  - this->last_real_nanoseconds;
  u64 elapsed_execution_nanoseconds  = raw__processor_thread__execution_nanoseconds() - this->last_execution_nanoseconds;
  if (! this->buffer_full) {
    this->elapsed_real_nanoseconds_array[this->current_index] = elapsed_real_nanoseconds;
    this->elapsed_real_nanoseconds_array[this->current_index] = elapsed_execution_nanoseconds;
    this->total_elapsed_real_nanoseconds      += elapsed_real_nanoseconds;
    this->total_elapsed_execution_nanoseconds += elapsed_execution_nanoseconds;
    this->current_index ++;
    if (this->current_index == this->average_count) {
      this->buffer_full   = boolean__true;
      this->current_index = 0;
    }
  } else {
    this->total_elapsed_real_nanoseconds      -= this->elapsed_real_nanoseconds_array[this->current_index];
    this->total_elapsed_execution_nanoseconds -= this->elapsed_real_nanoseconds_array[this->current_index];
    this->elapsed_real_nanoseconds_array[this->current_index] = elapsed_real_nanoseconds;
    this->elapsed_real_nanoseconds_array[this->current_index] = elapsed_execution_nanoseconds;
    this->total_elapsed_real_nanoseconds      += elapsed_real_nanoseconds;
    this->total_elapsed_execution_nanoseconds += elapsed_execution_nanoseconds;
    this->current_index ++;
    if (this->current_index == this->average_count) {
      this->current_index = 0;
    }
  }
  raw__nanosleep(this->sleep_nanoseconds);
}

void funk2_poller__test() {
  funk2_poller_t poller;
  funk2_poller__init(&poller, 0.01, 1000);
  printf("\nfunk2_poller__test: poller.target_cpu_usage=%g", poller.target_cpu_usage);
  funk2_poller__reset(&poller);
  double temp = 10.0;
  {
    s64 i;
    for (i = 0; i < 100; i ++) {
      {
	s64 j;
	for (j = 0; j < 1000000; j ++) {
	  temp *= temp;
	}
      }
      printf("\nfunk2_poller__test: i=" s64__fstr " poller.average_cpu_usage=%g", i, poller.average_cpu_usage);
    }
  }
  printf("\nfunk2_poller__test: done.");
  printf("\n");
}
