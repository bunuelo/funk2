// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#if defined(F2__PROCESSOR_MUTEX__DEBUG)
void funk2_processor_mutex__error() {
  printf("\nfunk2_processor_mutex__error here.\n");
  error(nil, "funk2_processor_mutex__error here.");
}
#endif

void funk2_processor_mutex__init(funk2_processor_mutex_t* this) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  this->is_initialized   = boolean__true;
  this->is_locked        = boolean__false;
  this->lock_source_file = NULL;
  this->lock_line_num    = 0;
#endif
  pthread_mutex_init(&(this->pthread_mutex), NULL);
}

void funk2_processor_mutex__destroy(funk2_processor_mutex_t* this) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_mutex__destroy error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
  this->is_initialized   = boolean__false;
  this->lock_source_file = "destroyed";
  this->lock_line_num    = 0;
#endif
  pthread_mutex_destroy(&(this->pthread_mutex));
}

boolean_t funk2_processor_mutex__is_locked(funk2_processor_mutex_t* this) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_mutex__is_locked error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
#endif
  if (pthread_mutex_trylock(&(this->pthread_mutex)) == 0) {
    pthread_mutex_unlock(&(this->pthread_mutex));
    return boolean__false;
  }
  return boolean__true;
}

funk2_processor_mutex_trylock_result_t funk2_processor_mutex__raw_trylock(funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_mutex__raw_trylock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
#endif
  if (pthread_mutex_trylock(&(this->pthread_mutex)) == 0) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
    this->is_locked        = boolean__true;
    this->lock_source_file = (char*)lock_source_file;
    this->lock_line_num    = (int)lock_line_num;
    this->lock_tid         = pthread_self();
#endif
    return funk2_processor_mutex_trylock_result__success;
  }
  return funk2_processor_mutex_trylock_result__failure;
}

void funk2_processor_mutex__raw_lock(funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_mutex__raw_lock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
#endif
  {
    u64 lock_tries = 0;
    while (funk2_processor_mutex__raw_trylock(this, lock_source_file, lock_line_num) != funk2_processor_mutex_trylock_result__success) {
      lock_tries ++;
      if (lock_tries < 1000) {
	// spin fast
      } else if (lock_tries < 2000) {
	raw__fast_spin_sleep_yield();
      } else {
	raw__spin_sleep_yield();
      }
    }
  }
}

void funk2_processor_mutex__raw_user_lock(funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_mutex__raw_lock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
#endif
  {
    u64 lock_tries = 0;
    while (funk2_processor_mutex__raw_trylock(this, lock_source_file, lock_line_num) != funk2_processor_mutex_trylock_result__success) {
      if (__funk2.user_thread_controller.need_wait &&
	  (pthread_self() != __funk2.memory.memory_handling_thread)) {
	funk2_user_thread_controller__user_wait_politely(&(__funk2.user_thread_controller));
      }
      {
	if (lock_tries > 1000) {
	  raw__spin_sleep_yield();
	} else {
	  lock_tries ++;
	}
	f2__this__fiber__yield(cause);
      }
    }
  }
}

void funk2_processor_mutex__raw_unlock(funk2_processor_mutex_t* this, const char* unlock_source_file, const int unlock_line_num) {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_mutex__raw_unlock error: attempted to use uninitialized mutex.\n"); fflush(stdout);
    funk2_processor_mutex__error();
  }
  this->is_locked = boolean__false;
#endif
  pthread_mutex_unlock(&(this->pthread_mutex));
}

u64 funk2_processor_mutex__eq_hash_value(funk2_processor_mutex_t* this) {
  return (u64)to_ptr(this);
}

u64 funk2_processor_mutex__equals_hash_value(funk2_processor_mutex_t* this) {
  boolean_t is_locked = funk2_processor_mutex__is_locked(this);
  return is_locked ? 1 : 0;
}

