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

#ifndef F2__USER_THREAD_CONTROLLER__H
#define F2__USER_THREAD_CONTROLLER__H

// funk2_user_thread_controller__touch_all_protected_alloc_arrays

typedef struct funk2_user_thread_controller__touch_all_protected_alloc_arrays_s {
  boolean_t               start;
  funk2_processor_mutex_t done_mutex;
  s64                     done_count;
  boolean_t               everyone_done;
} funk2_user_thread_controller__touch_all_protected_alloc_arrays_t;

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__init(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this);
void funk2_user_thread_controller__touch_all_protected_alloc_arrays__destroy(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this);
void funk2_user_thread_controller__touch_all_protected_alloc_arrays__signal_execute(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this);
void funk2_user_thread_controller__touch_all_protected_alloc_arrays__user_process(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this);

// funk2_user_thread_controller__blacken_grey_nodes

typedef struct funk2_user_thread_controller__blacken_grey_nodes_s {
  boolean_t               start;
  funk2_processor_mutex_t done_mutex;
  s64                     done_count;
  atomic_t                not_exited_count;
  boolean_t               everyone_done;
} funk2_user_thread_controller__blacken_grey_nodes_t;

void funk2_user_thread_controller__blacken_grey_nodes__init(funk2_user_thread_controller__blacken_grey_nodes_t* this);
void funk2_user_thread_controller__blacken_grey_nodes__destroy(funk2_user_thread_controller__blacken_grey_nodes_t* this);
void funk2_user_thread_controller__blacken_grey_nodes__signal_execute(funk2_user_thread_controller__blacken_grey_nodes_t* this);
void funk2_user_thread_controller__blacken_grey_nodes__user_process(funk2_user_thread_controller__blacken_grey_nodes_t* this);

// funk2_user_thread_controller__grey_from_other_nodes

typedef struct funk2_user_thread_controller__grey_from_other_nodes_s {
  boolean_t               start;
  funk2_processor_mutex_t done_mutex;
  s64                     done_count;
  boolean_t               everyone_done;
} funk2_user_thread_controller__grey_from_other_nodes_t;

void funk2_user_thread_controller__grey_from_other_nodes__init(funk2_user_thread_controller__grey_from_other_nodes_t* this);
void funk2_user_thread_controller__grey_from_other_nodes__destroy(funk2_user_thread_controller__grey_from_other_nodes_t* this);
void funk2_user_thread_controller__grey_from_other_nodes__signal_execute(funk2_user_thread_controller__grey_from_other_nodes_t* this);
void funk2_user_thread_controller__grey_from_other_nodes__user_process(funk2_user_thread_controller__grey_from_other_nodes_t* this);

// funk2_user_thread_controller__free_whiteness

typedef struct funk2_user_thread_controller__free_whiteness_s {
  boolean_t               start;
  funk2_processor_mutex_t done_mutex;
  s64                     done_count;
  boolean_t               everyone_done;
} funk2_user_thread_controller__free_whiteness_t;

void funk2_user_thread_controller__free_whiteness__init(funk2_user_thread_controller__free_whiteness_t* this);
void funk2_user_thread_controller__free_whiteness__destroy(funk2_user_thread_controller__free_whiteness_t* this);
void funk2_user_thread_controller__free_whiteness__signal_execute(funk2_user_thread_controller__free_whiteness_t* this);
void funk2_user_thread_controller__free_whiteness__user_process(funk2_user_thread_controller__free_whiteness_t* this);

// funk2_user_thread_controller__exit

typedef struct funk2_user_thread_controller__exit_s {
  boolean_t               start;
  funk2_processor_mutex_t done_mutex;
  s64                     done_count;
  boolean_t               everyone_done;
} funk2_user_thread_controller__exit_t;

void funk2_user_thread_controller__exit__init(funk2_user_thread_controller__exit_t* this);
void funk2_user_thread_controller__exit__destroy(funk2_user_thread_controller__exit_t* this);
void funk2_user_thread_controller__exit__signal_execute(funk2_user_thread_controller__exit_t* this);
void funk2_user_thread_controller__exit__user_process(funk2_user_thread_controller__exit_t* this);



// funk2_user_thread_controller

typedef struct funk2_user_thread_controller_s {
  boolean_t                                                                    please_wait;
  s64                                                                          waiting_count;
  funk2_processor_mutex_t                                                      waiting_count_mutex;
  funk2_user_thread_controller__touch_all_protected_alloc_arrays_t             touch_all_protected_alloc_arrays;
  funk2_user_thread_controller__blacken_grey_nodes_t                           blacken_grey_nodes;
  funk2_user_thread_controller__grey_from_other_nodes_t                        grey_from_other_nodes;
  funk2_user_thread_controller__free_whiteness_t                               free_whiteness;
  funk2_user_thread_controller__exit_t                                         exit;
} funk2_user_thread_controller_t;

void      funk2_user_thread_controller__init(                             funk2_user_thread_controller_t* this);
void      funk2_user_thread_controller__destroy(                          funk2_user_thread_controller_t* this);
void      funk2_user_thread_controller__wait_for_all_user_threads_to_wait(funk2_user_thread_controller_t* this);
void      funk2_user_thread_controller__user_wait_politely(               funk2_user_thread_controller_t* this);
void      funk2_user_thread_controller__user_check_wait_politely(         funk2_user_thread_controller_t* this);
void      funk2_user_thread_controller__touch_all_protected_alloc_arrays( funk2_user_thread_controller_t* this);
void      funk2_user_thread_controller__blacken_grey_nodes(               funk2_user_thread_controller_t* this);
void      funk2_user_thread_controller__grey_from_other_nodes(            funk2_user_thread_controller_t* this);
void      funk2_user_thread_controller__free_whiteness(                   funk2_user_thread_controller_t* this);
void      funk2_user_thread_controller__exit(                             funk2_user_thread_controller_t* this);

#endif // F2__USER_THREAD_CONTROLLER__H

