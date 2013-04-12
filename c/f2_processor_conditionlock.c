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

void funk2_processor_conditionlock__init(funk2_processor_conditionlock_t* this) {
  pthread_mutex_init(&(this->mutex), NULL);
  pthread_cond_init(&(this->cond), NULL);
}

void funk2_processor_conditionlock__destroy(funk2_processor_conditionlock_t* this) {
  pthread_mutex_destroy(&(this->mutex));
  pthread_cond_destroy(&(this->cond));
}

s64 funk2_processor_conditionlock__trylock(funk2_processor_conditionlock_t* this) {
  return pthread_mutex_trylock(&(this->mutex));
}

s64 funk2_processor_conditionlock__lock(funk2_processor_conditionlock_t* this) {
  return pthread_mutex_lock(&(this->mutex));
}

s64 funk2_processor_conditionlock__unlock(funk2_processor_conditionlock_t* this) {
  return pthread_mutex_unlock(&(this->mutex));
}

s64 funk2_processor_conditionlock__wait(funk2_processor_conditionlock_t* this) {
  return pthread_cond_wait(&(this->cond), &(this->mutex));
}

s64 funk2_processor_conditionlock__signal(funk2_processor_conditionlock_t* this) {
  return pthread_cond_signal(&(this->cond));
}

s64 funk2_processor_conditionlock__broadcast(funk2_processor_conditionlock_t* this) {
  return pthread_cond_broadcast(&(this->cond));
}

