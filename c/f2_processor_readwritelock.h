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

#ifndef F2__PROCESSOR_READWRITELOCK__H
#define F2__PROCESSOR_READWRITELOCK__H

#include "f2_global.h"

typedef struct funk2_processor_readwritelock_s {
  pthread_rwlock_t pthread_rwlock;
} funk2_processor_readwritelock_t;

typedef enum funk2_processor_readwritelock_trylock_result_e {
  funk2_processor_readwritelock_trylock_result__success,
  funk2_processor_readwritelock_trylock_result__failure
} funk2_processor_readwritelock_trylock_result_t;

void                                           funk2_processor_readwritelock__init              (funk2_processor_readwritelock_t* this);
void                                           funk2_processor_readwritelock__destroy           (funk2_processor_readwritelock_t* this);
boolean_t                                      funk2_processor_readwritelock__is_writelocked    (funk2_processor_readwritelock_t* this);
boolean_t                                      funk2_processor_readwritelock__is_readlocked     (funk2_processor_readwritelock_t* this);
funk2_processor_readwritelock_trylock_result_t funk2_processor_readwritelock__raw_trywritelock  (funk2_processor_readwritelock_t* this, const char* writelock_source_file, const int writelock_line_num);
funk2_processor_readwritelock_trylock_result_t funk2_processor_readwritelock__raw_tryreadlock   (funk2_processor_readwritelock_t* this, const char* readlock_source_file, const int readlock_line_num);
void                                           funk2_processor_readwritelock__raw_writelock     (funk2_processor_readwritelock_t* this, const char* writelock_source_file, const int writelock_line_num);
void                                           funk2_processor_readwritelock__raw_readlock      (funk2_processor_readwritelock_t* this, const char* readlock_source_file, const int readlock_line_num);
void                                           funk2_processor_readwritelock__raw_user_writelock(funk2_processor_readwritelock_t* this, const char* writelock_source_file, const int writelock_line_num);
void                                           funk2_processor_readwritelock__raw_user_readlock (funk2_processor_readwritelock_t* this, const char* readlock_source_file, const int readlock_line_num);
void                                           funk2_processor_readwritelock__raw_unlock        (funk2_processor_readwritelock_t* this, const char* unlock_source_file, const int unlock_line_num);
u64                                            funk2_processor_readwritelock__eq_hash_value     (funk2_processor_readwritelock_t* this);
u64                                            funk2_processor_readwritelock__equals_hash_value (funk2_processor_readwritelock_t* this);

#define funk2_processor_readwritelock__trywritelock(  this) funk2_processor_readwritelock__raw_trywritelock(  this, __FILE__, __LINE__)
#define funk2_processor_readwritelock__tryreadlock(   this) funk2_processor_readwritelock__raw_tryreadlock(   this, __FILE__, __LINE__)
#define funk2_processor_readwritelock__writelock(     this) funk2_processor_readwritelock__raw_writelock(     this, __FILE__, __LINE__)
#define funk2_processor_readwritelock__readlock(      this) funk2_processor_readwritelock__raw_readlock(      this, __FILE__, __LINE__)
#define funk2_processor_readwritelock__user_writelock(this) funk2_processor_readwritelock__raw_user_writelock(this, __FILE__, __LINE__)
#define funk2_processor_readwritelock__user_readlock( this) funk2_processor_readwritelock__raw_user_readlock( this, __FILE__, __LINE__)
#define funk2_processor_readwritelock__unlock(        this) funk2_processor_readwritelock__raw_unlock(        this, __FILE__, __LINE__)


#endif // F2__PROCESSOR_READWRITELOCK__H

