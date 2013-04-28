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

#if defined(F2__PROCESSOR_SPINLOCK__DEBUG)
void funk2_processor_spinlock__error() {
  printf("\nfunk2_processor_spinlock__error here.\n");
  error(nil, "funk2_processor_spinlock__error here.");
}
#endif

void funk2_processor_spinlock__init(funk2_processor_spinlock_t* this) {
#if defined(F2__PROCESSOR_SPINLOCK__DEBUG)
  this->is_initialized   = boolean__true;
  this->is_locked        = boolean__false;
  this->lock_source_file = NULL;
  this->lock_line_num    = 0;
#endif
  pthread_spin_init(&(this->pthread_spin), PTHREAD_PROCESS_PRIVATE);
}

void funk2_processor_spinlock__destroy(funk2_processor_spinlock_t* this) {
#if defined(F2__PROCESSOR_SPINLOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_spinlock__destroy error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_spinlock__error();
  }
  this->is_initialized   = boolean__false;
  this->lock_source_file = "destroyed";
  this->lock_line_num    = 0;
#endif
  pthread_spin_destroy(&(this->pthread_spin));
}

boolean_t funk2_processor_spinlock__is_locked(funk2_processor_spinlock_t* this) {
#if defined(F2__PROCESSOR_SPINLOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_spinlock__is_locked error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_spinlock__error();
  }
#endif
  if (pthread_spin_trylock(&(this->pthread_spin)) == 0) {
    pthread_spin_unlock(&(this->pthread_spin));
    return boolean__false;
  }
  return boolean__true;
}

funk2_processor_spinlock_trylock_result_t funk2_processor_spinlock__raw_trylock(funk2_processor_spinlock_t* this, const char* lock_source_file, const int lock_line_num) {
#if defined(F2__PROCESSOR_SPINLOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_spinlock__raw_trylock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_spinlock__error();
  }
#endif
  if (pthread_spin_trylock(&(this->pthread_spin)) == 0) {
#if defined(F2__PROCESSOR_SPINLOCK__DEBUG)
    this->is_locked        = boolean__true;
    this->lock_source_file = (char*)lock_source_file;
    this->lock_line_num    = (int)lock_line_num;
    this->lock_tid         = raw__gettid();
#endif
    return funk2_processor_spinlock_trylock_result__success;
  }
  return funk2_processor_spinlock_trylock_result__failure;
}

void funk2_processor_spinlock__raw_lock(funk2_processor_spinlock_t* this, const char* lock_source_file, const int lock_line_num) {
#if defined(F2__PROCESSOR_SPINLOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_spinlock__raw_lock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_spinlock__error();
  }
#endif
  pthread_spin_lock(&(this->pthread_spin));
}

void funk2_processor_spinlock__raw_user_lock(funk2_processor_spinlock_t* this, const char* lock_source_file, const int lock_line_num) {
#if defined(F2__PROCESSOR_SPINLOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_spinlock__raw_lock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_spinlock__error();
  }
#endif
  {
    funk2_poller_t poller;
    boolean_t      poller_initialized = boolean__false;
    u64            lock_tries         = 0;
    while (funk2_processor_spinlock__raw_trylock(this, lock_source_file, lock_line_num) != funk2_processor_spinlock_trylock_result__success) {
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
	    f2__this__fiber__yield(nil);
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

void funk2_processor_spinlock__raw_unlock(funk2_processor_spinlock_t* this, const char* unlock_source_file, const int unlock_line_num) {
#if defined(F2__PROCESSOR_SPINLOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_spinlock__raw_unlock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_spinlock__error();
  }
  this->is_locked = boolean__false;
#endif
  pthread_spin_unlock(&(this->pthread_spin));
}

u64 funk2_processor_spinlock__eq_hash_value(funk2_processor_spinlock_t* this) {
  return (u64)to_ptr(this);
}

u64 funk2_processor_spinlock__equals_hash_value(funk2_processor_spinlock_t* this) {
  boolean_t is_locked = funk2_processor_spinlock__is_locked(this);
  return is_locked ? 1 : 0;
}

