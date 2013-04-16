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

typedef struct funk2_atomic_u64_s funk2_atomic_u64_t;

#endif // F2__ATOMIC_U64__TYPES__H

#ifndef F2__ATOMIC_U64__H
#define F2__ATOMIC_U64__H

// If a platform does not support atomic builtins, we could add a spinlock to this struct.

struct funk2_atomic_u64_s {
  u64 value;
} __attribute__((aligned(8)));

void      funk2_atomic_u64__init            (funk2_atomic_u64_t* this);
void      funk2_atomic_u64__destroy         (funk2_atomic_u64_t* this);
boolean_t funk2_atomic_u64__compare_and_swap(funk2_atomic_u64_t* this, u64 old_value, u64 new_value);

#endif // F2__ATOMIC_U64__H

