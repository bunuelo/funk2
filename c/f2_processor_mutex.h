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

#ifndef F2__PROCESSOR_MUTEX__TYPES__H
#define F2__PROCESSOR_MUTEX__TYPES__H

typedef struct funk2_processor_mutex_s funk2_processor_mutex_t;

#endif // F2__PROCESSOR_MUTEX__TYPES__H


#ifndef F2__PROCESSOR_MUTEX__H
#define F2__PROCESSOR_MUTEX__H

#include "f2_global.h"
#include "f2_poller.h"
#include "f2_processor_thread_handler.h"
#include "f2_propogator_cell.h"

#define F2__PROCESSOR_MUTEX__DEBUG

#define PROCESSOR_MUTEX__INITIALIZED_MAGIC ((u64)0xDEADBEEFDEADBEEF)

struct funk2_processor_mutex_s {
#if defined(F2__PROCESSOR_MUTEX__DEBUG)
  boolean_t               is_initialized;
  u64                     initialized_magic;
  boolean_t               is_locked;
  char*                   lock_source_file;
  int                     lock_line_num;
  f2tid_t                 lock_tid;
#endif
  funk2_propogator_cell_t is_locked_cell;
};

typedef enum funk2_processor_mutex_trylock_result_e {
  funk2_processor_mutex_trylock_result__success = 0,
  funk2_processor_mutex_trylock_result__failure
} funk2_processor_mutex_trylock_result_t;

void                                   funk2_processor_mutex__init             (funk2_processor_mutex_t* this);
void                                   funk2_processor_mutex__destroy          (funk2_processor_mutex_t* this);
boolean_t                              funk2_processor_mutex__is_locked        (funk2_processor_mutex_t* this);
funk2_processor_mutex_trylock_result_t funk2_processor_mutex__raw_trylock      (funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num);
void                                   funk2_processor_mutex__raw_lock         (funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num);
void                                   funk2_processor_mutex__raw_lock_two     (funk2_processor_mutex_t* this, funk2_processor_mutex_t* that, const char* lock_source_file, const int lock_line_num);
void                                   funk2_processor_mutex__raw_user_lock    (funk2_processor_mutex_t* this, const char* lock_source_file, const int lock_line_num);
void                                   funk2_processor_mutex__raw_unlock       (funk2_processor_mutex_t* this, const char* unlock_source_file, const int unlock_line_num);
u64                                    funk2_processor_mutex__eq_hash_value    (funk2_processor_mutex_t* this);
u64                                    funk2_processor_mutex__equals_hash_value(funk2_processor_mutex_t* this);

#define funk2_processor_mutex__trylock(  this)       funk2_processor_mutex__raw_trylock(  this,       __FILE__, __LINE__)
#define funk2_processor_mutex__lock(     this)       funk2_processor_mutex__raw_lock(     this,       __FILE__, __LINE__)
#define funk2_processor_mutex__lock_two( this, that) funk2_processor_mutex__raw_lock_two( this, that, __FILE__, __LINE__)
#define funk2_processor_mutex__user_lock(this)       funk2_processor_mutex__raw_user_lock(this,       __FILE__, __LINE__)
#define funk2_processor_mutex__unlock(   this)       funk2_processor_mutex__raw_unlock(   this,       __FILE__, __LINE__)

#endif // F2__PROCESSOR_MUTEX__H

