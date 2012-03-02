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

#include "funk2.h"

void funk2_defragmenter__init(funk2_defragmenter_t* this) {
  this->need_defragmentation = boolean__false;
}

void funk2_defragmenter__destroy(funk2_defragmenter_t* this) {
}

void funk2_defragmenter__defragment(funk2_defragmenter_t* this) {
  
}

void funk2_defragmenter__handle(funk2_defragmenter_t* this) {
  if (this->need_defragmentation) {
    status("funk2_memory__handle asking all user processor threads to wait_politely so that we can begin collecting garbage.");
    __funk2.user_thread_controller.please_wait = boolean__true;
    funk2_user_thread_controller__wait_for_all_user_threads_to_wait(&(__funk2.user_thread_controller));
    status("");
    status("*******************************");
    status("**** DOING DEFRAGMENTATION ****");
    status("*******************************");
    status("");
    {
      int index;
      for (index = 0; index < memory_pool_num; index ++) {
	status ("__funk2.memory.pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(__funk2.memory.pool[index].total_global_memory));
      }
    }
    funk2_defragmenter__defragment(this);
    status("");
    status("***********************************");
    status("**** DONE WITH DEFRAGMENTATION ****");
    status("***********************************");
    status("");
    {
      int index;
      for (index = 0; index < memory_pool_num; index ++) {
	this->gc_pool[index].should_run_gc = boolean__false;
	status ("__funk2.memory.pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(__funk2.memory.pool[index].total_global_memory));
      }
    }
    this->need_defragmentation = boolean__false;
    __funk2.user_thread_controller.please_wait = boolean__false;
  }
}

