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

#ifndef F2__PROTECTED_ALLOC_ARRAY__H
#define F2__PROTECTED_ALLOC_ARRAY__H

#include "f2_hash.h"
#include "f2_garbage_collector_pool.h"

//#define F2__DEBUG__PROTECTED_ALLOC_ARRAY

typedef enum funk2_protected_alloc_array_event_type_e {
  funk2_protected_alloc_array_event_type__enter,
  funk2_protected_alloc_array_event_type__exit
} funk2_protected_alloc_array_event_type_t;

typedef struct funk2_protected_alloc_array_event_s {
  funk2_protected_alloc_array_event_type_t type;
  char*                                    source_filename;
  int                                      source_line_num;
} funk2_protected_alloc_array_event_t;

typedef struct funk2_protected_alloc_array_event_array_s {
  u64                                  used_num;
  u64                                  length;
  funk2_protected_alloc_array_event_t* data;
} funk2_protected_alloc_array_event_array_t;

void funk2_protected_alloc_array_event_array__init     (funk2_protected_alloc_array_event_array_t* this);
void funk2_protected_alloc_array_event_array__destroy  (funk2_protected_alloc_array_event_array_t* this);
void funk2_protected_alloc_array_event_array__add_event(funk2_protected_alloc_array_event_array_t* this, funk2_protected_alloc_array_event_type_t type, char* source_filename, int source_line_num);
void funk2_protected_alloc_array_event_array__reset    (funk2_protected_alloc_array_event_array_t* this);

typedef struct funk2_protected_alloc_array_s {
  u64                                       used_num;
  u64                                       length;
  f2ptr_t*                                  data;
  s64                                       reentrance_count;
  s64                                       max_reentrance_count;
#ifdef F2__DEBUG__PROTECTED_ALLOC_ARRAY
  funk2_protected_alloc_array_event_array_t event_array;
#endif // F2__DEBUG__PROTECTED_ALLOC_ARRAY
} funk2_protected_alloc_array_t;

void      funk2_protected_alloc_array__init                         (funk2_protected_alloc_array_t* this);
void      funk2_protected_alloc_array__destroy                      (funk2_protected_alloc_array_t* this);
void      funk2_protected_alloc_array__add_protected_alloc_f2ptr    (funk2_protected_alloc_array_t* this, f2ptr exp);
void      funk2_protected_alloc_array__signal_enter_protected_region(funk2_protected_alloc_array_t* this, char* source_filename, int source_line_num);
void      funk2_protected_alloc_array__signal_exit_protected_region (funk2_protected_alloc_array_t* this, char* source_filename, int source_line_num);
boolean_t funk2_protected_alloc_array__in_protected_region          (funk2_protected_alloc_array_t* this);
void      funk2_protected_alloc_array__touch_all                    (funk2_protected_alloc_array_t* this, funk2_garbage_collector_pool_t* garbage_collector_pool);
void      funk2_protected_alloc_array__defragment__fix_pointers     (funk2_protected_alloc_array_t* this);


// funk2_protected_alloc_array_fiber_hash

#define funk2_protected_alloc_array_fiber_hash__extra_array_buffer__max_num 64

typedef struct funk2_protected_alloc_array_fiber_hash_s {
  funk2_hash_t                   used_fiber_hash;
  u64                            extra_array_buffer__count;
  funk2_protected_alloc_array_t* extra_array_buffer[funk2_protected_alloc_array_fiber_hash__extra_array_buffer__max_num];
} funk2_protected_alloc_array_fiber_hash_t;

void                           funk2_protected_alloc_array_fiber_hash__init                            (funk2_protected_alloc_array_fiber_hash_t* this);
void                           funk2_protected_alloc_array_fiber_hash__destroy                         (funk2_protected_alloc_array_fiber_hash_t* this);
funk2_protected_alloc_array_t* funk2_protected_alloc_array_fiber_hash__try_lookup_protected_alloc_array(funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber);
funk2_protected_alloc_array_t* funk2_protected_alloc_array_fiber_hash__lookup_protected_alloc_array    (funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber);
void                           funk2_protected_alloc_array_fiber_hash__remove_protected_alloc_array    (funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber);
void                           funk2_protected_alloc_array_fiber_hash__add_protected_alloc_f2ptr       (funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber, f2ptr exp);
void                           funk2_protected_alloc_array_fiber_hash__signal_enter_protected_region   (funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber, char* source_filename, int source_line_num);
void                           funk2_protected_alloc_array_fiber_hash__signal_exit_protected_region    (funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber, char* source_filename, int source_line_num);
boolean_t                      funk2_protected_alloc_array_fiber_hash__in_protected_region             (funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber);
void                           funk2_protected_alloc_array_fiber_hash__touch_all                       (funk2_protected_alloc_array_fiber_hash_t* this, funk2_garbage_collector_pool_t* garbage_collector_pool);
void                           funk2_protected_alloc_array_fiber_hash__defragment__fix_pointers        (funk2_protected_alloc_array_fiber_hash_t* this);


#endif // F2__PROTECTED_ALLOC_ARRAY__H

