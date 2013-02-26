// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Tudor Golubenco (2008):
//
//     Original code for a gcc-specific replacement of asm/atomic.h in
//     the linux kernal, which is no longer available in user-space.  Bo
//     copied and adapted this code from this webpage:
//     http://golubenco.org/blog/atomic-operations/
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

#ifndef F2__ATOMIC__H
#define F2__ATOMIC__H
 
/**
 * Atomic type.
 */
 
typedef struct {
  volatile int counter;
} atomic_t;

#define ATOMIC_INIT(i)  { (i) }

/**
 * Read atomic variable
 * @param v pointer of type atomic_t
 *
 * Atomically reads the value of @v.
 */
#define atomic_read(v) ((v)->counter)
 
/**
 * Set atomic variable
 * @param v pointer of type atomic_t
 * @param i required value
 */
#define atomic_set(v,i) (((v)->counter) = (i))
 
/**
 * Add to the atomic variable
 * @param i integer value to add
 * @param v pointer of type atomic_t
 */
static inline void atomic_add( int i, atomic_t *v ) {
#if GCC_ATOMIC_BUILTINS
  (void)__sync_add_and_fetch(&v->counter, i);
#else
  v->counter += i;
#endif
}
 
/**
 * Subtract the atomic variable
 * @param i integer value to subtract
 * @param v pointer of type atomic_t
 *
 * Atomically subtracts @i from @v.
 */
static inline void atomic_sub( int i, atomic_t *v ) {
#if GCC_ATOMIC_BUILTINS
  (void)__sync_sub_and_fetch(&v->counter, i);
#else
  v->counter -= i;
#endif
}

/**
 * Subtract value from variable and test result
 * @param i integer value to subtract
 * @param v pointer of type atomic_t
 *
 * Atomically subtracts @i from @v and returns
 * true if the result is zero, or false for all
 * other cases.
 */
static inline int atomic_sub_and_test( int i, atomic_t *v ) {
#if GCC_ATOMIC_BUILTINS
  return !(__sync_sub_and_fetch(&v->counter, i));
#else
  v->counter -= i;
  return !(v->counter);
#endif
}

/**
 * Increment atomic variable
 * @param v pointer of type atomic_t
 *
 * Atomically increments @v by 1.
 */
static inline void atomic_inc( atomic_t *v ) {
#if GCC_ATOMIC_BUILTINS
  (void)__sync_fetch_and_add(&v->counter, 1);
#else
  v->counter ++;
#endif
}
 
/**
 * Increment atomic variable
 * @param v pointer of type atomic_t
 *
 * Atomically increments @v by 1 and
 * returns true if was zero before increment.
 */
static inline int atomic_test_and_inc( atomic_t *v ) {
#if GCC_ATOMIC_BUILTINS
  return !(__sync_fetch_and_add(&v->counter, 1));
#else
  return !(v->counter ++);
#endif
}
 
/**
 * @brief decrement atomic variable
 * @param v: pointer of type atomic_t
 *
 * Atomically decrements @v by 1.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */
static inline void atomic_dec( atomic_t *v ) {
#if GCC_ATOMIC_BUILTINS
  (void)__sync_fetch_and_sub(&v->counter, 1);
#else
  v->counter --;
#endif
}
 
/**
 * @brief Decrement and test
 * @param v pointer of type atomic_t
 *
 * Atomically decrements @v by 1 and
 * returns true if the result is 0, or false for all other
 * cases.
 */
static inline int atomic_dec_and_test( atomic_t *v ) {
#if GCC_ATOMIC_BUILTINS
  return !(__sync_sub_and_fetch(&v->counter, 1));
#else
  v->counter --;
  return !(v->counter);
#endif
}
 
/**
 * @brief Increment and test
 * @param v pointer of type atomic_t
 *
 * Atomically increments @v by 1
 * and returns true if the result is zero, or false for all
 * other cases.
 */
static inline int atomic_inc_and_test( atomic_t *v ) {
#if GCC_ATOMIC_BUILTINS
  return !(__sync_add_and_fetch(&v->counter, 1));
#else
  v->counter ++;
  return !(v->counter);
#endif
}

/**
 * @brief add and test if negative
 * @param v pointer of type atomic_t
 * @param i integer value to add
 *
 * Atomically adds @i to @v and returns true
 * if the result is negative, or false when
 * result is greater than or equal to zero.
 */
static inline int atomic_add_negative( int i, atomic_t *v ) {
#if GCC_ATOMIC_BUILTINS
  return (((int)(__sync_add_and_fetch(&v->counter, i))) < 0);
#else
  v->counter ++;
  return (v->counter < 0);
#endif
}
 
#endif
