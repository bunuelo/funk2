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

#ifndef F2__GARBAGE_COLLECTOR__TYPES__H
#define F2__GARBAGE_COLLECTOR__TYPES__H

typedef struct funk2_garbage_collector_s funk2_garbage_collector_t;

#endif // F2__GARBAGE_COLLECTOR__TYPES__H

#ifndef F2__GARBAGE_COLLECTOR__H
#define F2__GARBAGE_COLLECTOR__H

#include "f2_garbage_collector_pool.h"
#include "f2_never_delete_list.h"

#define DEBUG_GARBAGE_COLLECTOR_STATUS 1

#if defined(DEBUG_GARBAGE_COLLECTOR_STATUS)
#  define garbage_collector_status(msg, rest...) status(msg, ## rest)
#else
#  define garbage_collector_status(msg, rest...)
#endif

// garbage_collector

struct funk2_garbage_collector_s {
  funk2_processor_mutex_t        do_collection_mutex;
  funk2_garbage_collector_pool_t gc_pool[memory_pool_num];
  funk2_never_delete_list_t      never_delete_list;
  u64                            last_garbage_collect_nanoseconds_since_1970;
  boolean_t                      user_signal_garbage_collect_now;
  funk2_processor_mutex_t        total_garbage_collection_count__mutex;
  u64                            total_garbage_collection_count;
  s64                            temporary_load_buffer__length;
  u8*                            temporary_load_buffer;
};

void      funk2_garbage_collector__init                          (funk2_garbage_collector_t* this);
void      funk2_garbage_collector__destroy                       (funk2_garbage_collector_t* this);
void      funk2_garbage_collector__init_sets_from_memory         (funk2_garbage_collector_t* this, funk2_memory_t* memory);
void      funk2_garbage_collector__know_of_used_exp_mutation     (funk2_garbage_collector_t* this, f2ptr exp);
void      funk2_garbage_collector__know_of_no_more_references    (funk2_garbage_collector_t* this, f2ptr exp);
void      funk2_garbage_collector__know_of_protected_f2ptr       (funk2_garbage_collector_t* this, f2ptr exp);
void      funk2_garbage_collector__touch_f2ptr                   (funk2_garbage_collector_t* this, f2ptr exp);
void      funk2_garbage_collector__touch_all_roots               (funk2_garbage_collector_t* this);
boolean_t funk2_garbage_collector__still_have_grey_nodes         (funk2_garbage_collector_t* this);
void      funk2_garbage_collector__spread_all_blackness          (funk2_garbage_collector_t* this);
void      funk2_garbage_collector__whiten_all_used_memory        (funk2_garbage_collector_t* this);
void      funk2_garbage_collector__collect_garbage               (funk2_garbage_collector_t* this);
u64       funk2_garbage_collector__total_garbage_collection_count(funk2_garbage_collector_t* this);
void      funk2_garbage_collector__signal_enter_protected_region (funk2_garbage_collector_t* this, char* source_filename, int source_line_num);
void      funk2_garbage_collector__signal_exit_protected_region  (funk2_garbage_collector_t* this, char* source_filename, int source_line_num);
void      funk2_garbage_collector__touch_never_delete_list       (funk2_garbage_collector_t* this);
f2ptr     funk2_garbage_collector__add_f2ptr_to_never_delete_list(funk2_garbage_collector_t* this, f2ptr exp, char* source_filename, int source_line_num);
void      funk2_garbage_collector__handle                        (funk2_garbage_collector_t* this);
s64       funk2_garbage_collector__calculate_save_size           (funk2_garbage_collector_t* this);
void      funk2_garbage_collector__save_to_stream                (funk2_garbage_collector_t* this, int fd);
void      funk2_garbage_collector__load_from_stream              (funk2_garbage_collector_t* this, int fd);
void      funk2_garbage_collector__defragment__fix_pointers      (funk2_garbage_collector_t* this);

#define pause_gc()  funk2_garbage_collector__signal_enter_protected_region(&(__funk2.garbage_collector), __FILE__, __LINE__)
#define resume_gc() funk2_garbage_collector__signal_exit_protected_region( &(__funk2.garbage_collector), __FILE__, __LINE__)

#define never_gc(exp) funk2_garbage_collector__add_f2ptr_to_never_delete_list(&(__funk2.garbage_collector), exp, __FILE__, __LINE__);

// **

void f2__garbage_collector__reinitialize_globalvars();
void f2__garbage_collector__initialize();

#endif // F2__GARBAGE_COLLECTOR__H

