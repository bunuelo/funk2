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

#ifndef F2__ATOMIC_U64__TYPES__H
#define F2__ATOMIC_U64__TYPES__H

#define ATOMIC_U64_DEBUG

typedef struct funk2_atomic_u64_s funk2_atomic_u64_t;

#endif // F2__ATOMIC_U64__TYPES__H


#ifndef F2__ATOMIC_U64__H
#define F2__ATOMIC_U64__H

// If a platform does not support atomic builtins, we could add a spinlock to this struct.
// First, we would need to require memblocks to call destroy on each reference count, when it is no longer needed.

#define ATOMIC_U64_MAGIC 0xBEADBEADBEADBEAD

struct funk2_atomic_u64_s {
#if defined(ATOMIC_U64_DEBUG)
  u64 magic;
#endif // ATOMIC_U64_DEBUG
  u64 value;
} __attribute__((aligned(8)));

void      funk2_atomic_u64__init            (funk2_atomic_u64_t* this, u64 value);
void      funk2_atomic_u64__destroy         (funk2_atomic_u64_t* this); // not currently called for memblocks.
boolean_t funk2_atomic_u64__compare_and_swap(funk2_atomic_u64_t* this, u64 old_value, u64 new_value);
u64       funk2_atomic_u64__set_value       (funk2_atomic_u64_t* this, u64 new_value);
u64       funk2_atomic_u64__increment       (funk2_atomic_u64_t* this);
u64       funk2_atomic_u64__decrement       (funk2_atomic_u64_t* this);

#if defined(ATOMIC_U64_DEBUG)
#  define funk2_atomic_u64__value(this) ({				\
      if ((to_ptr(this)) != (((to_ptr(this)) >> 3) << 3)) {		\
	status("funk2_atomic_u64__value not aligned.  this=" u64__fstr, (u64)to_ptr(this)); \
	status("funk2_atomic_u64__value not aligned.  this=" u64__fstr, (u64)to_ptr(this)); \
	error(nil, "funk2_atomic_u64__value not aligned.");		\
      }									\
      ((this)->value);							\
    })
#else
#  define funk2_atomic_u64__value(this) ((this)->value)
#endif // ATOMIC_U64_DEBUG

#endif // F2__ATOMIC_U64__H

