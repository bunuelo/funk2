// 
// Copyright (c) 2007-2008 Bo Morgan.
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

void funk2_protected_alloc_array__init(funk2_protected_alloc_array_t* this) {
  this->used_num = 0;
  this->length   = 1024;
  this->data = (f2ptr*)from_ptr(f2__malloc(sizeof(f2ptr) * this->length));
  u64 i;
  for (i = 0; i < this->length; i ++) {
    this->data[i] = nil;
  }
  this->reentrance_count     = 0;
  this->max_reentrance_count = 0;
}

void funk2_protected_alloc_array__destroy(funk2_protected_alloc_array_t* this) {
  free(this->data);
}

void funk2_protected_alloc_array__add_protected_alloc_f2ptr(funk2_protected_alloc_array_t* this, f2ptr exp) {
  this->data[this->used_num] = exp;
  this->used_num ++;
  if (this->used_num >= this->length) {
    u64 old_length = this->length;
    this->length <<= 1;
    status("funk2_protected_alloc_array__add_protected_alloc_f2ptr: doubling size of protected_alloc_array from " u64__fstr " to " u64__fstr " f2ptrs.", old_length, this->length);
    this->data = from_ptr(f2__new_alloc(to_ptr(this->data), sizeof(f2ptr) * old_length, sizeof(f2ptr) * this->length));
  }
}

void found_max_reentrance(u64 max_reentrance_count) {
  status("found max reentrace count: " u64__fstr, max_reentrance_count);
}

void funk2_protected_alloc_array__signal_enter_protected_region(funk2_protected_alloc_array_t* this) {
  this->reentrance_count ++;
  if (this->reentrance_count > this->max_reentrance_count) {
    this->max_reentrance_count = this->reentrance_count;
    found_max_reentrance(this->max_reentrance_count);
  }
}

void funk2_protected_alloc_array__signal_exit_protected_region(funk2_protected_alloc_array_t* this) {
  if (this->reentrance_count == 0) {
    error(nil, "funk2_protected_alloc_array__signal_exit_protected_region error: bytecode reentrance underflow.");
  }
  this->reentrance_count --;
  if (this->reentrance_count == 0) {
    // protected counter is back to zero so reset used_num to zero.
    this->used_num = 0;
  }
}

boolean_t funk2_protected_alloc_array__in_protected_region(funk2_protected_alloc_array_t* this) {
  return (this->reentrance_count > 0);
}

