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

#define F2__PTYPE__C__COMPILING

#include "funk2.h"

void print_cmutex_error(int retval) {
  switch (retval) {
  case EINVAL: error(nil, "error unlocking ptype_cmutex: cmutex is not initialized.");              break;
  case EFAULT: error(nil, "error unlocking ptype_cmutex: cmutex is an invalid pointer.");           break;
  case EPERM:  error(nil, "error unlocking ptype_cmutex: the calling thread does not own cmutex."); break;
  default:     error(nil, "error unlocking ptype_cmutex: unknown error.");                          break;
  }
}

void raw__exp__increment_reference_count(f2ptr this) {
  if (this) {
    funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this));
    atomic_inc(&(block->reference_count));
  }
}

void debug__contradictory_atomic_dec_and_test() {
  printf("\ncontradictory atomic dec and test.");
  status(  "contradictory atomic dec and test.");
}

boolean_t raw__exp__decrement_reference_count(f2ptr this) {
  boolean_t no_more_references = boolean__false;
  if (this) {
    funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this));
    no_more_references      = atomic_dec_and_test(&(block->reference_count));
    //if (no_more_references) {
    //if (atomic_read(&(block->reference_count)) != 0) { // double check...
    //debug__contradictory_atomic_dec_and_test();
    //}
    //}
  }
  return no_more_references;
}

// notify garbage collector of changed references and mutated memory.
void funk2_garbage_collector__know_of_changed_references(funk2_garbage_collector_t* this, f2ptr exp, f2ptr old_value, f2ptr value) {
  if (old_value) {
    boolean_t no_more_references = raw__exp__decrement_reference_count(old_value);
    if (no_more_references) {
      // notify garbage collector to whiten old value if it is not already because it has no references (because of no references it doesn't upset the "no black references white" invariant).
      funk2_garbage_collector__know_of_no_more_references(this, old_value);
    }
  }
  if (value) {
    raw__exp__increment_reference_count(value);
  }
  
  // notify garbage collector to grey this memory if it is black because it has been mutated.
  funk2_garbage_collector__know_of_used_exp_mutation(this, exp);
  
  if (old_value) {
    // protect the old value
    funk2_garbage_collector__know_of_protected_f2ptr(this, old_value);
  }
} 

// monitor cause-cause read/write interactions

#define container__reflectively_know_of_reading_from(cause, container, data, sizeof_data) { \
    if (__funk2.ptypes.read_write_reflective_tracing_enabled) {		\
      raw__container__reflectively_know_of_reading_from(cause, container, data, sizeof_data); \
    }									\
  }

void raw__container__reflectively_know_of_reading_from(f2ptr cause, f2ptr container, f2ptr data, u64 sizeof_data) {
  if (cause != nil) {
    if (container != nil) {
      f2ptr current_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
      if (current_fiber != nil) {
	f2ptr reflective_cause = nil;
	f2ptr container__cause = f2ptype__cause(container, reflective_cause);
	if ((container__cause != nil) &&
	    (container__cause != cause)) {
	  f2ptr cause__cause_groups            = f2cause__cause_groups(cause,            reflective_cause);
	  f2ptr container__cause__cause_groups = f2cause__cause_groups(container__cause, reflective_cause);
	  if ((cause__cause_groups            != nil) &&
	      (container__cause__cause_groups != nil)) {
	    f2ptr cause__cause_group_iter = cause__cause_groups;
	    while (cause__cause_group_iter != nil) {
	      f2ptr cause__cause_group = f2cons__car(cause__cause_group_iter, reflective_cause);
	      {
		f2ptr container__cause__cause_group_iter = container__cause__cause_groups;
		while (container__cause__cause_group_iter != nil) {
		  f2ptr container__cause__cause_group = f2cons__car(container__cause__cause_group_iter, reflective_cause);
		  {
		    f2ptr cause__cause_group__cause_group_interaction_scheduler_ptypehash = f2cause_group__cause_group_interaction_scheduler_ptypehash(cause__cause_group, reflective_cause);
		    f2ptr cause_group_interaction                                         = raw__scheduler_ptypehash__lookup(reflective_cause, cause__cause_group__cause_group_interaction_scheduler_ptypehash, container__cause__cause_group);
		    if (cause_group_interaction != nil) {
		      raw__cause_group_interaction__increase_bytes_read_count(reflective_cause, cause_group_interaction, sizeof_data);
		    }
		  }
		  container__cause__cause_group_iter = f2cons__cdr(container__cause__cause_group_iter, reflective_cause);
		}
	      }
	      cause__cause_group_iter = f2cons__cdr(cause__cause_group_iter, reflective_cause);
	    }
	  }
	}
      }
    }
  }
}

#define container__reflectively_know_of_writing_to(cause, container, data, sizeof_data) { \
    if (__funk2.ptypes.read_write_reflective_tracing_enabled) {		\
      raw__container__reflectively_know_of_writing_to(cause, container, data, sizeof_data); \
    }									\
  }

void raw__container__reflectively_know_of_writing_to(f2ptr cause, f2ptr container, f2ptr data, u64 sizeof_data) {
  if (cause != nil) {
    if (container != nil) {
      f2ptr current_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
      if (current_fiber != nil) {
	f2ptr reflective_cause = nil;
	f2ptr container__cause = f2ptype__cause(container, reflective_cause);
	if (container__cause != nil) {
	  f2ptr cause__cause_groups            = f2cause__cause_groups(cause,            reflective_cause);
	  f2ptr container__cause__cause_groups = f2cause__cause_groups(container__cause, reflective_cause);
	  if ((cause__cause_groups            != nil) &&
	      (container__cause__cause_groups != nil)) {
	    f2ptr cause__cause_group_iter = cause__cause_groups;
	    while (cause__cause_group_iter != nil) {
	      f2ptr cause__cause_group = f2cons__car(cause__cause_group_iter, reflective_cause);
	      {
		f2ptr container__cause__cause_group_iter = container__cause__cause_groups;
		while (container__cause__cause_group_iter != nil) {
		  f2ptr container__cause__cause_group = f2cons__car(container__cause__cause_group_iter, reflective_cause);
		  {
		    f2ptr cause__cause_group__cause_group_interaction_scheduler_ptypehash = f2cause_group__cause_group_interaction_scheduler_ptypehash(cause__cause_group, reflective_cause);
		    f2ptr cause_group_interaction                                         = raw__scheduler_ptypehash__lookup(reflective_cause, cause__cause_group__cause_group_interaction_scheduler_ptypehash, container__cause__cause_group);
		    if (cause_group_interaction != nil) {
		      raw__cause_group_interaction__increase_bytes_written_count(reflective_cause, cause_group_interaction, sizeof_data);
		    }
		  }
		  container__cause__cause_group_iter = f2cons__cdr(container__cause__cause_group_iter, reflective_cause);
		}
	      }
	      cause__cause_group_iter = f2cons__cdr(cause__cause_group_iter, reflective_cause);
	    }
	  }
	}
      }
    }
  }
}


// used by global initialization for creation (and other) causes

f2ptr initial_cause() {
  return nil;
}

// this.system

f2ptr pfunk2__system__environment(f2ptr cause) {
  container__reflectively_know_of_reading_from(cause, nil, __funk2.memory.global_environment_f2ptr, sizeof(f2ptr));
  return __funk2.memory.global_environment_f2ptr;
}

// memblock

boolean_t raw__cause__is_traced__trace_depth(f2ptr cause, f2ptr this, int trace_depth) {
  if (! this) {
    return nil;
  }
#ifdef F2__PTYPE__TYPE_CHECK
  //if(! raw__cause__is_type(cause, this)) {
  //  status("raw__cause__is_traced !raw__cause__is_type(cause, this)");
  //  f2__print(nil, this); fflush(stdout);
  //  error(nil, "raw__cause__is_traced !raw__cause__is_type(cause, this)");
  //}
#endif
  return f2cause__memory_tracing_on__trace_depth(this, cause, trace_depth);
}

boolean_t raw__cause__is_traced(f2ptr cause, f2ptr this) {
  return raw__cause__is_traced__trace_depth(cause, this, 0);
}

void debug__cause__is_imaginary() {
  //printf("\ndebug__cause__is_imaginary here.");
}

boolean_t raw__cause__is_imaginary__trace_depth(f2ptr cause, f2ptr this, int trace_depth) {
  if (! this) {
    return nil;
  }
#ifdef F2__PTYPE__TYPE_CHECK
  //if(! raw__cause__is_type(cause, this)) {
  //  status("raw__cause__is_imaginary !raw__cause__is_type(cause, this)");
  //  f2__print(nil, this); fflush(stdout);
  //  error(nil, "raw__cause__is_imaginary !raw__cause__is_type(cause, this)");
  //}
#endif
  f2ptr the_cause_for_checking_whether_imaginary_or_not = nil; // avoids infinitely considering whether or not we are imagining by returning the "real" value of our cause's imagination stack... (see South Park, ImaginationLand Episode for elaboration)
  boolean_t return_value = (f2cause__imagination_stack(this, the_cause_for_checking_whether_imaginary_or_not) != nil);
  if (return_value) {
    debug__cause__is_imaginary();
  }
  return return_value;
}

boolean_t raw__cause__is_imaginary(f2ptr cause, f2ptr this) {
  return raw__cause__is_imaginary__trace_depth(cause, this, 0);
}

void ptype_error(f2ptr cause, f2ptr this, f2ptr expected_type) {
  error(nil, "ptype_error.");
}

// ptype

ptype_t pfunk2__f2ptype__raw(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  ptype_t retval = __pure__f2ptype__raw(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(retval));
  return retval;
}

f2ptr pfunk2__f2ptype__cause(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  f2ptr value = __pure__f2ptype__cause(this);
  debug__assert((! value) || raw__cause__is_type(cause, value), nil, "debug error: value is not cause.");
  container__reflectively_know_of_reading_from(cause, this, value, sizeof(value));
  return value;
}

f2ptr pfunk2__f2ptype__cause__set(f2ptr this, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  debug__assert((! value) || raw__cause__is_type(cause, value), nil, "debug error: value is not cause.");
  f2ptr old_value = __pure__f2ptype__cause(this);
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  __pure__f2ptype__cause(this) = value;
  container__reflectively_know_of_writing_to(cause, this, value, sizeof(value));
  return nil;
}

f2ptr pfunk2__f2ptype__creation_fiber(f2ptr this, f2ptr cause) {
  check_wait_politely();
  f2ptr value = __pure__f2ptype__creation_fiber(this);
  container__reflectively_know_of_reading_from(cause, this, value, sizeof(value));
  return value;
}

f2ptr pfunk2__f2ptype__creation_fiber__set(f2ptr this, f2ptr cause, f2ptr value) {
  check_wait_politely();
  f2ptr old_value = __pure__f2ptype__creation_fiber(this);
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  __pure__f2ptype__creation_fiber(this) = value;
  container__reflectively_know_of_writing_to(cause, this, value, sizeof(value));
  return nil;
}

boolean_t __ptypes__creation_cause_enabled = boolean__true;
boolean_t __ptypes__creation_fiber_enabled = boolean__true;

// integer

f2ptr ptype_integer__new(int pool_index, f2ptr cause, s64 i) {
  f2ptr integer_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_integer_block_t));
  ptype_integer_block_t* integer_block = (ptype_integer_block_t*)from_ptr(raw__f2ptr_to_ptr(integer_f2ptr));
  debug__assert(integer_block, nil, "block is nil.");
  integer_block->ptype.block.ptype    = ptype_integer;
  if (__ptypes__creation_cause_enabled) {
    if (cause != nil) {raw__exp__increment_reference_count(cause);}
    integer_block->ptype.cause = cause;
  } else {
    integer_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    integer_block->ptype.creation_fiber = creation_fiber;
  } else {
    integer_block->ptype.creation_fiber = nil;
  }
  integer_block->i = i;
  return integer_f2ptr;
}

f2ptr pfunk2__f2integer__new(f2ptr cause, s64 i) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2integer__new(pool_index, cause, i);
  return retval;
}

s64 pfunk2__f2integer__i(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_integer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_integer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  s64 i = __pure__f2integer__i(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(i));
  return i;
}




// double

f2ptr ptype_double__new(int pool_index, f2ptr cause, double d) {
  f2ptr double_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_double_block_t));
  ptype_double_block_t* double_block = (ptype_double_block_t*)from_ptr(raw__f2ptr_to_ptr(double_f2ptr));
  debug__assert(double_block, nil, "block is nil.");
  double_block->ptype.block.ptype = ptype_double;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    double_block->ptype.cause = cause;
  } else {
    double_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    double_block->ptype.creation_fiber = creation_fiber;
  } else {
    double_block->ptype.creation_fiber = nil;
  }
  double_block->d = d;
  return double_f2ptr;
}

f2ptr pfunk2__f2double__new(f2ptr cause, double d) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2double__new(pool_index, cause, d);
  return retval;
}

double pfunk2__f2double__d(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_double) {
    ptype_error(cause, this, __funk2.globalenv.ptype_double__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  double d = __pure__f2double__d(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(d));
  return d;
}





// float

f2ptr ptype_float__new(int pool_index, f2ptr cause, float f) {
  f2ptr float_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_float_block_t));
  ptype_float_block_t* float_block = (ptype_float_block_t*)from_ptr(raw__f2ptr_to_ptr(float_f2ptr));
  debug__assert(float_block, nil, "block is nil.");
  float_block->ptype.block.ptype    = ptype_float;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    float_block->ptype.cause = cause;
  } else {
    float_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    float_block->ptype.creation_fiber = creation_fiber;
  } else {
    float_block->ptype.creation_fiber = nil;
  }
  float_block->f = f;
  return float_f2ptr;
}

f2ptr pfunk2__f2float__new(f2ptr cause, float f) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2float__new(pool_index, cause, f);
  return retval;
}

float pfunk2__f2float__f(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_float) {
    ptype_error(cause, this, __funk2.globalenv.ptype_float__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  float f = __pure__f2float__f(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(f));
  return f;
}






// pointer

f2ptr ptype_pointer__new(int pool_index, f2ptr cause, ptr p) {
  f2ptr pointer_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_pointer_block_t));
  ptype_pointer_block_t* pointer_block = (ptype_pointer_block_t*)from_ptr(raw__f2ptr_to_ptr(pointer_f2ptr));
  debug__assert(pointer_block, nil, "block is nil.");
  pointer_block->ptype.block.ptype    = ptype_pointer;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    pointer_block->ptype.cause = cause;
  } else {
    pointer_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    pointer_block->ptype.creation_fiber = creation_fiber;
  } else {
    pointer_block->ptype.creation_fiber = nil;
  }
  pointer_block->p = p;
  return pointer_f2ptr;
}

f2ptr pfunk2__f2pointer__new(f2ptr cause, ptr p) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2pointer__new(pool_index, cause, p);
  return retval;
}

ptr pfunk2__f2pointer__p(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_pointer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_pointer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  ptr p = __pure__f2pointer__p(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(p));
  return p;
}






// cmutex

f2ptr ptype_cmutex__new(int pool_index, f2ptr cause) {
  f2ptr cmutex_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_cmutex_block_t));
  ptype_cmutex_block_t* cmutex_block = (ptype_cmutex_block_t*)from_ptr(raw__f2ptr_to_ptr(cmutex_f2ptr));
  debug__assert(cmutex_block, nil, "block is nil.");
  cmutex_block->ptype.block.ptype    = ptype_cmutex;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    cmutex_block->ptype.cause = cause;
  } else {
    cmutex_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    cmutex_block->ptype.creation_fiber = creation_fiber;
  } else {
    cmutex_block->ptype.creation_fiber = nil;
  }
  cmutex_block->locked_state         = boolean__false;
  funk2_processor_mutex__init(cmutex_block->m);
  return cmutex_f2ptr;
}

f2ptr pfunk2__f2cmutex__new(f2ptr cause) {
  check_wait_politely();
  int   pool_index = this_processor_thread__pool_index();
  f2ptr retval     = __pure__f2cmutex__new(pool_index, cause);
  return retval;
}

funk2_processor_mutex_t* ptype_cmutex__m(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  funk2_processor_mutex_t* m = __pure__f2cmutex__m(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(m));
  return m;
}

boolean_t pfunk2__f2cmutex__is_locked(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  //int pool_index = this_processor_thread__pool_index();
  boolean_t is_locked = funk2_processor_mutex__is_locked(ptype_cmutex__m(this, cause));
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(boolean_t));
  return is_locked;
}

void pfunk2__f2cmutex__unlock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  // note that this assumes the cmutex is locked.
  __pure__f2cmutex__locked_state__set(this, boolean__false);
  funk2_processor_mutex__unlock(ptype_cmutex__m(this, cause));
  container__reflectively_know_of_writing_to(cause, this, nil, sizeof(boolean_t));
}

int pfunk2__f2cmutex__trylock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int return_value = funk2_processor_mutex__trylock(ptype_cmutex__m(this, cause));
  if (return_value == 0) {
    __pure__f2cmutex__locked_state__set(this, boolean__true);
    container__reflectively_know_of_writing_to(cause, this, nil, sizeof(boolean_t));
  }
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(return_value));
  return return_value;
}






// creadwritelock

f2ptr ptype_creadwritelock__new(int pool_index, f2ptr cause) {
  f2ptr creadwritelock_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_creadwritelock_block_t));
  ptype_creadwritelock_block_t* creadwritelock_block = (ptype_creadwritelock_block_t*)from_ptr(raw__f2ptr_to_ptr(creadwritelock_f2ptr));
  debug__assert(creadwritelock_block, nil, "block is nil.");
  creadwritelock_block->ptype.block.ptype    = ptype_creadwritelock;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    creadwritelock_block->ptype.cause = cause;
  } else {
    creadwritelock_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    creadwritelock_block->ptype.creation_fiber = creation_fiber;
  } else {
    creadwritelock_block->ptype.creation_fiber = nil;
  }
  funk2_processor_readwritelock__init(creadwritelock_block->rwlock);
  return creadwritelock_f2ptr;
}

f2ptr pfunk2__f2creadwritelock__new(f2ptr cause) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2creadwritelock__new(pool_index, cause);
  return retval;
}

funk2_processor_readwritelock_t* ptype_creadwritelock__rwlock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  funk2_processor_readwritelock_t* rwlock = __pure__f2creadwritelock__rwlock(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(rwlock));
  return rwlock;
}

boolean_t pfunk2__f2creadwritelock__is_writelocked(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_creadwritelock) {
    ptype_error(cause, this, __funk2.globalenv.ptype_creadwritelock__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  boolean_t is_writelocked = funk2_processor_readwritelock__is_writelocked(ptype_creadwritelock__rwlock(this, cause));
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(boolean_t));
  return is_writelocked;
}

boolean_t pfunk2__f2creadwritelock__is_readlocked(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_creadwritelock) {
    ptype_error(cause, this, __funk2.globalenv.ptype_creadwritelock__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  boolean_t is_readlocked = funk2_processor_readwritelock__is_readlocked(ptype_creadwritelock__rwlock(this, cause));
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(boolean_t));
  return is_readlocked;
}

void pfunk2__f2creadwritelock__unlock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_creadwritelock) {
    ptype_error(cause, this, __funk2.globalenv.ptype_creadwritelock__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  // note that this assumes the creadwritelock is locked.
  funk2_processor_readwritelock__unlock(ptype_creadwritelock__rwlock(this, cause));
  container__reflectively_know_of_writing_to(cause, this, nil, sizeof(boolean_t));
}

int pfunk2__f2creadwritelock__trywritelock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_creadwritelock) {
    ptype_error(cause, this, __funk2.globalenv.ptype_creadwritelock__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int return_value = funk2_processor_readwritelock__trywritelock(ptype_creadwritelock__rwlock(this, cause));
  if (return_value == 0) {
    container__reflectively_know_of_writing_to(cause, this, nil, sizeof(boolean_t));
  }
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(return_value));
  return return_value;
}

int pfunk2__f2creadwritelock__tryreadlock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_creadwritelock) {
    ptype_error(cause, this, __funk2.globalenv.ptype_creadwritelock__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int return_value = funk2_processor_readwritelock__tryreadlock(ptype_creadwritelock__rwlock(this, cause));
  if (return_value == 0) {
    container__reflectively_know_of_writing_to(cause, this, nil, sizeof(boolean_t));
  }
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(return_value));
  return return_value;
}






// char

f2ptr ptype_char__new(int pool_index, f2ptr cause, funk2_character_t ch) {
  f2ptr char_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_char_block_t));
  ptype_char_block_t* char_block = (ptype_char_block_t*)from_ptr(raw__f2ptr_to_ptr(char_f2ptr));
  debug__assert(char_block, nil, "block is nil.");
  char_block->ptype.block.ptype    = ptype_char;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    char_block->ptype.cause = cause;
  } else {
    char_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    char_block->ptype.creation_fiber = creation_fiber;
  } else {
    char_block->ptype.creation_fiber = nil;
  }
  char_block->ch = ch;
  return char_f2ptr;
}

f2ptr pfunk2__f2char__new(f2ptr cause, funk2_character_t ch) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2char__new(pool_index, cause, ch);
  return retval;
}

funk2_character_t pfunk2__f2char__ch(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_char) {
    ptype_error(cause, this, __funk2.globalenv.ptype_char__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 ch = __pure__f2char__ch(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(ch));
  return ch;
}





// string

f2ptr ptype_string__new(int pool_index, f2ptr cause, u64 length, funk2_character_t* str) {
  f2ptr                 string_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_string_block_t) + ((length + 1) * sizeof(funk2_character_t)));
  ptype_string_block_t* string_block = (ptype_string_block_t*)from_ptr(raw__f2ptr_to_ptr(string_f2ptr));
  debug__assert(string_block, nil, "block is nil.");
  string_block->ptype.block.ptype    = ptype_string;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    string_block->ptype.cause = cause;
  } else {
    string_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    string_block->ptype.creation_fiber = creation_fiber;
  } else {
    string_block->ptype.creation_fiber = nil;
  }
  string_block->length               = length;
  if (str) {memcpy(string_block->str, str, length * sizeof(funk2_character_t));}
  else     {memset(string_block->str, 0,   length * sizeof(funk2_character_t));}
  string_block->str[length] = 0;
  return string_f2ptr;
}

f2ptr pfunk2__f2string__new(f2ptr cause, u64 length, funk2_character_t* init) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2string__new(pool_index, cause, length, init);
  return retval;
}

u64 pfunk2__f2string__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64  length = __pure__f2string__length(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(length));
  return length;
}

funk2_character_t pfunk2__f2string__elt(f2ptr this, int index, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  funk2_character_t ch = __pure__f2string__str(this)[index];
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(ch));
  return ch;
}

void pfunk2__f2string__elt__set(f2ptr this, int index, f2ptr cause, funk2_character_t ch) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2string__str(this)[index] = ch;
  container__reflectively_know_of_writing_to(cause, this, nil, sizeof(ch));
}

void pfunk2__f2string__str_copy(f2ptr this, f2ptr cause, funk2_character_t* str) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 total_length = __pure__f2string__length(this) * sizeof(funk2_character_t);
  memcpy(str, __pure__f2string__str(this), total_length);
  container__reflectively_know_of_reading_from(cause, this, nil, total_length);
}

u64 pfunk2__f2string__eq_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 return_value = (u64)this;
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(return_value));
  return return_value;
}






// symbol

f2ptr ptype_symbol__new(int pool_index, f2ptr cause, u64 length, funk2_character_t* str) {
  if (length == 0) {
    return nil;
  }
  return funk2_symbol_hash__lookup_or_create_symbol(&(__funk2.ptypes.symbol_hash), pool_index, cause, length, str);
}

f2ptr pfunk2__f2symbol__new(f2ptr cause, u64 length, funk2_character_t* init) {
  check_wait_politely();
  int   pool_index = this_processor_thread__pool_index();
  f2ptr retval     = __pure__f2symbol__new(pool_index, cause, length, init);
  return retval;
}

u64 pfunk2__f2symbol__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2symbol__length(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(length));
  return length;
}

u64 pfunk2__f2symbol__eq_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 eq_hash_value = __pure__f2symbol__eq_hash_value(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(eq_hash_value));
  return eq_hash_value;
}

funk2_character_t pfunk2__f2symbol__elt(f2ptr this, int index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  funk2_character_t ch = __pure__f2symbol__str(this)[index];
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(ch));
  return ch;
}

void pfunk2__f2symbol__str_copy(f2ptr this, f2ptr cause, funk2_character_t* str) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 total_length = __pure__f2symbol__length(this) * sizeof(funk2_character_t);
  memcpy(str, __pure__f2symbol__str(this), total_length);
  container__reflectively_know_of_reading_from(cause, this, nil, total_length);
}






// chunk

f2ptr ptype_chunk__new(int pool_index, f2ptr cause, u64 length, byte* bytes) {
  u64 data_byte_num = (sizeof(u8) * length);
  f2ptr chunk_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_chunk_block_t) + data_byte_num);
  ptype_chunk_block_t* chunk_block = (ptype_chunk_block_t*)from_ptr(raw__f2ptr_to_ptr(chunk_f2ptr));
  debug__assert(chunk_block, nil, "block is nil.");
  chunk_block->ptype.block.ptype    = ptype_chunk;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    chunk_block->ptype.cause = cause;
  } else {
    chunk_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    chunk_block->ptype.creation_fiber = creation_fiber;
  } else {
    chunk_block->ptype.creation_fiber = nil;
  }
  chunk_block->length               = length;
  if (bytes) {memcpy(chunk_block->bytes, bytes, data_byte_num);}
  else       {memset(chunk_block->bytes, 0,     data_byte_num);}
  return chunk_f2ptr;
}

f2ptr ptype_chunk__new_copy(int pool_index, f2ptr cause, f2ptr init_chunk) {
  ptype_chunk_block_t* init_chunk_block = (ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(init_chunk)));
  u64 data_byte_num = (sizeof(u8) * init_chunk_block->length);
  f2ptr chunk_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_chunk_block_t));
  ptype_chunk_block_t* chunk_block = (ptype_chunk_block_t*)from_ptr(raw__f2ptr_to_ptr(chunk_f2ptr));
  debug__assert(chunk_block, nil, "block is nil.");
  chunk_block->ptype.block.ptype    = ptype_chunk;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    chunk_block->ptype.cause = cause;
  } else {
    chunk_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    chunk_block->ptype.creation_fiber = creation_fiber;
  } else {
    chunk_block->ptype.creation_fiber = nil;
  }
  chunk_block->length               = init_chunk_block->length;
  memcpy(chunk_block->bytes, init_chunk_block->bytes, data_byte_num);
  return chunk_f2ptr;
}

u8* ptype_chunk__bytes(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u8* bytes = __pure__f2chunk__bytes(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(bytes));
  return bytes;
}

f2ptr pfunk2__f2chunk__new(f2ptr cause, u64 length, byte* bytes) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2chunk__new(pool_index, cause, length, bytes);
  return retval;
}

f2ptr pfunk2__f2chunk__new_copy(f2ptr cause, f2ptr init_chunk) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2chunk__new_copy(pool_index, cause, init_chunk);
  return retval;
}

u64 pfunk2__f2chunk__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2chunk__length(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(length));
  return length;
}

void pfunk2__f2chunk__str_copy(f2ptr this, f2ptr cause, u8* str) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 total_length = __pure__f2chunk__length(this);
  memcpy(str, __pure__f2chunk__bytes(this), total_length);
  container__reflectively_know_of_reading_from(cause, this, nil, total_length);
}

u64 pfunk2__f2chunk__eq_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 return_value = (u64)this;
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(return_value));
  return return_value;
}

u64 pfunk2__f2chunk__equals_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 len   = __pure__f2chunk__length(this);
  u8* bytes = __pure__f2chunk__bytes(this);
  u64 return_value = (u64)chararray__hash_value(len, bytes);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(return_value));
  return return_value;
}

u8 pfunk2__f2chunk__bit8__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u8 retval = __pure__f2chunk__bit8__elt(this, index);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(retval));
  return retval;
}

void  pfunk2__f2chunk__bit8__elt__set(f2ptr this, u64 index, f2ptr cause, u8 value)   {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
  __pure__f2chunk__bit8__elt__set(this, index, value);
  container__reflectively_know_of_writing_to(cause, this, nil, sizeof(value));
}

u16 pfunk2__f2chunk__bit16__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u16 retval = __pure__f2chunk__bit16__elt(this, index);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(retval));
  return retval;
}

void pfunk2__f2chunk__bit16__elt__set(f2ptr this, u64 index, f2ptr cause, u16 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit16__elt__set(this, index, value);
  container__reflectively_know_of_writing_to(cause, this, nil, sizeof(value));
}

u32 pfunk2__f2chunk__bit32__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u32 retval = __pure__f2chunk__bit32__elt(this, index);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(retval));
  return retval;
}

void pfunk2__f2chunk__bit32__elt__set(f2ptr this, u64 index, f2ptr cause, u32 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit32__elt__set(this, index, value);
  container__reflectively_know_of_writing_to(cause, this, nil, sizeof(value));
}

u64 pfunk2__f2chunk__bit64__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 retval = __pure__f2chunk__bit64__elt(this, index);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(retval));
  return retval;
}

void pfunk2__f2chunk__bit64__elt__set(f2ptr this, u64 index, f2ptr cause, u64 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit64__elt__set(this, index, value);
  container__reflectively_know_of_writing_to(cause, this, nil, sizeof(value));
}

f2ptr pfunk2__f2chunk__cfunk_jump(f2ptr this, f2ptr cause, f2ptr fiber, f2ptr env, f2ptr args) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  cfunkptr_t jump = (cfunkptr_t)(((ptype_chunk_block_t*)from_ptr(f2ptr_to_ptr(this)))->bytes);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(jump));
  printf("\nchunk-cfunk_jump: jumping to 0x%08lx", (long)jump); fflush(stdout);
  return jump(cause, fiber, env, args);
}

int pfunk2__f2chunk__bytecode_jump(f2ptr this, f2ptr cause, f2ptr fiber) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  bytecode_jump_t jump = (bytecode_jump_t)(((ptype_chunk_block_t*)from_ptr(f2ptr_to_ptr(this)))->bytes);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(jump));
  //printf("\nchunk-bytecode_jump: jumping to 0x%08lx", (long)jump); fflush(stdout);
  f2ptr bytecode = nil;
  return jump(fiber, bytecode);
}

f2ptr pfunk2__f2chunk__send(f2ptr this, f2ptr cause, int start, int length, int fd, int flags) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr rv = f2integer__new(cause, send(fd, ((u8*)(__pure__f2chunk__bytes(this))) + start, length, flags));
  container__reflectively_know_of_reading_from(cause, this, nil, length);
  return rv;
}

f2ptr pfunk2__f2chunk__recv(f2ptr this, f2ptr cause, int start, int length, int fd, int flags) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr rv = f2integer__new(cause, recv(fd, ((u8*)(__pure__f2chunk__bytes(this))) + start, length, flags));
  container__reflectively_know_of_writing_to(cause, this, nil, length);
  return rv;
}





// cons

f2ptr ptype_cons__new(int pool_index, f2ptr cause, f2ptr car, f2ptr cdr) {
  f2ptr cons_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_cons_block_t));
  ptype_cons_block_t* cons_block = (ptype_cons_block_t*)from_ptr(raw__f2ptr_to_ptr(cons_f2ptr));
  debug__assert(cons_block, nil, "block is nil.");
  //debug__assert(!cause || valid_funk2_memblock_ptr(f2ptr_to_ptr(cause)), nil, "valid_funk2_memblock_ptr(cause) failed");
  cons_block->ptype.block.ptype = ptype_cons;
  if (__ptypes__creation_cause_enabled) {
    if (cause != nil) {raw__exp__increment_reference_count(cause);}
    cons_block->ptype.cause = cause;
  } else {
    cons_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    cons_block->ptype.creation_fiber = creation_fiber;
  } else {
    cons_block->ptype.creation_fiber = nil;
  }
  {
    if (car != nil) {raw__exp__increment_reference_count(car);}
    cons_block->car.data = car;
  }
  {
    if (cdr != nil) {raw__exp__increment_reference_count(cdr);}
    cons_block->cdr.data = cdr;
  }
  return cons_f2ptr;
}

f2ptr pfunk2__f2cons__new(f2ptr cause, f2ptr car, f2ptr cdr) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr this = __pure__f2cons__new(pool_index, cause, car, cdr);
  return this;
}

f2ptr pfunk2__f2cons__car(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cons) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cons__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr rv = __pure__f2cons__car(this);
  container__reflectively_know_of_reading_from(cause, this, rv, sizeof(rv));
  return rv;
}

f2ptr pfunk2__f2cons__car__set(f2ptr this, f2ptr cause, f2ptr value) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cons) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cons__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr old_value = __pure__f2cons__car(this);
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  
  __pure__f2cons__car__set(this, value);
  container__reflectively_know_of_writing_to(cause, this, value, sizeof(value));
  return nil;
}

f2ptr pfunk2__f2cons__cdr(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cons) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cons__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr rv = __pure__f2cons__cdr(this);
  container__reflectively_know_of_reading_from(cause, this, rv, sizeof(rv));
  return rv;
}

f2ptr pfunk2__f2cons__cdr__set(f2ptr this, f2ptr cause, f2ptr value) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cons) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cons__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr old_value = __pure__f2cons__cdr(this);
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  
  __pure__f2cons__cdr__set(this, value);
  container__reflectively_know_of_writing_to(cause, this, value, sizeof(value));
  return nil;
}





// simple_array

f2ptr ptype_simple_array__new(int pool_index, f2ptr cause, u64 length, ptr f2ptr_ptr) {
  u64 data_byte_num = (sizeof(f2ptr_t) * length);
  f2ptr simple_array_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_simple_array_block_t) + data_byte_num);
  ptype_simple_array_block_t* simple_array_block = (ptype_simple_array_block_t*)from_ptr(raw__f2ptr_to_ptr(simple_array_f2ptr));
  debug__assert(simple_array_block, nil, "block is nil.");
  //debug__assert(!cause || valid_funk2_memblock_ptr(f2ptr_to_ptr(cause)), nil, "valid_funk2_memblock_ptr(cause) failed");
  simple_array_block->ptype.block.ptype    = ptype_simple_array;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    simple_array_block->ptype.cause = cause;
  } else {
    simple_array_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    simple_array_block->ptype.creation_fiber = creation_fiber;
  } else {
    simple_array_block->ptype.creation_fiber = nil;
  }
  simple_array_block->length               = length;
  if (f2ptr_ptr) {memcpy(simple_array_block->slot, from_ptr(f2ptr_ptr), data_byte_num);}
  else           {memset(simple_array_block->slot, 0,                   data_byte_num);}
  return simple_array_f2ptr;
}

f2ptr pfunk2__f2simple_array__new(f2ptr cause, u64 length, ptr f2ptr_ptr) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr this = __pure__f2simple_array__new(pool_index, cause, length, f2ptr_ptr);
  return this;
}

f2ptr pfunk2__f2simple_array__new_copy(f2ptr cause, u64 length, f2ptr init_array) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(init_array) != ptype_simple_array) {
    ptype_error(cause, init_array, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  container__reflectively_know_of_reading_from(cause, init_array, nil, sizeof(f2ptr) * length);
  return pfunk2__f2simple_array__new(cause, length, to_ptr(((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(init_array))))->slot));
}

u64 pfunk2__f2simple_array__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2simple_array__length(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(length));
  return length;
}

#ifdef DEBUG
#  define F2__PTYPE__SIMPLE_ARRAY__BOUNDARY_CHECK
#endif // DEBUG

f2ptr pfunk2__f2simple_array__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2array_elt failed debug assertion: cause is non-null and not a cause.");
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
#ifdef F2__PTYPE__SIMPLE_ARRAY__BOUNDARY_CHECK
  int length = __pure__f2simple_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
    //error(nil, "f2array__elt error: index out of range.");
  }
#endif
  f2ptr rv = __pure__f2simple_array__elt(this, index);
  container__reflectively_know_of_reading_from(cause, this, rv, sizeof(rv));
  return rv;
}

f2ptr pfunk2__f2simple_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2array_elt failed debug assertion: cause is non-null and not a cause.");
  
  //int pool_index = __f2ptr__pool_index(this);
  
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length     = __pure__f2simple_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
    //error(nil, "f2array__elt__set__trace_depth error: index out of range.");
  }
  
  f2ptr old_value = __pure__f2simple_array__elt(this, index);
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  
  __pure__f2simple_array__elt__set(this, index, value);
  container__reflectively_know_of_writing_to(cause, this, value, sizeof(value));
  return nil;
}





// larva

f2ptr ptype_larva__new(int pool_index, f2ptr cause, u32 larva_type, f2ptr bug) {
  f2ptr larva_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_larva_block_t));
  ptype_larva_block_t* larva_block = (ptype_larva_block_t*)from_ptr(raw__f2ptr_to_ptr(larva_f2ptr));
  debug__assert(larva_block, nil, "block is nil.");
  larva_block->ptype.block.ptype    = ptype_larva;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    larva_block->ptype.cause = cause;
  } else {
    larva_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    larva_block->ptype.creation_fiber = creation_fiber;
  } else {
    larva_block->ptype.creation_fiber = nil;
  }
  larva_block->larva_type = larva_type;
  {
    if (bug) {raw__exp__increment_reference_count(bug);}
    larva_block->bug = bug;
  }
  return larva_f2ptr;
}

f2ptr pfunk2__f2larva__new(f2ptr cause, u32 larva_type, f2ptr bug) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2larva__new(pool_index, cause, larva_type, bug);
  return retval;
}

u32 pfunk2__f2larva__larva_type(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_larva) {
    ptype_error(cause, this, __funk2.globalenv.ptype_larva__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u32 type = __pure__f2larva__larva_type(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(type));
  return type;
}

f2ptr pfunk2__f2larva__bug(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_larva) {
    ptype_error(cause, this, __funk2.globalenv.ptype_larva__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr bug = __pure__f2larva__bug(this);
  container__reflectively_know_of_reading_from(cause, this, bug, sizeof(bug));
  return bug;
}




// mutable_array_pointer

f2ptr ptype_mutable_array_pointer__new(int pool_index, f2ptr cause, f2ptr array, u64 index) {
  f2ptr mutable_array_pointer_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_mutable_array_pointer_block_t));
  ptype_mutable_array_pointer_block_t* mutable_array_pointer_block = (ptype_mutable_array_pointer_block_t*)from_ptr(raw__f2ptr_to_ptr(mutable_array_pointer_f2ptr));
  debug__assert(mutable_array_pointer_block, nil, "block is nil.");
  mutable_array_pointer_block->ptype.block.ptype    = ptype_mutable_array_pointer;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    mutable_array_pointer_block->ptype.cause = cause;
  } else {
    mutable_array_pointer_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    mutable_array_pointer_block->ptype.creation_fiber = creation_fiber;
  } else {
    mutable_array_pointer_block->ptype.creation_fiber = nil;
  }
  {
    if (array) {raw__exp__increment_reference_count(array);}
    mutable_array_pointer_block->array = array;
  }
  mutable_array_pointer_block->index = index;
  return mutable_array_pointer_f2ptr;
}

f2ptr pfunk2__f2mutable_array_pointer__new(f2ptr cause, f2ptr array, u64 index) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2mutable_array_pointer__new(pool_index, cause, array, index);
  return retval;
}

f2ptr pfunk2__f2mutable_array_pointer__array(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutable_array_pointer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutable_array_pointer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr array = __pure__f2mutable_array_pointer__array(this);
  container__reflectively_know_of_reading_from(cause, this, array, sizeof(array));
  return array;
}

void pfunk2__f2mutable_array_pointer__array__set(f2ptr this, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutable_array_pointer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutable_array_pointer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  
  {
    f2ptr old_value = __pure__f2mutable_array_pointer__array(this);
    funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
    __pure__f2mutable_array_pointer__array__set(this, value);
  }  
  
  container__reflectively_know_of_writing_to(cause, this, value, sizeof(value));
}

u64 pfunk2__f2mutable_array_pointer__index(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutable_array_pointer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutable_array_pointer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 index = __pure__f2mutable_array_pointer__index(this);
  container__reflectively_know_of_reading_from(cause, this, nil, sizeof(index));
  return index;
}

void pfunk2__f2mutable_array_pointer__index__set(f2ptr this, f2ptr cause, u64 index) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutable_array_pointer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutable_array_pointer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2mutable_array_pointer__index__set(this, index);
  container__reflectively_know_of_writing_to(cause, this, nil, sizeof(index));
}




// symbol_hash

void funk2_symbol_hash__init(funk2_symbol_hash_t* this) {
  funk2_processor_mutex__init(&(this->cmutex));
  this->array               = (funk2_symbol_hash_node_t**)from_ptr(f2__malloc(sizeof(funk2_symbol_hash_node_t*) * SYMBOL_HASH__INITIAL_ARRAY_LENGTH));
  memset(this->array, 0, sizeof(funk2_symbol_hash_node_t*) * SYMBOL_HASH__INITIAL_ARRAY_LENGTH);
  this->total_symbol_num    = 0;
  this->eq_hash_value_bit_mask = SYMBOL_HASH__INITIAL_ARRAY_LENGTH - 1; // assumes SYMBOL_HASH__INITIAL_ARRAY_LENGTH is power of 2
  this->array_length        = SYMBOL_HASH__INITIAL_ARRAY_LENGTH;
}

void funk2_symbol_hash__destroy(funk2_symbol_hash_t* this) {
  {
    funk2_symbol_hash_node_t** array_iter = this->array;
    funk2_symbol_hash_node_t*  node_iter;
    int i;
    for (i = this->array_length; i > 0; i --) {
      node_iter = *array_iter;
      while (node_iter) {
	funk2_symbol_hash_node_t* next = node_iter->next;
	f2__free(to_ptr(node_iter));
	node_iter = next;
      }
      array_iter ++;
    }
  }
  f2__free(to_ptr(this->array));
}

void funk2_symbol_hash__reinit(funk2_symbol_hash_t* this) {
  funk2_symbol_hash__destroy(this);
  funk2_symbol_hash__init(this);
}

void funk2_symbol_hash__add_symbol(funk2_symbol_hash_t* this, f2ptr symbol_f2ptr) {
  ptype_symbol_block_t*     symbol_block = (ptype_symbol_block_t*)from_ptr(f2ptr_to_ptr(symbol_f2ptr));
  u64                       bin_index    = symbol_block->eq_hash_value & (this->eq_hash_value_bit_mask);
  funk2_symbol_hash_node_t* new_node     = (funk2_symbol_hash_node_t*)from_ptr(f2__malloc(sizeof(funk2_symbol_hash_node_t)));
  new_node->symbol = symbol_f2ptr;
  new_node->next = this->array[bin_index];
  this->array[bin_index] = new_node;
}

f2ptr funk2_symbol_hash__lookup_symbol__thread_unsafe(funk2_symbol_hash_t* this, u64 length, funk2_character_t* str) {
  ptype_symbol_block_t* symbol_block = NULL;
  // search for chararray in hashed symbols
  u64 bin_index = (u64)((u64)character_array__hash_value(length, str) & (u64)(this->eq_hash_value_bit_mask));
  funk2_symbol_hash_node_t* node = (this->array[bin_index]);
  while (node) {
    symbol_block = (ptype_symbol_block_t*)from_ptr(f2ptr_to_ptr(node->symbol));
    //if we find a symbol that matches chararray, return it.
    debug__assert(symbol_block->ptype.block.used, nil, "funk2_symbol_hash__lookup_symbol error: found unused symbol.");
    if (symbol_block->length == length && (! memcmp(symbol_block->str, str, length * sizeof(funk2_character_t)))) {
      funk2_processor_mutex__unlock(&(this->cmutex));
      return node->symbol;
    }
    node = node->next;
  }
  return nil;
}

f2ptr funk2_symbol_hash__lookup_symbol(funk2_symbol_hash_t* this, u64 length, funk2_character_t* str) {
  funk2_processor_mutex__user_lock(&this->cmutex);
  f2ptr result = funk2_symbol_hash__lookup_symbol__thread_unsafe(this, length, str);
  funk2_processor_mutex__unlock(&(this->cmutex));
  return result;
}

f2ptr funk2_symbol_hash__lookup_or_create_symbol__thread_unsafe(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, u64 length, funk2_character_t* str) {
  f2ptr symbol_f2ptr = funk2_symbol_hash__lookup_symbol__thread_unsafe(this, length, str);
  if (symbol_f2ptr) {
    return symbol_f2ptr;
  }
  
  // otherwise, create a new symbol
  symbol_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_symbol_block_t) + (length * sizeof(funk2_character_t)));
  ptype_symbol_block_t* symbol_block = (ptype_symbol_block_t*)from_ptr(raw__f2ptr_to_ptr(symbol_f2ptr));
  debug__assert(symbol_block, nil, "block is nil.");
  symbol_block->ptype.block.ptype    = ptype_symbol;
  if (__ptypes__creation_cause_enabled) {
    if (cause) {raw__exp__increment_reference_count(cause);}
    symbol_block->ptype.cause = cause;
  } else {
    symbol_block->ptype.cause = nil;
  }
  if (__ptypes__creation_fiber_enabled) {
    f2ptr creation_fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(this_processor_thread__pool_index());
    if (creation_fiber != nil) {raw__exp__increment_reference_count(creation_fiber);}
    symbol_block->ptype.creation_fiber = creation_fiber;
  } else {
    symbol_block->ptype.creation_fiber = nil;
  }
  symbol_block->length               = length;
  if (str) {memcpy(symbol_block->str, str, length * sizeof(funk2_character_t));}
  else     {memset(symbol_block->str, 0,   length * sizeof(funk2_character_t));}
  symbol_block->eq_hash_value  = (u64)((u64)character_array__hash_value(length, str));
  
  // and add new symbol to hash table
  funk2_symbol_hash__add_symbol(this, symbol_f2ptr);
  return symbol_f2ptr;
}

f2ptr funk2_symbol_hash__lookup_or_create_symbol(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, u64 length, funk2_character_t* str) {
  funk2_processor_mutex__user_lock(&this->cmutex);
  f2ptr result = funk2_symbol_hash__lookup_or_create_symbol__thread_unsafe(this, pool_index, cause, length, str);
  funk2_processor_mutex__unlock(&(this->cmutex));
  return result;
}

#define gensym__length 11
f2ptr funk2_symbol_hash__generate_new_random_symbol__thread_unsafe(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, s64 initial_string_length, funk2_character_t* initial_string) {
  s64 total_gensym_length = initial_string_length + gensym__length;
  funk2_character_t* gensym__name = (funk2_character_t*)from_ptr(f2__malloc((total_gensym_length + 1) * sizeof(funk2_character_t)));
  {
    int index;
    for (index = 0; index < initial_string_length; index ++) {
      gensym__name[index] = initial_string[index];
    }
  }
  gensym__name[initial_string_length + 0] = (funk2_character_t)'-';
  f2ptr symbol_exists;
  do {
    int index;
    for (index = 0; index < gensym__length - 1; index ++) {
      int random_num = random() % (10 + 26);
      if (random_num < 10) {
	gensym__name[initial_string_length + index + 1] = ((funk2_character_t)'0') + random_num;
      } else {
	gensym__name[initial_string_length + index + 1] = ((funk2_character_t)'a') + (random_num - 10);
      }
    }
    symbol_exists = funk2_symbol_hash__lookup_symbol__thread_unsafe(this, total_gensym_length, gensym__name);
  } while (symbol_exists);
  f2ptr new_symbol = funk2_symbol_hash__lookup_or_create_symbol__thread_unsafe(this, pool_index, cause, total_gensym_length, gensym__name);
  return new_symbol;
}

f2ptr funk2_symbol_hash__generate_new_random_symbol(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, s64 initial_string_length, funk2_character_t* initial_string) {
  funk2_processor_mutex__user_lock(&this->cmutex);
  f2ptr new_symbol = funk2_symbol_hash__generate_new_random_symbol__thread_unsafe(this, pool_index, cause, initial_string_length, initial_string);
  funk2_processor_mutex__unlock(&(this->cmutex));
  return new_symbol;
}



void funk2_symbol_hash__touch_all_symbols(funk2_symbol_hash_t* this, funk2_garbage_collector_t* garbage_collector) {
  garbage_collector_status("funk2_garbage_collector: touch_all_symbols.");
  funk2_symbol_hash_node_t** array_iter = this->array;
  funk2_symbol_hash_node_t*  node_iter;
  int i;
  for (i = this->array_length; i > 0; i --) {
    for (node_iter = array_iter[0]; node_iter; node_iter = node_iter->next) {
      funk2_garbage_collector__touch_f2ptr(garbage_collector, node_iter->symbol);
    }
    array_iter ++;
  }
}

// 2^64 = 18, 446,744,073,709,551,616
//   or = 18  sextillion


void funk2_symbol_hash__defragment__fix_pointers(funk2_symbol_hash_t* this) {
  funk2_symbol_hash__reinit(this);
  
  {
    s64 pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      {
	funk2_memblock_t* iter          = funk2_memorypool__beginning_of_blocks(&(__funk2.memory.pool[pool_index]));
	funk2_memblock_t* end_of_blocks = funk2_memorypool__end_of_blocks(&(__funk2.memory.pool[pool_index]));
	while(iter < end_of_blocks) {
	  if (iter->used) {
	    ptype_block_t* block = (ptype_block_t*)iter;
	    switch(block->block.ptype) {
	    case ptype_symbol: {
	      f2ptr block_f2ptr = funk2_memory__ptr_to_f2ptr__slow(&(__funk2.memory), to_ptr(block));
	      funk2_symbol_hash__add_symbol(this, block_f2ptr);
	    } break;
	    default:
	      break;
	    }
	  }
	  iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
	}
	release__assert(iter == end_of_blocks, nil, "memory_test: (end_of_blocks != iter) failure.");
      }
    }
  }
}

// ptypes

void funk2_ptypes__init(funk2_ptypes_t* this) {
  this->read_write_reflective_tracing_enabled = boolean__false;
  funk2_symbol_hash__init(&(this->symbol_hash));
}

void funk2_ptypes__defragment__fix_pointers(funk2_ptypes_t* this) {
  funk2_symbol_hash__defragment__fix_pointers(&(this->symbol_hash));
}

void funk2_ptypes__destroy(funk2_ptypes_t* this) {
  funk2_symbol_hash__destroy(&(this->symbol_hash));
}


// **

void f2__ptypes__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  funk2_ptypes__defragment__fix_pointers(&(__funk2.ptypes));
  
}

// initialize ptypes

void f2__ptypes__reinitialize_globalvars() {
}

void f2__ptypes__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "ptypes", "", &f2__ptypes__reinitialize_globalvars, &f2__ptypes__defragment__fix_pointers);
  
  funk2_ptypes__init(&(__funk2.ptypes));
}

void f2__ptypes__destroy() {
  funk2_ptypes__destroy(&(__funk2.ptypes));
}

