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

#if defined(F2__PROCESSOR_MUTEX__DEBUG)
void funk2_processor_mutex__error() {
  printf("\nfunk2_processor_mutex__error here.\n");
  error(nil, "funk2_processor_mutex__error here.");
}
#endif

void funk2_processor_mutex__init(funk2_processor_mutex_t* this) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  this->is_initialized    = boolean__true;
  this->initialized_magic = PROCESSOR_MUTEX__INITIALIZED_MAGIC;
  this->is_locked         = boolean__false;
  this->lock_source_file  = NULL;
  this->lock_line_num     = 0;
#endif
  //pthread_mutex_init(&(this->pthread_mutex), NULL);
  funk2_propogator_cell__init_input(&(this->is_locked_cell), 0);
}

void funk2_processor_mutex__destroy(funk2_processor_mutex_t* this) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if ((! this->is_initialized) ||
      (this->initialized_magic != PROCESSOR_MUTEX__INITIALIZED_MAGIC)) {
    printf("\nfunk2_processor_mutex__destroy error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
  this->is_initialized   = boolean__false;
  this->lock_source_file = "destroyed";
  this->lock_line_num    = 0;
#endif
  //pthread_mutex_destroy(&(this->pthread_mutex));
  funk2_propogator_cell__destroy(&(this->is_locked_cell));
}

boolean_t funk2_processor_mutex__is_locked(funk2_processor_mutex_t* this) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if ((! this->is_initialized) ||
      (this->initialized_magic != PROCESSOR_MUTEX__INITIALIZED_MAGIC)) {
    printf("\nfunk2_processor_mutex__is_locked error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
#endif
  //if (pthread_mutex_trylock(&(this->pthread_mutex)) == 0) {
  //pthread_mutex_unlock(&(this->pthread_mutex));
  //return boolean__false;
  //}
  //return boolean__true;
  return (funk2_propogator_cell__value(&(this->is_locked_cell)) != 0);
}

funk2_processor_mutex_trylock_result_t funk2_processor_mutex__raw_trylock(funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if ((! this->is_initialized) ||
      (this->initialized_magic != PROCESSOR_MUTEX__INITIALIZED_MAGIC)) {
    printf("\nfunk2_processor_mutex__raw_trylock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
#endif
  //if (pthread_mutex_trylock(&(this->pthread_mutex)) == 0) {
  u64       old_value = 0;
  u64       new_value = 1;
  boolean_t success   = funk2_propogator_cell__compare_and_swap(&(this->is_locked_cell), old_value, new_value);
  if (success) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
    this->is_locked        = boolean__true;
    this->lock_source_file = (char*)lock_source_file;
    this->lock_line_num    = (int)lock_line_num;
    this->lock_tid         = raw__gettid();
#endif
    return funk2_processor_mutex_trylock_result__success;
  }
  return funk2_processor_mutex_trylock_result__failure;
}

void funk2_processor_mutex__raw_lock(funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if ((! this->is_initialized) ||
      (this->initialized_magic != PROCESSOR_MUTEX__INITIALIZED_MAGIC)) {
    printf("\nfunk2_processor_mutex__raw_lock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
#endif
  //pthread_mutex_lock(&(this->pthread_mutex));
  boolean_t success = boolean__false;
  while (! success) {
    funk2_processor_mutex_trylock_result_t result = funk2_processor_mutex__raw_trylock(this, lock_source_file, lock_line_num);
    if (result == funk2_processor_mutex_trylock_result__success) {
      return;
    }
    funk2_propogator_cell__lock(&(this->is_locked_cell));
    while (funk2_propogator_cell__value(&(this->is_locked_cell)) != 0) {
      funk2_propogator_cell__wait(&(this->is_locked_cell));
    }
    funk2_propogator_cell__unlock(&(this->is_locked_cell));
  }
}

void funk2_processor_mutex__raw_user_lock(funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if ((! this->is_initialized) ||
      (this->initialized_magic != PROCESSOR_MUTEX__INITIALIZED_MAGIC)) {
    printf("\nfunk2_processor_mutex__raw_lock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
#endif
  {
    funk2_poller_t poller;
    boolean_t      poller_initialized = boolean__false;
    u64            lock_tries         = 0;
    while (funk2_processor_mutex__raw_trylock(this, lock_source_file, lock_line_num) != funk2_processor_mutex_trylock_result__success) {
      f2tid_t my_tid = raw__gettid();
      if (funk2_user_thread_controller__need_wait(&(__funk2.user_thread_controller)) &&
	  (my_tid != __funk2.memory.memory_handling_tid)) {
	funk2_user_thread_controller__user_wait_politely(&(__funk2.user_thread_controller));
      }
      {
	if (lock_tries < 1000) {
	  raw__fast_spin_sleep_yield();
	  lock_tries ++;
	} else {
	  if (! poller_initialized) {
	    funk2_poller__init_deep_sleep(&poller);
	    funk2_poller__reset(&poller);
	    poller_initialized = boolean__true;
	  } else {
	    funk2_poller__sleep(&poller);
	  }
	}
      }
    }
    if (poller_initialized) {
      funk2_poller__destroy(&poller);
    }
  }
}

void funk2_processor_mutex__raw_unlock(funk2_processor_mutex_t* this, const char* unlock_source_file, const int unlock_line_num) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if ((! this->is_initialized) ||
      (this->initialized_magic != PROCESSOR_MUTEX__INITIALIZED_MAGIC)) {
    printf("\nfunk2_processor_mutex__raw_unlock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
  this->is_locked = boolean__false;
#endif
  //pthread_mutex_unlock(&(this->pthread_mutex));
  u64       old_value = 1;
  u64       new_value = 0;
  boolean_t success   = funk2_propogator_cell__compare_and_swap(&(this->is_locked_cell), old_value, new_value);
  if (! success) {
    error(nil, "funk2_processor_mutex__raw_unlock: attempt to unlock mutex that is not locked.");
  }
}

u64 funk2_processor_mutex__eq_hash_value(funk2_processor_mutex_t* this) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if ((! this->is_initialized) ||
      (this->initialized_magic != PROCESSOR_MUTEX__INITIALIZED_MAGIC)) {
    printf("\nfunk2_processor_mutex__eq_hash_value error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
#endif
  return (u64)to_ptr(this);
}

u64 funk2_processor_mutex__equals_hash_value(funk2_processor_mutex_t* this) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if ((! this->is_initialized) ||
      (this->initialized_magic != PROCESSOR_MUTEX__INITIALIZED_MAGIC)) {
    printf("\nfunk2_processor_mutex__equals_hash_value error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
#endif
  boolean_t is_locked = funk2_processor_mutex__is_locked(this);
  return is_locked ? 1 : 0;
}

