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
    funk2_poller_t funk2_processor_conditionlock_helper__poller;	\
    boolean_t      funk2_processor_conditionlock_helper__poller_initialized = boolean__false; \
    s64            funk2_processor_conditionlock_helper__wait_tries         = 0; \
    while (condition) {							\
      if (pthread_mutex_trylock(&((this)->mutex)) == 0) {		\
	while (condition) {						\
	  pthread_cond_wait(&((this)->cond), &((this)->mutex));		\
	}								\
	pthread_mutex_unlock(&((this)->mutex));				\
      }	else {								\
	if (funk2_processor_conditionlock_helper__wait_tries < 1000) {	\
	  /* spin super fast waiting for pure concurrent thread */	\
	  funk2_processor_conditionlock_helper__wait_tries ++;		\
	} else if (funk2_processor_conditionlock_helper__wait_tries < 2000) { \
	  /* spin fast but yield to parallel threads */			\
	  raw__fast_spin_sleep_yield();					\
	  funk2_processor_conditionlock_helper__wait_tries ++;		\
	} else if (funk2_processor_conditionlock_helper__wait_tries == 2000) { \
	  funk2_poller__init(&funk2_processor_conditionlock_helper__poller, poller__deep_sleep_percentage, 10); \
	  funk2_poller__reset(&funk2_processor_conditionlock_helper__poller); \
	  funk2_processor_conditionlock_helper__poller_initialized = boolean__true; \
	  funk2_processor_conditionlock_helper__wait_tries ++;		\
	} else {							\
	  /* spin but go into deep sleep (about 1% of CPU usage) */	\
	  funk2_poller__sleep(&funk2_processor_conditionlock_helper__poller); \
	}								\
      }									\
    }									\
    if (funk2_processor_conditionlock_helper__poller_initialized) {	\
      funk2_poller__destroy(&funk2_processor_conditionlock_helper__poller); \
    }									\
  }

#define pthread_cond_wait_while(condition, pthread_cond, pthread_mutex) { \
    funk2_poller_t pthread_cond_wait_helper__poller;			\
    boolean_t      pthread_cond_wait_helper__poller_initialized = boolean__false; \
    s64            pthread_cond_wait_helper__wait_tries         = 0;	\
    while (condition) {							\
      if (pthread_mutex_trylock(pthread_mutex) == 0) {			\
	while (condition) {						\
	  pthread_cond_wait(pthread_cond, pthread_mutex);		\
	}								\
	pthread_mutex_unlock(pthread_mutex);				\
      }	else {								\
	if (pthread_cond_wait_helper__wait_tries < 1000) {		\
	  /* spin super fast waiting for pure concurrent thread */	\
	  pthread_cond_wait_helper__wait_tries ++;			\
	} else if (pthread_cond_wait_helper__wait_tries < 2000) {	\
	  /* spin fast but yield to parallel threads */			\
	  raw__fast_spin_sleep_yield();					\
	  pthread_cond_wait_helper__wait_tries ++;			\
	} else if (pthread_cond_wait_helper__wait_tries == 2000) {	\
	  funk2_poller__init(&pthread_cond_wait_helper__poller, poller__deep_sleep_percentage, 10); \
	  funk2_poller__reset(&pthread_cond_wait_helper__poller);	\
	  pthread_cond_wait_helper__poller_initialized = boolean__true;	\
	  pthread_cond_wait_helper__wait_tries ++;			\
	} else {							\
	  /* spin but go into deep sleep (about 1% of CPU usage) */	\
	  funk2_poller__sleep(&pthread_cond_wait_helper__poller);	\
	}								\
      }									\
    }									\
    if (pthread_cond_wait_helper__poller_initialized) {			\
      funk2_poller__destroy(&pthread_cond_wait_helper__poller);		\
    }									\
  }

#endif // F2__PROCESSOR_CONDITIONLOCK__H
