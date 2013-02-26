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

#ifndef F2__PRIMES__H
#define F2__PRIMES__H

typedef struct funk2_primes_s funk2_primes_t;

struct funk2_primes_s {
  f2ptr prime_array__symbol;
  f2ptr prime_array;
};

f2ptr  f2__prime_array__new(f2ptr cause, f2ptr prime_count);
f2ptr raw__prime_array__new_by_extension(f2ptr cause, f2ptr this, u64 prime_count);
f2ptr  f2__prime_array__new_by_extension(f2ptr cause, f2ptr this, f2ptr prime_count);

f2ptr raw__prime(f2ptr cause, u64 prime_index);
f2ptr  f2__prime(f2ptr cause, f2ptr prime_index);

// **

void f2__primes__initialize();

#endif // F2__PRIMES__H

