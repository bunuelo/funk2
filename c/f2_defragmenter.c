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
  this->total_defragmentation_count = 0;
  this->need_defragmentation        = boolean__false;
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
	status ("__funk2.memory.pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(__funk2.memory.pool[index].total_global_memory));
      }
    }
    this->need_defragmentation = boolean__false;
    this->total_defragmentation_count ++;
    __funk2.user_thread_controller.please_wait = boolean__false;
  }
}

void funk2_defragmenter__signal_start(funk2_defragmenter_t* this) {
  this->need_defragmentation = boolean__true;
}

f2ptr f2__defragmenter__signal_start(f2ptr cause) {
  funk2_defragmenter__signal_start(&(__funk2.defragmenter));
  return nil;
}
def_pcfunk0(defragmenter__signal_start,
	    "Signals to the management thread to start a defragmentation of memory.",
	    return f2__defragmenter__signal_start(this_cause));


u64 funk2_defragmenter__total_defragmentation_count(funk2_defragmenter_t* this) {
  return this->total_defragmentation_count;
}

u64 raw__defragmenter__total_defragmentation_count(f2ptr cause) {
  return funk2_defragmenter__total_defragmentation_count(&(__funk2.defragmenter));
}

f2ptr f2__defragmenter__total_defragmentation_count(f2ptr cause) {
  return f2integer__new(cause, raw__defragmenter__total_defragmentation_count(cause));
}
def_pcfunk0(defragmenter__total_defragmentation_count,
	    "Signals to the management thread to start a defragmentation of memory.",
	    return f2__defragmenter__total_defragmentation_count(this_cause));




// **

void f2__defragmenter__reinitialize_globalvars() {
}

void f2__defragmenter__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "defragmenter", "", &f2__defragmenter__reinitialize_globalvars);
  f2__defragmenter__reinitialize_globalvars();
  
  f2__primcfunk__init__0(defragmenter__signal_start);
  f2__primcfunk__init__0(defragmenter__total_defragmentation_count);
  
}

void f2__defragmenter__destroy() {
}

