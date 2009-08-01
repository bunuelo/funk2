// 
// Copyright (c) 2007-2008 Bo Morgan.
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

// garbage_collector

struct funk2_garbage_collector_s {
  funk2_garbage_collector_pool_t gc_pool[memory_pool_num];
  funk2_never_delete_list_t      never_delete_list;
  u64                            last_garbage_collect_nanoseconds_since_1970;
};

void  funk2_garbage_collector__init(funk2_garbage_collector_t* this, funk2_memory_t* memory);
void  funk2_garbage_collector__destroy(funk2_garbage_collector_t* this);
void  funk2_garbage_collector__know_of_used_exp_mutation(funk2_garbage_collector_t* this, f2ptr exp);
void  funk2_garbage_collector__know_of_no_more_references(funk2_garbage_collector_t* this, f2ptr exp);
void  funk2_garbage_collector__know_of_protected_f2ptr(funk2_garbage_collector_t* this, f2ptr exp);
void  funk2_garbage_collector__touch_all_roots(funk2_garbage_collector_t* this);
void  funk2_garbage_collector__touch_f2ptr(funk2_garbage_collector_t* this, f2ptr exp);
void  funk2_garbage_collector__collect_garbage(funk2_garbage_collector_t* this);
void  funk2_garbage_collector__signal_enter_protected_region(funk2_garbage_collector_t* this);
void  funk2_garbage_collector__signal_exit_protected_region(funk2_garbage_collector_t* this);
void  funk2_garbage_collector__touch_never_delete_list(funk2_garbage_collector_t* this);
f2ptr funk2_garbage_collector__add_f2ptr_to_never_delete_list(funk2_garbage_collector_t* this, f2ptr exp);
void  funk2_garbage_collector__handle(funk2_garbage_collector_t* this);

#define pause_gc()    funk2_garbage_collector__signal_enter_protected_region(&(__funk2.garbage_collector))
#define resume_gc()   funk2_garbage_collector__signal_exit_protected_region(&(__funk2.garbage_collector))
#define never_gc(exp) funk2_garbage_collector__add_f2ptr_to_never_delete_list(&(__funk2.garbage_collector), exp);

#endif // F2__GARBAGE_COLLECTOR__H

