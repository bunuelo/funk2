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

u64 u64__sqrt (u64 n) {
  register u64 root;
  register u64 remainder;
  register u64 place;
  
  root = 0;
  remainder = n;
  place = 0x4000000000000000; // OR place = 0x4000; OR place = 0x40; - respectively
  
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

f2ptr raw__generate_primes(f2ptr cause, u64 prime_count) {
  u64* prime_array = (u64*)from_ptr(f2__malloc(sizeof(u64) * prime_count));
  prime_array[0] = 2;
  {
    u64 index;
    for (index = 1; index < prime_count; index ++) {
      u64 prime_guess = prime_array[index - 1];
      boolean_t is_prime = boolean__false;
      while (! is_prime) {
	prime_guess ++;
	is_prime = boolean__true;
	{
	  u64 prime_guess__sqrt = u64__sqrt(prime_guess);
	  u64 try_divisor_index;
	  for (try_divisor_index = 0; try_divisor_index < index; try_divisor_index ++) {
	    u64 try_divisor = prime_array[try_divisor_index];
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
      prime_array[index] = prime_guess;
    }
  }
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

f2ptr f2__generate_primes(f2ptr cause, f2ptr prime_count) {
  if (! raw__integer__is_type(cause, prime_count)) {
    return f2larva__new(cause, 1);
  }
  s64 prime_count__i = f2integer__i(prime_count, cause);
  if (prime_count__i < 0) {
    return f2larva__new(cause, 2);
  }
  return raw__generate_primes(cause, prime_count__i);
}
def_pcfunk1(generate_primes, prime_count, return f2__generate_primes(this_cause, prime_count));


// **

void f2__primes__reinitialize_globalvars() {
}

void f2__primes__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primes", "", &f2__primes__reinitialize_globalvars);
  
  f2__primes__reinitialize_globalvars();
  
  f2__primcfunk__init__1(generate_primes, prime_count, "generate the first <prime_count> prime numbers and return them in an array.");
}

