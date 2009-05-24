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

void funk2_processor_mutex__init(funk2_processor_mutex_t* this) {
  this->is_locked        = boolean__false;
  this->lock_source_file = NULL;
  this->lock_line_num    = 0;
  pthread_mutex_init(&(this->pthread_mutex), NULL);
}

void funk2_processor_mutex__destroy(funk2_processor_mutex_t* this) {
  pthread_mutex_destroy(&(this->pthread_mutex));
}

funk2_processor_mutex_trylock_result_t funk2_processor_mutex__raw_trylock(funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num) {
  if (pthread_mutex_trylock(&(this->pthread_mutex)) == 0) {
    this->is_locked        = boolean__true;
    this->lock_source_file = (char*)lock_source_file;
    this->lock_line_num    = (int)lock_line_num;
    return funk2_processor_mutex_trylock_result__success;
  }
  return funk2_processor_mutex_trylock_result__failure;
}

void funk2_processor_mutex__raw_lock(funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num) {
  while (funk2_processor_mutex__raw_trylock(this, lock_source_file, lock_line_num) != funk2_processor_mutex_trylock_result__success) {
    sched_yield();
    //f2__sleep(1);
  }
}

void funk2_processor_mutex__raw_unlock(funk2_processor_mutex_t* this, const char* unlock_source_file, const int unlock_line_num) {
  this->is_locked = boolean__false;
  pthread_mutex_unlock(&(this->pthread_mutex));
}


