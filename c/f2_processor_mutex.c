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

#if defined(F2__PROCESSOR_MUTEX__DEBUG)
void funk2_processor_mutex__error() {
  printf("\nfunk2_processor_mutex__error here.\n");
  exit(-1);
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
  while (funk2_processor_mutex__raw_trylock(this, lock_source_file, lock_line_num) != funk2_processor_mutex_trylock_result__success) {
    sched_yield();
    if (__ptypes_please_wait_for_gc_to_take_place && pthread_self() != __funk2.memory.memory_handling_thread) {
      wait_politely();
    }
    //f2__sleep(1);
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


