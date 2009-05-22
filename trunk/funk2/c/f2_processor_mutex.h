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

#ifndef F2__PROCESSOR_MUTEX__H
#define F2__PROCESSOR_MUTEX__H

typedef struct funk2_processor_mutex_s {
  char            lock_source_file[1024];
  int             lock_line_num;
  pthread_mutex_t pthread_mutex;
} funk2_processor_mutex_t;

typedef enum funk2_processor_mutex_trylock_result_e {
  funk2_processorr_trylock_result__success,
  funk2_processorr_trylock_result__failure
} funk2_processorr_trylock_result_t;

void                                   funk2_processor_mutex__init(funk2_processor_mutex_t* this);
void                                   funk2_processor_mutex__destroy(funk2_processor_mutex_t* this);
void                                   funk2_processor_mutex__lock(funk2_processor_mutex_t* this);
funk2_processor_mutex_trylock_result_t funk2_processor_mutex__trylock(funk2_processor_mutex_t* this);
void                                   funk2_processor_mutex__unlock(funk2_processor_mutex_t* this);

#endif // F2__PROCESSOR_MUTEX__H

