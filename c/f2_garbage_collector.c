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


