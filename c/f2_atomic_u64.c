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

void funk2_atomic_u64__init(funk2_atomic_u64_t* this, u64 value) {
#if defined(ATOMIC_U64_DEBUG)
  this->magic = ATOMIC_U64_MAGIC;
  if ((to_ptr(this)) != (((to_ptr(this)) >> 3) << 3)) {
    status("funk2_atomic_u64__init not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    status("funk2_atomic_u64__init not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    error(nil, "funk2_atomic_u64__init not aligned.");
  }
#endif // ATOMIC_U64_DEBUG
  this->value = value;
}

void funk2_atomic_u64__destroy(funk2_atomic_u64_t* this) {
#if defined(ATOMIC_U64_DEBUG)
  if (this->magic != ATOMIC_U64_MAGIC) {
    error(nil, "funk2_atomic_u64__destroy no magic.");
  }
  if ((to_ptr(this)) != (((to_ptr(this)) >> 3) << 3)) {
    status("funk2_atomic_u64__destroy not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    status("funk2_atomic_u64__destroy not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    error(nil, "funk2_atomic_u64__destroy not aligned.");
  }
#endif // ATOMIC_U64_DEBUG
}

boolean_t funk2_atomic_u64__compare_and_swap(funk2_atomic_u64_t* this, u64 old_value, u64 new_value) {
#if defined(ATOMIC_U64_DEBUG)
  if (this->magic != ATOMIC_U64_MAGIC) {
    error(nil, "funk2_atomic_u64__compare_and_swap no magic.");
  }
  if ((to_ptr(this)) != (((to_ptr(this)) >> 3) << 3)) {
    status("funk2_atomic_u64__compare_and_swap not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    status("funk2_atomic_u64__compare_and_swap not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    error(nil, "funk2_atomic_u64__compare_and_swap not aligned.");
  }
#endif // ATOMIC_U64_DEBUG
  boolean_t success = __sync_bool_compare_and_swap(&(this->value), old_value, new_value);
  return success;
}

u64 funk2_atomic_u64__set_value(funk2_atomic_u64_t* this, u64 new_value) {
#if defined(ATOMIC_U64_DEBUG)
  if (this->magic != ATOMIC_U64_MAGIC) {
    error(nil, "funk2_atomic_u64__set_value no magic.");
  }
  if ((to_ptr(this)) != (((to_ptr(this)) >> 3) << 3)) {
    status("funk2_atomic_u64__set_value not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    status("funk2_atomic_u64__set_value not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    error(nil, "funk2_atomic_u64__set_value not aligned.");
  }
#endif // ATOMIC_U64_DEBUG
  u64       old_value;
  boolean_t success = boolean__false;;
  while (! success) {
    old_value = funk2_atomic_u64__value(this);
    success   = funk2_atomic_u64__compare_and_swap(this, old_value, new_value);
  }
  return old_value;
}

u64 funk2_atomic_u64__increment(funk2_atomic_u64_t* this) {
#if defined(ATOMIC_U64_DEBUG)
  if (this->magic != ATOMIC_U64_MAGIC) {
    error(nil, "funk2_atomic_u64__increment no magic.");
  }
  if ((to_ptr(this)) != (((to_ptr(this)) >> 3) << 3)) {
    status("funk2_atomic_u64__increment not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    status("funk2_atomic_u64__increment not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    error(nil, "funk2_atomic_u64__increment not aligned.");
  }
#endif // ATOMIC_U64_DEBUG
  u64 old_value;
  u64 new_value;
  {
    boolean_t success = boolean__false;
    while (! success) {
      old_value = funk2_atomic_u64__value(this);
      new_value = old_value + 1;
      success = funk2_atomic_u64__compare_and_swap(this, old_value, new_value);
    }
  }
  return new_value;
}

u64 funk2_atomic_u64__decrement(funk2_atomic_u64_t* this) {
#if defined(ATOMIC_U64_DEBUG)
  if (this->magic != ATOMIC_U64_MAGIC) {
    error(nil, "funk2_atomic_u64__decrement no magic.");
  }
  if ((to_ptr(this)) != (((to_ptr(this)) >> 3) << 3)) {
    status("funk2_atomic_u64__decrement not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    status("funk2_atomic_u64__decrement not aligned.  this=" u64__fstr, (u64)to_ptr(this));
    error(nil, "funk2_atomic_u64__decrement not aligned.");
  }
#endif // ATOMIC_U64_DEBUG
  u64 old_value;
  u64 new_value;
  {
    boolean_t success = boolean__false;
    while (! success) {
      old_value = funk2_atomic_u64__value(this);
      new_value = old_value - 1;
      success = funk2_atomic_u64__compare_and_swap(this, old_value, new_value);
    }
  }
  return new_value;
}

