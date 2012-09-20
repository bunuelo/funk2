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

void funk2_processor_readwritelock__init(funk2_processor_readwritelock_t* this) {
  pthread_rwlock_init(&(this->pthread_rwlock), NULL);
}

void funk2_processor_readwritelock__destroy(funk2_processor_readwritelock_t* this) {
  pthread_rwlock_destroy(&(this->pthread_rwlock));
}

boolean_t funk2_processor_readwritelock__is_writelocked(funk2_processor_readwritelock_t* this) {
  if (pthread_rwlock_trywrlock(&(this->pthread_rwlock)) == 0) {
    pthread_rwlock_unlock(&(this->pthread_rwlock));
    return boolean__false;
  }
  return boolean__true;
}

boolean_t funk2_processor_readwritelock__is_readlocked(funk2_processor_readwritelock_t* this) {
  if (pthread_rwlock_tryrdlock(&(this->pthread_rwlock)) == 0) {
    pthread_rwlock_unlock(&(this->pthread_rwlock));
    return boolean__false;
  }
  return boolean__true;
}

funk2_processor_readwritelock_trylock_result_t funk2_processor_readwritelock__raw_trywritelock(funk2_processor_readwritelock_t* this, const char* writelock_source_file, const int writelock_line_num) {
  if (pthread_rwlock_trywrlock(&(this->pthread_rwlock)) == 0) {
    return funk2_processor_readwritelock_trylock_result__success;
  }
  return funk2_processor_readwritelock_trylock_result__failure;
}

funk2_processor_readwritelock_trylock_result_t funk2_processor_readwritelock__raw_tryreadlock(funk2_processor_readwritelock_t* this, const char* readlock_source_file, const int readlock_line_num) {
  if (pthread_rwlock_tryrdlock(&(this->pthread_rwlock)) == 0) {
    return funk2_processor_readwritelock_trylock_result__success;
  }
  return funk2_processor_readwritelock_trylock_result__failure;
}

void funk2_processor_readwritelock__raw_writelock(funk2_processor_readwritelock_t* this, const char* writelock_source_file, const int writelock_line_num) {
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

void funk2_processor_readwritelock__raw_readlock(funk2_processor_readwritelock_t* this, const char* readlock_source_file, const int readlock_line_num) {
  u64 readlock_tries = 0;
  while (funk2_processor_readwritelock__raw_tryreadlock(this, readlock_source_file, readlock_line_num) != funk2_processor_readwritelock_trylock_result__success) {
    readlock_tries ++;
    if (readlock_tries > 1000) {
      raw__spin_sleep_yield();
    } else {
      raw__fast_spin_sleep_yield();
    }
  }
}

void funk2_processor_readwritelock__raw_user_writelock(funk2_processor_readwritelock_t* this, const char* writelock_source_file, const int writelock_line_num) {
  u64 writelock_tries = 0;
  while (funk2_processor_readwritelock__raw_trywritelock(this, writelock_source_file, writelock_line_num) != funk2_processor_readwritelock_trylock_result__success) {
    if (__funk2.user_thread_controller.need_wait && pthread_self() != __funk2.memory.memory_handling_thread) {
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

void funk2_processor_readwritelock__raw_user_readlock(funk2_processor_readwritelock_t* this, const char* readlock_source_file, const int readlock_line_num) {
  u64 readlock_tries = 0;
  while (funk2_processor_readwritelock__raw_tryreadlock(this, readlock_source_file, readlock_line_num) != funk2_processor_readwritelock_trylock_result__success) {
    if (__funk2.user_thread_controller.need_wait && pthread_self() != __funk2.memory.memory_handling_thread) {
      funk2_user_thread_controller__user_wait_politely(&(__funk2.user_thread_controller));
    }
    {
      readlock_tries ++;
      if (readlock_tries > 1000) {
	raw__spin_sleep_yield();
      } else {
	raw__fast_spin_sleep_yield();
      }
    }
  }
}

void funk2_processor_readwritelock__raw_unlock(funk2_processor_readwritelock_t* this, const char* unwritelock_source_file, const int unwritelock_line_num) {
  pthread_rwlock_unlock(&(this->pthread_rwlock));
}

u64 funk2_processor_readwritelock__eq_hash_value(funk2_processor_readwritelock_t* this) {
  return (u64)to_ptr(this);
}

u64 funk2_processor_readwritelock__equals_hash_value(funk2_processor_readwritelock_t* this) {
  boolean_t is_writelocked = funk2_processor_readwritelock__is_writelocked(this);
  return is_writelocked ? 1 : 0;
}

