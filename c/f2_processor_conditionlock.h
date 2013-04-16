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

#ifndef F2__PROCESSOR_CONDITIONLOCK__TYPES__H
#define F2__PROCESSOR_CONDITIONLOCK__TYPES__H

typedef struct funk2_processor_conditionlock_s funk2_processor_conditionlock_t;

//#define F2__DEBUG__PROCESSOR_CONDITIONLOCK

#endif // F2__PROCESSOR_CONDITIONLOCK__TYPES__H


#ifndef F2__PROCESSOR_CONDITIONLOCK__H
#define F2__PROCESSOR_CONDITIONLOCK__H

#include "f2_global.h"

#define PROCESSOR_CONDTIONLOCK_MAGIC ((u64)0xFEEDDEADFEEDDEAD)

struct funk2_processor_conditionlock_s {
  u64             initialized_magic;
  pthread_mutex_t mutex;
  pthread_cond_t  cond;
};

void funk2_processor_conditionlock__init     (funk2_processor_conditionlock_t* this);
void funk2_processor_conditionlock__destroy  (funk2_processor_conditionlock_t* this);
s64  funk2_processor_conditionlock__trylock  (funk2_processor_conditionlock_t* this);
s64  funk2_processor_conditionlock__lock     (funk2_processor_conditionlock_t* this);
s64  funk2_processor_conditionlock__unlock   (funk2_processor_conditionlock_t* this);
s64  funk2_processor_conditionlock__wait     (funk2_processor_conditionlock_t* this);
s64  funk2_processor_conditionlock__signal   (funk2_processor_conditionlock_t* this);
s64  funk2_processor_conditionlock__broadcast(funk2_processor_conditionlock_t* this);

#define funk2_processor_conditionlock__wait_while(condition, this) {	\
    pthread_mutex_lock(&((this)->mutex));				\
    while (condition) {							\
      pthread_cond_wait(&((this)->cond), &((this)->mutex));		\
    }									\
    pthread_mutex_unlock(&((this)->mutex));				\
  }

#define pthread_cond_wait_while(condition, pthread_cond, pthread_mutex) { \
    pthread_mutex_lock(pthread_mutex);					\
    while (condition) {							\
      pthread_cond_wait(pthread_cond, pthread_mutex);			\
    }									\
    pthread_mutex_unlock(pthread_mutex);				\
  }

#endif // F2__PROCESSOR_CONDITIONLOCK__H
