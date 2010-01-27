// 
// Copyright (c) 2007-2009 Bo Morgan.
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

u64 u64__sqrt(u64 this) {
  register u64 root;
  register u64 remainder;
  register u64 place;
  
  root = 0;
  remainder = this;
  place = 0x4000000000000000;
  
  while (place > remainder) {
    place = place >> 2;
  }
  
  while (place) {
    if (remainder >= root + place) {
      remainder = remainder - root - place;
      root = root + (place << 1);
    }
    root = root >> 1;
    place = place >> 2;
  }
  return root;
}

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
  if (! raw__integer__is_type(cause, prime_count)) {
    return f2larva__new(cause, 1);
  }
  s64 prime_count__i = f2integer__i(prime_count, cause);
  if (prime_count__i < 0) {
    return f2larva__new(cause, 2);
  }
  return raw__prime_array__new(cause, prime_count__i);
}
def_pcfunk1(prime_array__new, prime_count, return f2__prime_array__new(this_cause, prime_count));

f2ptr f2__prime_array__new_by_extension(f2ptr cause, f2ptr this, f2ptr prime_count) {
  if ((! raw__array__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, prime_count))) {
    return f2larva__new(cause, 1);
  }
  u64 this__length = raw__array__length(cause, this);
  if (this__length == 0) {
    return f2larva__new(cause, 2);
  }
  f2ptr prime_count__i      = f2integer__i(prime_count, cause);
  u64   prime_array__length = prime_count__i;
  f2ptr prime_array         = raw__array__new(cause, prime_array__length);
  {
    u64   u64_prime_array__length = prime_count__i;
    u64*  u64_prime_array         = (u64*)f2__malloc(sizeof(u64) * u64_prime_array__length);
    {
      u64 index;
      for (index = 0; index < this__length; index ++) {
	f2ptr elt = raw__array__elt(cause, this, index);
	if (! raw__integer__is_type(cause, elt)) {
	  f2__free(to_ptr(prime_array));
	  return f2larva__new(cause, 1);
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
def_pcfunk2(prime_array__new_by_extension, this, prime_count, return f2__prime_array__new_by_extension(this_cause, this, prime_count));

// **

void f2__primes__reinitialize_globalvars() {
}

void f2__primes__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primes", "", &f2__primes__reinitialize_globalvars);
  
  f2__primes__reinitialize_globalvars();
  
  f2__primcfunk__init__1(prime_array__new, prime_count, "generate the first <prime_count> prime numbers and return them in an array.");
  f2__primcfunk__init__2(prime_array__new_by_extension, this, prime_count, "generate the first <prime_count> prime numbers by extending a shorted array of prime numbers.");
}

