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

#if defined(F2__PROCESSOR_READWRITELOCK__DEBUG)
void funk2_processor_readwritelock__error() {
  printf("\nfunk2_processor_readwritelock__error here.\n");
  error(nil, "funk2_processor_readwritelock__error here.");
}
#endif

void funk2_processor_readwritelock__init(funk2_processor_readwritelock_t* this) {
#if defined(F2__PROCESSOR_READWRITELOCK__DEBUG)
  this->is_initialized   = boolean__true;
  this->is_writelocked        = boolean__false;
  this->writelock_source_file = NULL;
  this->writelock_line_num    = 0;
#endif
  pthread_rwlock_init(&(this->pthread_rwlock), NULL);
}

void funk2_processor_readwritelock__destroy(funk2_processor_readwritelock_t* this) {
#if defined(F2__PROCESSOR_READWRITELOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_readwritelock__destroy error: attempted to use uninitialized readwritelock.\n"); fflush(stdout);
    funk2_processor_readwritelock__error();
  }
  this->is_initialized   = boolean__false;
  this->writelock_source_file = "destroyed";
  this->writelock_line_num    = 0;
#endif
  pthread_rwlock_destroy(&(this->pthread_rwlock));
}

boolean_t funk2_processor_readwritelock__is_writelocked(funk2_processor_readwritelock_t* this) {
#if defined(F2__PROCESSOR_READWRITELOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_readwritelock__is_locked error: attempted to use uninitialized readwritelock.\n"); fflush(stdout);
    funk2_processor_readwritelock__error();
  }
#endif
  if (pthread_rwlock_trywrlock(&(this->pthread_rwlock)) == 0) {
    pthread_rwlock_unwrlock(&(this->pthread_rwlock));
    return boolean__false;
  }
  return boolean__true;
}

funk2_processor_readwritelock_trylock_result_t funk2_processor_readwritelock__raw_trywritelock(funk2_processor_readwritelock_t* this, const char* writelock_source_file, const int writelock_line_num) {
#if defined(F2__PROCESSOR_READWRITELOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_readwritelock__raw_trylock error: attempted to use uninitialized readwritelock.\n"); fflush(stdout);
    funk2_processor_readwritelock__error();
  }
#endif
  if (pthread_rwlock_trywrlock(&(this->pthread_rwlock)) == 0) {
#if defined(F2__PROCESSOR_READWRITELOCK__DEBUG)
    this->is_writelocked        = boolean__true;
    this->writelock_source_file = (char*)writelock_source_file;
    this->writelock_line_num    = (int)writelock_line_num;
    this->writelock_tid         = pthread_self();
#endif
    return funk2_processor_readwritelock_trylock_result__success;
  }
  return funk2_processor_readwritelock_trylock_result__failure;
}

void funk2_processor_readwritelock__raw_writelock(funk2_processor_readwritelock_t* this, const char* writelock_source_file, const int writelock_line_num) {
#if defined(F2__PROCESSOR_READWRITELOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_readwritelock__raw_lock error: attempted to use uninitialized readwritelock.\n"); fflush(stdout);
    funk2_processor_readwritelock__error();
  }
#endif
  {
    u64 writelock_tries = 0;
    while (funk2_processor_readwritelock__raw_trywritelock(this, writelock_source_file, writelock_line_num) != funk2_processor_readwritelock_trylock_result__success) {
      writelock_tries ++;
      if (writelock_tries > 1000) {
	raw__spin_sleep_yield();
      } else {
	raw__fast_spin_sleep_yield();
      }
    }
  }
}

void funk2_processor_readwritelock__raw_user_writelock(funk2_processor_readwritelock_t* this, const char* writelock_source_file, const int writelock_line_num) {
#if defined(F2__PROCESSOR_READWRITELOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_readwritelock__raw_lock error: attempted to use uninitialized readwritelock.\n"); fflush(stdout);
    funk2_processor_readwritelock__error();
  }
#endif
  {
    u64 writelock_tries = 0;
    while (funk2_processor_readwritelock__raw_trywritelock(this, writelock_source_file, writelock_line_num) != funk2_processor_readwritelock_trylock_result__success) {
      if (__funk2.user_thread_controller.please_wait && pthread_self() != __funk2.memory.memory_handling_thread) {
	funk2_user_thread_controller__user_wait_politely(&(__funk2.user_thread_controller));
      }
      {
	writelock_tries ++;
	if (writelock_tries > 1000) {
	  raw__spin_sleep_yield();
	} else {
	  raw__fast_spin_sleep_yield();
	}
      }
    }
  }
}

void funk2_processor_readwritelock__raw_unwritelock(funk2_processor_readwritelock_t* this, const char* unwritelock_source_file, const int unwritelock_line_num) {
#if defined(F2__PROCESSOR_READWRITELOCK__DEBUG)
  if (! this->is_initialized) {
    printf("\nfunk2_processor_readwritelock__raw_unlock error: attempted to use uninitialized readwritelock.\n"); fflush(stdout);
    funk2_processor_readwritelock__error();
  }
  this->is_writelocked = boolean__false;
#endif
  pthread_rwlock_unwritelock(&(this->pthread_rwlock));
}

u64 funk2_processor_readwritelock__eq_hash_value(funk2_processor_readwritelock_t* this) {
  return (u64)to_ptr(this);
}

u64 funk2_processor_readwritelock__equals_hash_value(funk2_processor_readwritelock_t* this) {
  boolean_t is_writelocked = funk2_processor_readwritelock__is_writelocked(this);
  return is_writelocked ? 1 : 0;
}

