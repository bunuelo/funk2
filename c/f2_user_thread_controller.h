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

#ifndef F2__USER_THREAD_CONTROLLER__H
#define F2__USER_THREAD_CONTROLLER__H

#include "f2_processor_spinlock.h"

// funk2_user_thread_controller__touch_all_protected_alloc_arrays

typedef struct funk2_user_thread_controller__touch_all_protected_alloc_arrays_s {
  boolean_t       start;
  pthread_mutex_t done_count_mutex;
  pthread_cond_t  done_count_cond;
  s64             done_count;
  pthread_mutex_t everyone_done_mutex;
  pthread_cond_t  everyone_done_cond;
  boolean_t       everyone_done;
} funk2_user_thread_controller__touch_all_protected_alloc_arrays_t;

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__init(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this);
void funk2_user_thread_controller__touch_all_protected_alloc_arrays__destroy(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this);
void funk2_user_thread_controller__touch_all_protected_alloc_arrays__signal_execute(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this);
void funk2_user_thread_controller__touch_all_protected_alloc_arrays__user_process(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this);

// funk2_user_thread_controller__blacken_grey_nodes

typedef struct funk2_user_thread_controller__blacken_grey_nodes_s {
  boolean_t       start;
  pthread_mutex_t done_count_mutex;
  pthread_cond_t  done_count_cond;
  s64             done_count;
  atomic_t        not_exited_count;
  pthread_mutex_t everyone_done_mutex;
  pthread_cond_t  everyone_done_cond;
  boolean_t       everyone_done;
} funk2_user_thread_controller__blacken_grey_nodes_t;

void funk2_user_thread_controller__blacken_grey_nodes__init(funk2_user_thread_controller__blacken_grey_nodes_t* this);
void funk2_user_thread_controller__blacken_grey_nodes__destroy(funk2_user_thread_controller__blacken_grey_nodes_t* this);
void funk2_user_thread_controller__blacken_grey_nodes__signal_execute(funk2_user_thread_controller__blacken_grey_nodes_t* this);
void funk2_user_thread_controller__blacken_grey_nodes__user_process(funk2_user_thread_controller__blacken_grey_nodes_t* this);

// funk2_user_thread_controller__grey_from_other_nodes

typedef struct funk2_user_thread_controller__grey_from_other_nodes_s {
  boolean_t       start;
  pthread_mutex_t done_count_mutex;
  pthread_cond_t  done_count_cond;
  s64             done_count;
  pthread_mutex_t everyone_done_mutex;
  pthread_cond_t  everyone_done_cond;
  boolean_t       everyone_done;
} funk2_user_thread_controller__grey_from_other_nodes_t;

void funk2_user_thread_controller__grey_from_other_nodes__init(funk2_user_thread_controller__grey_from_other_nodes_t* this);
void funk2_user_thread_controller__grey_from_other_nodes__destroy(funk2_user_thread_controller__grey_from_other_nodes_t* this);
void funk2_user_thread_controller__grey_from_other_nodes__signal_execute(funk2_user_thread_controller__grey_from_other_nodes_t* this);
void funk2_user_thread_controller__grey_from_other_nodes__user_process(funk2_user_thread_controller__grey_from_other_nodes_t* this);

// funk2_user_thread_controller__free_white_exps

typedef struct funk2_user_thread_controller__free_white_exps_s {
  boolean_t       start;
  pthread_mutex_t done_count_mutex;
  pthread_cond_t  done_count_cond;
  s64             done_count;
  pthread_mutex_t everyone_done_mutex;
  pthread_cond_t  everyone_done_cond;
  boolean_t       everyone_done;
} funk2_user_thread_controller__free_white_exps_t;

void funk2_user_thread_controller__free_white_exps__init(funk2_user_thread_controller__free_white_exps_t* this);
void funk2_user_thread_controller__free_white_exps__destroy(funk2_user_thread_controller__free_white_exps_t* this);
void funk2_user_thread_controller__free_white_exps__signal_execute(funk2_user_thread_controller__free_white_exps_t* this);
void funk2_user_thread_controller__free_white_exps__user_process(funk2_user_thread_controller__free_white_exps_t* this);

// funk2_user_thread_controller__remove_freed_fibers

typedef struct funk2_user_thread_controller__remove_freed_fibers_s {
  boolean_t       start;
  pthread_mutex_t done_count_mutex;
  pthread_cond_t  done_count_cond;
  s64             done_count;
  pthread_mutex_t everyone_done_mutex;
  pthread_cond_t  everyone_done_cond;
  boolean_t       everyone_done;
} funk2_user_thread_controller__remove_freed_fibers_t;

void funk2_user_thread_controller__remove_freed_fibers__init(funk2_user_thread_controller__remove_freed_fibers_t* this);
void funk2_user_thread_controller__remove_freed_fibers__destroy(funk2_user_thread_controller__remove_freed_fibers_t* this);
void funk2_user_thread_controller__remove_freed_fibers__signal_execute(funk2_user_thread_controller__remove_freed_fibers_t* this);
void funk2_user_thread_controller__remove_freed_fibers__user_process(funk2_user_thread_controller__remove_freed_fibers_t* this);

// funk2_user_thread_controller__exit

typedef struct funk2_user_thread_controller__exit_s {
  boolean_t       start;
  pthread_mutex_t done_count_mutex;
  pthread_cond_t  done_count_cond;
  s64             done_count;
  pthread_mutex_t everyone_done_mutex;
  pthread_cond_t  everyone_done_cond;
  boolean_t       everyone_done;
} funk2_user_thread_controller__exit_t;

void funk2_user_thread_controller__exit__init(funk2_user_thread_controller__exit_t* this);
void funk2_user_thread_controller__exit__destroy(funk2_user_thread_controller__exit_t* this);
void funk2_user_thread_controller__exit__signal_execute(funk2_user_thread_controller__exit_t* this);
void funk2_user_thread_controller__exit__user_process(funk2_user_thread_controller__exit_t* this);

// funk2_user_thread_controller__defragment__move_memory

typedef struct funk2_user_thread_controller__defragment__move_memory_s {
  boolean_t       start;
  pthread_mutex_t done_count_mutex;
  pthread_cond_t  done_count_cond;
  s64             done_count;
  pthread_mutex_t everyone_done_mutex;
  pthread_cond_t  everyone_done_cond;
  boolean_t       everyone_done;
  boolean_t       user_process_done[memory_pool_num];
  pthread_mutex_t user_process_already_waiting_mutex[memory_pool_num];
} funk2_user_thread_controller__defragment__move_memory_t;

void funk2_user_thread_controller__defragment__move_memory__init(funk2_user_thread_controller__defragment__move_memory_t* this);
void funk2_user_thread_controller__defragment__move_memory__destroy(funk2_user_thread_controller__defragment__move_memory_t* this);
void funk2_user_thread_controller__defragment__move_memory__signal_execute(funk2_user_thread_controller__defragment__move_memory_t* this);
void funk2_user_thread_controller__defragment__move_memory__user_process(funk2_user_thread_controller__defragment__move_memory_t* this);

// funk2_user_thread_controller__defragment__fix_pointers

typedef struct funk2_user_thread_controller__defragment__fix_pointers_s {
  boolean_t       start;
  pthread_mutex_t done_count_mutex;
  pthread_cond_t  done_count_cond;
  s64             done_count;
  pthread_mutex_t everyone_done_mutex;
  pthread_cond_t  everyone_done_cond;
  boolean_t       everyone_done;
  boolean_t       user_process_done[memory_pool_num];
  pthread_mutex_t user_process_already_waiting_mutex[memory_pool_num];
} funk2_user_thread_controller__defragment__fix_pointers_t;

void funk2_user_thread_controller__defragment__fix_pointers__init(funk2_user_thread_controller__defragment__fix_pointers_t* this);
void funk2_user_thread_controller__defragment__fix_pointers__destroy(funk2_user_thread_controller__defragment__fix_pointers_t* this);
void funk2_user_thread_controller__defragment__fix_pointers__signal_execute(funk2_user_thread_controller__defragment__fix_pointers_t* this);
void funk2_user_thread_controller__defragment__fix_pointers__user_process(funk2_user_thread_controller__defragment__fix_pointers_t* this);



// funk2_user_thread_controller

typedef struct funk2_user_thread_controller_s {
  boolean_t                                                        need_wait;
  pthread_mutex_t                                                  something_to_do_while_waiting_politely_mutex;
  pthread_cond_t                                                   something_to_do_while_waiting_politely_cond;
  pthread_mutex_t                                                  waiting_count_mutex;
  pthread_cond_t                                                   waiting_count_cond;
  s64                                                              waiting_count;
  u64                                                              total_nanoseconds_spent_waiting[memory_pool_num];
  funk2_user_thread_controller__touch_all_protected_alloc_arrays_t touch_all_protected_alloc_arrays;
  funk2_user_thread_controller__blacken_grey_nodes_t               blacken_grey_nodes;
  funk2_user_thread_controller__grey_from_other_nodes_t            grey_from_other_nodes;
  funk2_user_thread_controller__free_white_exps_t                  free_white_exps;
  funk2_user_thread_controller__remove_freed_fibers_t              remove_freed_fibers;
  funk2_user_thread_controller__exit_t                             exit;
  funk2_user_thread_controller__defragment__move_memory_t          defragment__move_memory;
  funk2_user_thread_controller__defragment__fix_pointers_t         defragment__fix_pointers;
} funk2_user_thread_controller_t;

void  funk2_user_thread_controller__init                                               (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__destroy                                            (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__wait_for_all_user_threads_to_wait                  (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__signal_user_waiting_politely                       (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__signal_user_done_waiting_politely                  (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__user_wait_politely                                 (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__user_check_wait_politely                           (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__touch_all_protected_alloc_arrays                   (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__blacken_grey_nodes                                 (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__grey_from_other_nodes                              (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__free_white_exps                                    (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__remove_freed_fibers                                (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__exit                                               (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__defragment__move_memory                            (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__defragment__fix_pointers                           (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__need_start_count__increment                        (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__need_start_count__decrement                        (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__need_start_count__wait_until_nonzero               (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__end_signal_something_to_do_while_waiting_politely  (funk2_user_thread_controller_t* this);
void  funk2_user_thread_controller__need_wait__set                                     (funk2_user_thread_controller_t* this, boolean_t need_wait);

#define check_wait_politely() { \
    if (__funk2.user_thread_controller.need_wait) {		\
      funk2_user_thread_controller__user_wait_politely(&(__funk2.user_thread_controller)); \
    }								\
  }

#endif // F2__USER_THREAD_CONTROLLER__H

