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

#include "funk2.h"

// garbage_collector

void funk2_garbage_collector__init(funk2_garbage_collector_t* this, funk2_memory_t* memory) {
  status("initializing garbage collector.");
  
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_garbage_collector_pool__init(&(this->gc_pool[pool_index]), &(memory->pool[pool_index]), pool_index);
  }
}

void funk2_garbage_collector__destroy(funk2_garbage_collector_t* this) {
  status("destroying garbage collector.");
  
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_garbage_collector_pool__destroy(&(this->gc_pool[pool_index]));
  }
}

void funk2_garbage_collector__know_of_used_exp_mutation(funk2_garbage_collector_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (block->gc.tricolor == funk2_garbage_collector_tricolor__black) {
    int pool_index = this_processor_thread__pool_index();
    int exp__pool_index = __f2ptr__pool_index(exp);
    if (pool_index == exp__pool_index) {
      funk2_garbage_collector_pool__know_of_used_exp_self_mutation(&(this->gc_pool[exp__pool_index]), exp);
    } else {
      funk2_garbage_collector_pool__know_of_used_exp_other_mutation(&(this->gc_pool[exp__pool_index]), exp);
    }
  }
}

void funk2_garbage_collector__know_of_no_more_references(funk2_garbage_collector_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (block->gc.tricolor != funk2_garbage_collector_tricolor__white) {
    int pool_index = this_processor_thread__pool_index();
    int exp__pool_index = __f2ptr__pool_index(exp);
    if (pool_index == exp__pool_index) {
      funk2_garbage_collector_pool__know_of_used_exp_self_no_more_references(&(this->gc_pool[exp__pool_index]), exp);
    } else {
      funk2_garbage_collector_pool__know_of_used_exp_other_no_more_references(&(this->gc_pool[exp__pool_index]), exp);
    }
  }
}

void funk2_garbage_collector__touch_all_roots(funk2_garbage_collector_t* this) {
  // this is where we touch everything we want to keep!
  {
    // parallelized
    //funk2_user_thread_controller__touch_all_referenced_from_pool_generation(&(this->user_thread_controller), generation_num);
    // parallelized
    //funk2_user_thread_controller__touch_all_protected_alloc_arrays(&(__this->user_thread_controller));
    // serial
    //funk2_memory__touch_all_symbols(this);
    // serial
    //funk2_memory__touch_never_delete_list(this);
  }
}

void funk2_garbage_collector__collect_garbage(funk2_garbage_collector_t* this) {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_garbage_collector_pool__flush_other_knowledge(&(this->gc_pool[pool_index]));
  }
  funk2_garbage_collector__touch_all_roots(this);
}

// memory handling thread should never call this function
void funk2_garbage_collector__signal_enter_protected_region(funk2_memory_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__signal_enter_protected_region(&(this->gc_pool[pool_index]));
}

// memory handling thread should never call this function
void funk2_garbage_collector__signal_exit_protected_region(funk2_memory_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__signal_exit_protected_region(&(this->gc_pool[pool_index]));
}


