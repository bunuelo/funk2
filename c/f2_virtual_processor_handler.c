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

#include "funk2.h"

// funk2_virtual_processor_handler

void funk2_virtual_processor_handler__init(funk2_virtual_processor_handler_t* this, u64 virtual_processor_count) {
  status("initializing virtual_processor_handler with " u64__fstr " virtual processor threads.", virtual_processor_count);
  funk2_thread_safe_hash__init(&(this->virtual_processor_index_processor_thread_hash), 16);
  funk2_atomic_u64__init(&(this->all_virtual_processor_threads),  (u64)to_ptr(NULL));
  funk2_atomic_u64__init(&(this->free_virtual_processor_threads), (u64)to_ptr(NULL));
  funk2_atomic_u64__init(&(this->free_virtual_processor_thread_count), 0);
  funk2_thread_safe_hash__init(&(this->virtual_processor_thread_processor_thread_hash), 16);
  funk2_thread_safe_hash__init(&(this->virtual_processor_index_tid_hash), 16);
  this->virtual_processor_count     = virtual_processor_count;
  this->virtual_processor           = NULL;
  this->hardware_affinities_enabled = boolean__true;
}

void funk2_virtual_processor_handler__destroy(funk2_virtual_processor_handler_t* this) {
  status("destroying virtual_processor_handler.");
  funk2_virtual_processor_handler__destroy_all_virtual_processor_threads(this);
  {
    s64 index;
    for (index = 0; index < this->virtual_processor_count; index ++) {
      funk2_virtual_processor__destroy(this->virtual_processor[index]);
    }
  }
  f2__free(to_ptr(this->virtual_processor));
  funk2_thread_safe_hash__destroy(&(this->virtual_processor_index_processor_thread_hash));
  {
    funk2_virtual_processor_thread_cons_t* iter = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(this->all_virtual_processor_threads)));
    while (iter) {
      funk2_virtual_processor_thread_cons_t* next = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(iter->next)));
      f2__free(to_ptr(iter));
      iter = next;
    }
  }
  {
    funk2_virtual_processor_thread_cons_t* iter = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(this->free_virtual_processor_threads)));
    while (iter) {
      funk2_virtual_processor_thread_cons_t* next = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(iter->next)));
      f2__free(to_ptr(iter));
      iter = next;
    }
  }
  funk2_thread_safe_hash__destroy(&(this->virtual_processor_thread_processor_thread_hash));
  funk2_thread_safe_hash__destroy(&(this->virtual_processor_index_tid_hash));
}

void funk2_virtual_processor_handler__destroy_all_virtual_processor_threads(funk2_virtual_processor_handler_t* this) {
  {
    funk2_virtual_processor_thread_cons_t* iter = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(this->all_virtual_processor_threads)));
    while (iter) {
      funk2_virtual_processor_thread_t* virtual_processor_thread = iter->virtual_processor_thread;
      funk2_virtual_processor_thread__signal_exit(virtual_processor_thread);
      iter = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(iter->next)));
    }
  }
  {
    funk2_virtual_processor_thread_cons_t* iter = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(this->all_virtual_processor_threads)));
    while (iter) {
      funk2_virtual_processor_thread_t* virtual_processor_thread = iter->virtual_processor_thread;
      funk2_virtual_processor_thread__finalize_exit(virtual_processor_thread);
      iter = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(iter->next)));
    }
  }
  {
    funk2_virtual_processor_thread_cons_t* iter = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(this->all_virtual_processor_threads)));
    while (iter) {
      funk2_virtual_processor_thread_t* virtual_processor_thread = iter->virtual_processor_thread;
      funk2_virtual_processor_thread__destroy(virtual_processor_thread);
      f2__free(to_ptr(virtual_processor_thread));
      iter = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(iter->next)));
    }
  }
}

void funk2_virtual_processor_handler__start_virtual_processors(funk2_virtual_processor_handler_t* this) {
  if (this->virtual_processor != NULL) {
    error(nil, "funk2_virtual_processor_handler__start_virtual_processors error: virtual_processor array seems to already be initialized.");
  }
  this->virtual_processor = (funk2_virtual_processor_t**)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_t*) * (this->virtual_processor_count)));
  {
    s64 index;
    for (index = 0; index < (this->virtual_processor_count); index ++) {
      this->virtual_processor[index] = (funk2_virtual_processor_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_t)));
    }
  }
  {
    s64 index;
    for (index = 0; index < (this->virtual_processor_count); index ++) {
      funk2_virtual_processor__init(this->virtual_processor[index], index);
    }
  }
}

funk2_virtual_processor_thread_t* funk2_virtual_processor_handler__get_free_virtual_processor_thread(funk2_virtual_processor_handler_t* this) {
  funk2_virtual_processor_thread_t*      virtual_processor_thread = NULL;
  funk2_virtual_processor_thread_cons_t* cons                     = NULL;
  {
    boolean_t remove_free_success = boolean__false;
    while (! remove_free_success) {
      cons = (funk2_virtual_processor_thread_cons_t*)from_ptr(funk2_atomic_u64__value(&(this->free_virtual_processor_threads)));
      if (cons == NULL) {
	// no free threads exist, so just ignore free list and return newly allocated thread.
	virtual_processor_thread = (funk2_virtual_processor_thread_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_thread_t)));
	funk2_virtual_processor_thread__init(virtual_processor_thread);
	funk2_thread_safe_hash__add(&(this->virtual_processor_thread_processor_thread_hash), (u64)to_ptr(virtual_processor_thread->processor_thread), (u64)to_ptr(virtual_processor_thread));
	{
	  funk2_virtual_processor_thread_cons_t* cons = (funk2_virtual_processor_thread_cons_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_thread_cons_t)));
	  cons->virtual_processor_thread              = virtual_processor_thread;
	  {
	    boolean_t add_used_success = boolean__false;
	    while (! add_used_success) {
	      u64 old_value = funk2_atomic_u64__value(&(this->all_virtual_processor_threads));
	      funk2_atomic_u64__set_value(&(cons->next), old_value);
	      add_used_success = funk2_atomic_u64__compare_and_swap(&(this->all_virtual_processor_threads), old_value, (u64)to_ptr(cons));
	    }
	  }
	}
	return virtual_processor_thread;
      }
      remove_free_success = funk2_atomic_u64__compare_and_swap(&(this->free_virtual_processor_threads), (u64)to_ptr(cons), funk2_atomic_u64__value(&(cons->next)));
    }
  }
  virtual_processor_thread = cons->virtual_processor_thread;
  f2__free(to_ptr(cons));
  funk2_atomic_u64__decrement(&(this->free_virtual_processor_thread_count));
  return virtual_processor_thread;
}

void funk2_virtual_processor_handler__know_of_virtual_processor_thread_assignment_to_virtual_processor(funk2_virtual_processor_handler_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread, u64 virtual_processor_index) {
  //status("funk2_virtual_processor_handler__know_of_virtual_processor_thread_assignment_to_virtual_processor: virtual_processor_index=" u64__fstr, virtual_processor_index);
  funk2_thread_safe_hash__add(&(this->virtual_processor_index_processor_thread_hash), (u64)to_ptr(virtual_processor_thread), virtual_processor_index);
  funk2_thread_safe_hash__add(&(this->virtual_processor_index_tid_hash), virtual_processor_thread->processor_thread->tid, (u64)virtual_processor_index);
  funk2_virtual_processor__know_of_one_more_assigned_virtual_processor_thread(this->virtual_processor[virtual_processor_index]);
}

void funk2_virtual_processor_handler__know_of_virtual_processor_thread_unassignment_from_virtual_processor(funk2_virtual_processor_handler_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread) {
  u64 virtual_processor_index = virtual_processor_thread->virtual_processor_assignment_index;
  //status("funk2_virtual_processor_handler__know_of_virtual_processor_thread_unassignment_from_virtual_processor: virtual_processor_thread->virtual_processor_assignment_index=" u64__fstr, virtual_processor_index);
  funk2_thread_safe_hash__remove(&(this->virtual_processor_index_processor_thread_hash), (u64)to_ptr(virtual_processor_thread));
  funk2_thread_safe_hash__remove(&(this->virtual_processor_index_tid_hash), virtual_processor_thread->processor_thread->tid);
  funk2_virtual_processor__know_of_one_less_spinning_virtual_processor_thread(this->virtual_processor[virtual_processor_index]);
  { // add to free processor thread list if we don't already have too many free threads
    if (funk2_atomic_u64__value(&(this->free_virtual_processor_thread_count)) < 100) {
      funk2_virtual_processor_thread_cons_t* cons = (funk2_virtual_processor_thread_cons_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_thread_cons_t)));
      cons->virtual_processor_thread              = virtual_processor_thread;
      {
	boolean_t success = boolean__false;
	while (! success) {
	  u64 old_value = funk2_atomic_u64__value(&(this->free_virtual_processor_threads));
	  funk2_atomic_u64__set_value(&(cons->next), old_value);
	  success = funk2_atomic_u64__compare_and_swap(&(this->free_virtual_processor_threads), old_value, (u64)to_ptr(cons));
	}
      }
      funk2_atomic_u64__increment(&(this->free_virtual_processor_thread_count));
    } else {
      funk2_virtual_processor_thread__signal_exit(virtual_processor_thread);
    }
  }
}

funk2_virtual_processor_thread_t* funk2_virtual_processor_handler__my_virtual_processor_thread(funk2_virtual_processor_handler_t* this) {
  funk2_processor_thread_t*         processor_thread         = funk2_processor_thread_handler__myself(&(__funk2.processor_thread_handler));
  funk2_virtual_processor_thread_t* virtual_processor_thread = (funk2_virtual_processor_thread_t*)from_ptr(funk2_thread_safe_hash__lookup(&(this->virtual_processor_thread_processor_thread_hash), (u64)to_ptr(processor_thread)));
  return virtual_processor_thread;
}

s64 funk2_virtual_processor_handler__try_get_my_virtual_processor_index(funk2_virtual_processor_handler_t* this) {
  if (__funk2.memory.bootstrapping_mode) {
    return 0;
  }
  f2tid_t tid = raw__gettid();
  return funk2_thread_safe_hash__try_lookup(&(this->virtual_processor_index_tid_hash), tid, (u64)-1);
}

u64 funk2_virtual_processor_handler__my_virtual_processor_index(funk2_virtual_processor_handler_t* this) {
  s64 virtual_processor_index = funk2_virtual_processor_handler__try_get_my_virtual_processor_index(this);
  if (virtual_processor_index == -1) {
    error(nil, "funk2_virtual_processor_handler__my_virtual_processor_index fatal error: could not find virtual processor index.");
  }
  return (u64)virtual_processor_index;
}

funk2_virtual_processor_t* funk2_virtual_processor_handler__try_get_my_virtual_processor(funk2_virtual_processor_handler_t* this) {
  s64 virtual_processor_assignment_index = funk2_virtual_processor_handler__try_get_my_virtual_processor_index(this);
  if (virtual_processor_assignment_index == -1) {
    return NULL;
  } else {
    return this->virtual_processor[virtual_processor_assignment_index];
  }
}

funk2_virtual_processor_t* funk2_virtual_processor_handler__my_virtual_processor(funk2_virtual_processor_handler_t* this) {
  s64 virtual_processor_assignment_index = funk2_virtual_processor_handler__try_get_my_virtual_processor_index(this);
#if defined(DEBUG)
  if (virtual_processor_assignment_index == -1) {
    error(nil, "funk2_virtual_processor_handler__my_virtual_processor fatal error: could not get my virtual processor.");
  }
#endif // defined(DEBUG)
  funk2_virtual_processor_t* my_virtual_processor = this->virtual_processor[virtual_processor_assignment_index];
  return my_virtual_processor;
}

void funk2_virtual_processor_handler__yield(funk2_virtual_processor_handler_t* this) {
  funk2_virtual_processor_t* virtual_processor = funk2_virtual_processor_handler__my_virtual_processor(this);
  funk2_virtual_processor__yield(virtual_processor);
}

void funk2_virtual_processor_handler__exit_fiber(funk2_virtual_processor_handler_t* this, f2ptr exit_value) {
  funk2_virtual_processor_t* virtual_processor = funk2_virtual_processor_handler__my_virtual_processor(this);
  funk2_virtual_processor__exit_fiber(virtual_processor, exit_value);
}


f2ptr f2__global_virtual_processor_handler__hardware_affinities_enabled(f2ptr cause) {
  return f2bool__new(__funk2.virtual_processor_handler.hardware_affinities_enabled);
}
def_pcfunk0(global_virtual_processor_handler__hardware_affinities_enabled,
	    "Gets a boolean value that tells the virtual_processor_handler whether or not to attempt to assign virtual_processors to specific underlying machine hardware processors.\n"
	    "Setting this value to true can improve CPU and core caching behavior in some instances.",
	    return f2__global_virtual_processor_handler__hardware_affinities_enabled(this_cause));


f2ptr f2__global_virtual_processor_handler__set_hardware_affinities_enabled(f2ptr cause, f2ptr hardware_affinities_enabled) {
  __funk2.virtual_processor_handler.hardware_affinities_enabled = ((hardware_affinities_enabled != nil) ? boolean__true : boolean__false);
  return nil;
}
def_pcfunk1(global_virtual_processor_handler__set_hardware_affinities_enabled, hardware_affinities_enabled,
	    "Sets a boolean value that tells the virtual_processor_handler whether or not to attempt to assign virtual_processors to specific underlying machine hardware processors.\n"
	    "This can improve CPU and core caching behavior in some instances.",
	    return f2__global_virtual_processor_handler__set_hardware_affinities_enabled(this_cause, hardware_affinities_enabled));



// **

void f2__virtual_processor_handler__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(global_virtual_processor_handler__hardware_affinities_enabled);
  f2__primcfunk__init__defragment__fix_pointers(global_virtual_processor_handler__set_hardware_affinities_enabled);
}

void f2__virtual_processor_handler__reinitialize_globalvars() {
  f2__primcfunk__init__0(global_virtual_processor_handler__hardware_affinities_enabled);
  f2__primcfunk__init__1(global_virtual_processor_handler__set_hardware_affinities_enabled, enable_hardware_affinities);
}

void f2__virtual_processor_handler__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "virtual_processor_handler", "", &f2__virtual_processor_handler__reinitialize_globalvars, &f2__virtual_processor_handler__defragment__fix_pointers);
  
  f2__virtual_processor_handler__reinitialize_globalvars();
}

