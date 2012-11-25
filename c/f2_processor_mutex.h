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

#ifndef F2__PROCESSOR_MUTEX__H
#define F2__PROCESSOR_MUTEX__H

#include "f2_global.h"

//#define F2__PROCESSOR_MUTEX__DEBUG

typedef struct funk2_processor_mutex_s {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  boolean_t       is_initialized;
  boolean_t       is_locked;
  char*           lock_source_file;
  int             lock_line_num;
  pthread_t       lock_tid;
#endif
  pthread_mutex_t pthread_mutex;
} funk2_processor_mutex_t;

typedef enum funk2_processor_mutex_trylock_result_e {
  funk2_processor_mutex_trylock_result__success,
  funk2_processor_mutex_trylock_result__failure
} funk2_processor_mutex_trylock_result_t;

void                                   funk2_processor_mutex__init             (funk2_processor_mutex_t* this);
void                                   funk2_processor_mutex__destroy          (funk2_processor_mutex_t* this);
boolean_t                              funk2_processor_mutex__is_locked        (funk2_processor_mutex_t* this);
funk2_processor_mutex_trylock_result_t funk2_processor_mutex__raw_trylock      (funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num);
void                                   funk2_processor_mutex__raw_lock         (funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num);
void                                   funk2_processor_mutex__raw_user_lock    (funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num);
void                                   funk2_processor_mutex__raw_unlock       (funk2_processor_mutex_t* this, const char* unlock_source_file, const int unlock_line_num);
u64                                    funk2_processor_mutex__eq_hash_value    (funk2_processor_mutex_t* this);
u64                                    funk2_processor_mutex__equals_hash_value(funk2_processor_mutex_t* this);

#define funk2_processor_mutex__trylock(  this) funk2_processor_mutex__raw_trylock(  this, __FILE__, __LINE__)
#define funk2_processor_mutex__lock(     this) funk2_processor_mutex__raw_lock(     this, __FILE__, __LINE__)
#define funk2_processor_mutex__user_lock(this) funk2_processor_mutex__raw_user_lock(this, __FILE__, __LINE__)
#define funk2_processor_mutex__unlock(   this) funk2_processor_mutex__raw_unlock(   this, __FILE__, __LINE__)


#define pthread_cond_wait_while(condition, pthread_cond, pthread_mutex) { \
    s64 pthread_cond_wait_helper__wait_tries = 0;			\
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
	} else {							\
	  /* spin but go into deep sleep (about 1% of CPU usage) */	\
	  raw__spin_sleep_yield();					\
	}								\
      }									\
    }									\
  }


#endif // F2__PROCESSOR_MUTEX__H

