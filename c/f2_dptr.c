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

// struct dptr

void funk2_dptr__init(funk2_dptr_t* this, f2ptr p, f2ptr tracing_on, f2ptr trace, f2ptr imagination_frame, f2ptr mutate_funks, f2ptr read_funks) {
  this->p                 = p;
#if defined(F2__USE_TRACED_DPTRS)
  this->tracing_on        = tracing_on;
  this->trace             = trace;
  this->imagination_frame = imagination_frame;
  this->mutate_funks      = mutate_funks;
  this->read_funks        = read_funks;
#endif // F2__USE_TRACED_DPTRS
}

boolean_t funk2_dptr__check_all_memory_pointers_valid_in_memory(funk2_dptr_t* this, funk2_memory_t* memory) {
  boolean_t found_invalid = boolean__false;
  found_invalid |= (! funk2_memory__is_reasonably_valid_used_funk2_memblock_ptr(memory, __f2ptr_to_ptr(this->p)));
#if defined(F2__USE_TRACED_DPTRS)
  found_invalid |= (! funk2_memory__is_reasonably_valid_used_funk2_memblock_ptr(memory, __f2ptr_to_ptr(this->tracing_on)));
  found_invalid |= (! funk2_memory__is_reasonably_valid_used_funk2_memblock_ptr(memory, __f2ptr_to_ptr(this->trace)));
  found_invalid |= (! funk2_memory__is_reasonably_valid_used_funk2_memblock_ptr(memory, __f2ptr_to_ptr(this->imagination_frame)));
  found_invalid |= (! funk2_memory__is_reasonably_valid_used_funk2_memblock_ptr(memory, __f2ptr_to_ptr(this->mutate_funks)));
  found_invalid |= (! funk2_memory__is_reasonably_valid_used_funk2_memblock_ptr(memory, __f2ptr_to_ptr(this->read_funks)));
#endif // F2__USE_TRACED_DPTRS
  return found_invalid;
}

void funk2_dptr__decrement_reference_counts(funk2_dptr_t* this, funk2_garbage_collector_t* garbage_collector) {
  funk2_memblock__decrement_reference_count((funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this->p)),                 this->p,                 garbage_collector);
#if defined(F2__USE_TRACED_DPTRS)
  funk2_memblock__decrement_reference_count((funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this->tracing_on)),        this->tracing_on,        garbage_collector);
  funk2_memblock__decrement_reference_count((funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this->trace)),             this->trace,             garbage_collector);
  funk2_memblock__decrement_reference_count((funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this->imagination_frame)), this->imagination_frame, garbage_collector);
  funk2_memblock__decrement_reference_count((funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this->mutate_funks)),      this->mutate_funks,      garbage_collector);
  funk2_memblock__decrement_reference_count((funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this->read_funks)),        this->read_funks,        garbage_collector);
#endif // F2__USE_TRACED_DPTRS
}

void funk2_dptr__grey_referenced_elements(funk2_dptr_t* this, funk2_garbage_collector_pool_t* garbage_collector_pool, int pool_index) {
  funk2_garbage_collector_pool__grey_maybe_other_element(garbage_collector_pool, pool_index, this->p);
#if defined(F2__USE_TRACED_DPTRS)
  funk2_garbage_collector_pool__grey_maybe_other_element(garbage_collector_pool, pool_index, this->tracing_on);
  funk2_garbage_collector_pool__grey_maybe_other_element(garbage_collector_pool, pool_index, this->trace);
  funk2_garbage_collector_pool__grey_maybe_other_element(garbage_collector_pool, pool_index, this->imagination_frame);
  funk2_garbage_collector_pool__grey_maybe_other_element(garbage_collector_pool, pool_index, this->mutate_funks);
  funk2_garbage_collector_pool__grey_maybe_other_element(garbage_collector_pool, pool_index, this->read_funks);
#endif // F2__USE_TRACED_DPTRS
}


