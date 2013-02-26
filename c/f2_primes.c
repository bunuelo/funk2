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

// returned data must be f2__free'd to release memory resources allocated in this function
void raw__u64_prime_array__extend(u64 valid_length, u64 this__length, u64* this) {
  u64 index;
  for (index = valid_length; index < this__length; index ++) {
    u64 prime_guess = this[index - 1];
    boolean_t is_prime = boolean__false;
    while (! is_prime) {
      prime_guess ++;
      is_prime = boolean__true;
      {
	u64 prime_guess__sqrt = u64__sqrt(prime_guess);
	u64 try_divisor_index;
	for (try_divisor_index = 0; try_divisor_index < index; try_divisor_index ++) {
	  u64 try_divisor = this[try_divisor_index];
	  if (try_divisor > prime_guess__sqrt) {
	    break;
	  }
	  if (prime_guess % try_divisor == 0) {
	    is_prime = boolean__false;
	    break;
	  }
	}
      }
    }
    this[index] = prime_guess;
  }
}

// returned data must be f2__free'd to release memory resources allocated in this function
u64* raw__u64_prime_array__new_by_extension(u64 this__length, u64* this, u64 new_prime_array__length) {
  u64* new_prime_array = (u64*)from_ptr(f2__malloc(sizeof(u64) * new_prime_array__length));
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      new_prime_array[index] = this[index];
    }
    raw__u64_prime_array__extend(this__length, new_prime_array__length, new_prime_array);
  }
  return new_prime_array;
}

// returned data must be f2__free'd to release memory resources allocated in this function
u64* raw__u64_prime_array__new(u64 prime_array__length) {
  u64 first_prime = 2;
  return raw__u64_prime_array__new_by_extension(1, &first_prime, prime_array__length);
}

f2ptr raw__prime_array__new(f2ptr cause, u64 prime_count) {
  u64* prime_array = raw__u64_prime_array__new(prime_count);
  f2ptr result = raw__array__new(cause, prime_count);
  {
    u64 index;
    for (index = 0; index < prime_count; index ++) {
      raw__array__elt__set(cause, result, index, f2integer__new(cause, prime_array[index]));
    }
  }
  f2__free(to_ptr(prime_array));
  return result;
}

f2ptr f2__prime_array__new(f2ptr cause, f2ptr prime_count) {
  assert_argument_type(integer, prime_count);
  s64 prime_count__i = f2integer__i(prime_count, cause);
  if (prime_count__i < 0) {
    return f2larva__new(cause, 2, nil);
  }
  return raw__prime_array__new(cause, prime_count__i);
}
def_pcfunk1(prime_array__new, prime_count,
	    "generate the first <prime_count> prime numbers and return them in an array., """,
	    return f2__prime_array__new(this_cause, prime_count));

f2ptr raw__prime_array__new_by_extension(f2ptr cause, f2ptr this, u64 prime_count) {
  assert_argument_type(array, this);
  u64 this__length = raw__array__length(cause, this);
  if (this__length == 0) {
    return f2larva__new(cause, 2, nil);
  }
  u64   prime_array__length = prime_count;
  f2ptr prime_array         = raw__array__new(cause, prime_array__length);
  {
    u64   u64_prime_array__length = prime_count;
    u64*  u64_prime_array         = (u64*)from_ptr(f2__malloc(sizeof(u64) * u64_prime_array__length));
    {
      u64 index;
      for (index = 0; index < this__length; index ++) {
	f2ptr elt = raw__array__elt(cause, this, index);
	if (! raw__integer__is_type(cause, elt)) {
	  f2__free(to_ptr(prime_array));
	  return f2larva__new(cause, 1, nil);
	}
	u64 elt__i = f2integer__i(elt, cause);
	u64_prime_array[index] = elt__i;
      }
    }
    raw__u64_prime_array__extend(this__length, u64_prime_array__length, u64_prime_array);
    {
      u64 index;
      for (index = 0; index < prime_array__length; index ++) {
	raw__array__elt__set(cause, prime_array, index, f2integer__new(cause, u64_prime_array[index]));
      }
    }
  }
  return prime_array;
}

f2ptr f2__prime_array__new_by_extension(f2ptr cause, f2ptr this, f2ptr prime_count) {
  assert_argument_type(integer, prime_count);
  u64 prime_count__i = f2integer__i(prime_count, cause);
  return raw__prime_array__new_by_extension(cause, this, prime_count__i);
}
def_pcfunk2(prime_array__new_by_extension, this, prime_count,
	    "generate the first <prime_count> prime numbers by extending a shorted array of prime numbers.",
	    return f2__prime_array__new_by_extension(this_cause, this, prime_count));

// funk2_primes_t

void funk2_primes__reinit(funk2_primes_t* this, f2ptr cause) {
  this->prime_array__symbol = new__symbol(cause, "prime_array");
  this->prime_array         = nil;
}

void funk2_primes__init(funk2_primes_t* this, f2ptr cause) {
  funk2_primes__reinit(this, cause);
}

void funk2_primes__defragment__fix_pointers(funk2_primes_t* this) {
  // -- reinitialize --
  
  defragment__fix_pointer(this->prime_array__symbol);
  defragment__fix_pointer(this->prime_array);
  
  // -- initialize --
  
}

void funk2_primes__destroy(funk2_primes_t* this) {
}

f2ptr funk2_primes__prime(funk2_primes_t* this, f2ptr cause, u64 prime_index) {
  f2ptr prime_array = this->prime_array;
  if (prime_array == nil) {
    prime_array = raw__prime_array__new(cause, prime_index + 1);
  }
  u64 prime_array__length = raw__array__length(cause, prime_array);
  if (prime_index >= prime_array__length) {
    prime_array = raw__prime_array__new_by_extension(cause, prime_array, prime_index + (prime_index >> 2) + 1);
  }
  this->prime_array = prime_array;
  environment__add_var_value(cause, global_environment(), this->prime_array__symbol, this->prime_array);
  return raw__array__elt(cause, prime_array, prime_index);
}

f2ptr raw__prime(f2ptr cause, u64 prime_index) {
  return funk2_primes__prime(&(__funk2.primes), cause, prime_index);
}

f2ptr f2__prime(f2ptr cause, f2ptr prime_index) {
  assert_argument_type(integer, prime_index);
  u64 prime_index__i = f2integer__i(prime_index, cause);
  return raw__prime(cause, prime_index__i);
}
def_pcfunk1(prime, prime_index,
	    "return the <prime_index>'th prime (index 0 => 2, index 1 => 3, index 2 => 5, etc.)",
	    return f2__prime(this_cause, prime_index));

// **

void f2__primes__defragment__fix_pointers() {
  // -- reinitialize --
  
  funk2_primes__defragment__fix_pointers(&(__funk2.primes));
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(prime_array__new);
  f2__primcfunk__init__defragment__fix_pointers(prime_array__new_by_extension);
  f2__primcfunk__init__defragment__fix_pointers(prime);
}

void f2__primes__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  funk2_primes__reinit(&(__funk2.primes), cause);
  
  f2__primcfunk__init__1(prime_array__new, prime_count);
  f2__primcfunk__init__2(prime_array__new_by_extension, this, prime_count);
  f2__primcfunk__init__1(prime, prime_index);
}

void f2__primes__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primes", "", &f2__primes__reinitialize_globalvars, &f2__primes__defragment__fix_pointers);
  
  f2ptr cause = initial_cause();
  funk2_primes__init(&(__funk2.primes), cause);
  
  f2__primes__reinitialize_globalvars();
}

