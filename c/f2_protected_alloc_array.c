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

// protected_alloc_array_event_array

void funk2_protected_alloc_array_event_array__init(funk2_protected_alloc_array_event_array_t* this) {
  this->used_num = 0;
  this->length   = 1024 * 1024;
  this->data     = (funk2_protected_alloc_array_event_t*)from_ptr(f2__malloc(sizeof(funk2_protected_alloc_array_event_t) * this->length));
}

void funk2_protected_alloc_array_event_array__destroy(funk2_protected_alloc_array_event_array_t* this) {
  free(this->data);
}

void funk2_protected_alloc_array_event_array__add_event(funk2_protected_alloc_array_event_array_t* this, funk2_protected_alloc_array_event_type_t type, char* source_filename, int source_line_num) {
  this->data[this->used_num].type            = type;
  this->data[this->used_num].source_filename = source_filename;
  this->data[this->used_num].source_line_num = source_line_num;
  this->used_num ++;
  if (this->used_num >= this->length) {
    u64 old_length = this->length;
    this->length <<= 1;
    status("funk2_protected_alloc_array_event_array__add_event: doubling size of event_array from " u64__fstr " to " u64__fstr " events.", old_length, this->length);
    this->data = from_ptr(f2__new_alloc(to_ptr(this->data), sizeof(funk2_protected_alloc_array_event_t) * old_length, sizeof(funk2_protected_alloc_array_event_t) * this->length));
  }
}

void funk2_protected_alloc_array_event_array__reset(funk2_protected_alloc_array_event_array_t* this) {
  this->used_num = 0;
}


// funk2_protected_alloc_array

void funk2_protected_alloc_array__init(funk2_protected_alloc_array_t* this) {
  this->used_num = 0;
  this->length   = 2ull * 1024;
  this->data = (f2ptr_t*)from_ptr(f2__malloc(sizeof(f2ptr_t) * this->length));
  u64 i;
  for (i = 0; i < this->length; i ++) {
    this->data[i].data = nil;
  }
  this->reentrance_count     = 0;
  this->max_reentrance_count = 0;
#ifdef F2__DEBUG__PROTECTED_ALLOC_ARRAY
  funk2_protected_alloc_array_event_array__init(&(this->event_array));
#endif // F2__DEBUG__PROTECTED_ALLOC_ARRAY
}

void funk2_protected_alloc_array__destroy(funk2_protected_alloc_array_t* this) {
  free(this->data);
#ifdef F2__DEBUG__PROTECTED_ALLOC_ARRAY
  funk2_protected_alloc_array_event_array__destroy(&(this->event_array));
#endif // F2__DEBUG__PROTECTED_ALLOC_ARRAY
}

void funk2_protected_alloc_array__add_protected_alloc_f2ptr(funk2_protected_alloc_array_t* this, f2ptr exp) {
  if (this->reentrance_count == 0) {
    return;
  }
  this->data[this->used_num].data = exp;
  this->used_num ++;
  if (this->used_num >= this->length) {
    u64 old_length          = this->length;
    u64 old_length__bit_num = u64__bit_num(old_length);
    u64 new_length__bit_num = ((old_length__bit_num * 9) >> 3) + 1;
    this->length = (1ll << new_length__bit_num);
    status("funk2_protected_alloc_array__add_protected_alloc_f2ptr: increasing size of protected_alloc_array from " u64__fstr " to " u64__fstr " f2ptrs.", old_length, this->length);
    this->data = (f2ptr_t*)from_ptr(f2__new_alloc(to_ptr(this->data), sizeof(f2ptr_t) * old_length, sizeof(f2ptr_t) * this->length));
  }
}

void found_max_reentrance(u64 max_reentrance_count) {
  status("found max reentrace count: " u64__fstr, max_reentrance_count);
}

void funk2_protected_alloc_array__signal_enter_protected_region(funk2_protected_alloc_array_t* this, char* source_filename, int source_line_num) {
#ifdef F2__DEBUG__PROTECTED_ALLOC_ARRAY
  funk2_protected_alloc_array_event_array__add_event(&(this->event_array), funk2_protected_alloc_array_event_type__enter, source_filename, source_line_num);
#endif // F2__DEBUG__PROTECTED_ALLOC_ARRAY
  this->reentrance_count ++;
  if (this->reentrance_count > this->max_reentrance_count) {
    this->max_reentrance_count = this->reentrance_count;
    found_max_reentrance(this->max_reentrance_count);
  }
}

void funk2_protected_alloc_array__signal_exit_protected_region(funk2_protected_alloc_array_t* this, char* source_filename, int source_line_num) {
#ifdef F2__DEBUG__PROTECTED_ALLOC_ARRAY
  funk2_protected_alloc_array_event_array__add_event(&(this->event_array), funk2_protected_alloc_array_event_type__exit, source_filename, source_line_num);
#endif // F2__DEBUG__PROTECTED_ALLOC_ARRAY
  if (this->reentrance_count == 0) {
    error(nil, "funk2_protected_alloc_array__signal_exit_protected_region error: bytecode reentrance underflow.");
  }
  this->reentrance_count --;
  if (this->reentrance_count == 0) {
    // protected counter is back to zero so reset used_num to zero.
    this->used_num = 0;
#ifdef F2__DEBUG__PROTECTED_ALLOC_ARRAY
    funk2_protected_alloc_array_event_array__reset(&(this->event_array));
#endif // F2__DEBUG__PROTECTED_ALLOC_ARRAY
  }
  
#ifdef F2__DEBUG__PROTECTED_ALLOC_ARRAY
  if (this->reentrance_count < 0) {
    error(nil, "funk2_protected_alloc_array__signal_exit_protected_region error: this->reentrace_count < 0.");
  }
#endif // F2__DEBUG__PROTECTED_ALLOC_ARRAY

}

boolean_t funk2_protected_alloc_array__in_protected_region(funk2_protected_alloc_array_t* this) {
  return (this->reentrance_count != 0);
}

void funk2_protected_alloc_array__touch_all(funk2_protected_alloc_array_t* this, funk2_garbage_collector_pool_t* garbage_collector_pool) {
  u64 i;
  for (i = 0; i < this->used_num; i ++) {
    funk2_garbage_collector_pool__touch_f2ptr(garbage_collector_pool, this->data[i].data);
  }
}

void funk2_protected_alloc_array__defragment__fix_pointers(funk2_protected_alloc_array_t* this) {
  u64 index;
  for (index = 0; index < this->used_num; index ++) {
    defragment__fix_pointer(this->data[index].data);
  }
}


// funk2_protected_alloc_array_fiber_hash

void funk2_protected_alloc_array_fiber_hash__init(funk2_protected_alloc_array_fiber_hash_t* this) {
  funk2_hash__init(&(this->used_fiber_hash), 10);
  this->extra_array_buffer__count = 0;
}

void funk2_protected_alloc_array_fiber_hash__destroy(funk2_protected_alloc_array_fiber_hash_t* this) {
  funk2_hash__destroy(&(this->used_fiber_hash));
  {
    u64 index;
    for (index = 0; index < this->extra_array_buffer__count; index ++) {
      funk2_protected_alloc_array_t* protected_alloc_array = this->extra_array_buffer[index];
      funk2_protected_alloc_array__destroy(protected_alloc_array);
      f2__free(to_ptr(protected_alloc_array));
    }
  }
}

funk2_protected_alloc_array_t* funk2_protected_alloc_array_fiber_hash__allocate_and_init_protected_alloc_array(funk2_protected_alloc_array_fiber_hash_t* this) {
  funk2_protected_alloc_array_t* protected_alloc_array;
  if (this->extra_array_buffer__count > 0) {
    this->extra_array_buffer__count --;
    protected_alloc_array = this->extra_array_buffer[this->extra_array_buffer__count];
  } else {
    protected_alloc_array = from_ptr(f2__malloc(sizeof(funk2_protected_alloc_array_t)));
    funk2_protected_alloc_array__init(protected_alloc_array);
  }
  return protected_alloc_array;
}

void funk2_protected_alloc_array_fiber_hash__destroy_and_deallocate_protected_alloc_array(funk2_protected_alloc_array_fiber_hash_t* this, funk2_protected_alloc_array_t* protected_alloc_array) {
  if (this->extra_array_buffer__count < funk2_protected_alloc_array_fiber_hash__extra_array_buffer__max_num) {
    this->extra_array_buffer[this->extra_array_buffer__count] = protected_alloc_array;
    this->extra_array_buffer__count ++;
  } else {
    funk2_protected_alloc_array__destroy(protected_alloc_array);
    f2__free(to_ptr(protected_alloc_array));
  }
}

funk2_protected_alloc_array_t* funk2_protected_alloc_array_fiber_hash__try_lookup_protected_alloc_array(funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber) {
  return (funk2_protected_alloc_array_t*)from_ptr(funk2_hash__try_lookup(&(this->used_fiber_hash), fiber, (u64)NULL));
}

funk2_protected_alloc_array_t* funk2_protected_alloc_array_fiber_hash__lookup_protected_alloc_array(funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber) {
  funk2_protected_alloc_array_t* protected_alloc_array = funk2_protected_alloc_array_fiber_hash__try_lookup_protected_alloc_array(this, fiber);
  if (protected_alloc_array == NULL) {
    protected_alloc_array = funk2_protected_alloc_array_fiber_hash__allocate_and_init_protected_alloc_array(this);
    funk2_hash__add(&(this->used_fiber_hash), fiber, to_ptr(protected_alloc_array));
  }
  return protected_alloc_array;
}

void funk2_protected_alloc_array_fiber_hash__remove_protected_alloc_array(funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber) {
  funk2_protected_alloc_array_t* protected_alloc_array = funk2_protected_alloc_array_fiber_hash__try_lookup_protected_alloc_array(this, fiber);
  if (protected_alloc_array == NULL) {
    error(nil, "funk2_protected_alloc_array_fiber_hash__remove_protected_alloc_array fatal error: protected_alloc_array == NULL.");
  }
  funk2_hash__remove(&(this->used_fiber_hash), fiber);
  funk2_protected_alloc_array_fiber_hash__destroy_and_deallocate_protected_alloc_array(this, protected_alloc_array);
}

void funk2_protected_alloc_array_fiber_hash__add_protected_alloc_f2ptr(funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber, f2ptr exp) {
  funk2_protected_alloc_array_t* protected_alloc_array = funk2_protected_alloc_array_fiber_hash__lookup_protected_alloc_array(this, fiber);
  funk2_protected_alloc_array__add_protected_alloc_f2ptr(protected_alloc_array, exp);
}

void funk2_protected_alloc_array_fiber_hash__signal_enter_protected_region(funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber, char* source_filename, int source_line_num) {
  funk2_protected_alloc_array_t* protected_alloc_array = funk2_protected_alloc_array_fiber_hash__lookup_protected_alloc_array(this, fiber);
  funk2_protected_alloc_array__signal_enter_protected_region(protected_alloc_array, source_filename, source_line_num);
}

void funk2_protected_alloc_array_fiber_hash__signal_exit_protected_region(funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber, char* source_filename, int source_line_num) {
  funk2_protected_alloc_array_t* protected_alloc_array = funk2_protected_alloc_array_fiber_hash__lookup_protected_alloc_array(this, fiber);
  funk2_protected_alloc_array__signal_exit_protected_region(protected_alloc_array, source_filename, source_line_num);
  if (! funk2_protected_alloc_array__in_protected_region(protected_alloc_array)) {
    funk2_protected_alloc_array_fiber_hash__remove_protected_alloc_array(this, fiber);
  }
}

boolean_t funk2_protected_alloc_array_fiber_hash__in_protected_region(funk2_protected_alloc_array_fiber_hash_t* this, f2ptr fiber) {
  funk2_protected_alloc_array_t* protected_alloc_array = funk2_protected_alloc_array_fiber_hash__try_lookup_protected_alloc_array(this, fiber);
  if (protected_alloc_array == NULL) {
    return boolean__false;
  }
  return funk2_protected_alloc_array__in_protected_region(protected_alloc_array);
}


void funk2_protected_alloc_array_fiber_hash__touch_all(funk2_protected_alloc_array_fiber_hash_t* this, funk2_garbage_collector_pool_t* garbage_collector_pool) {
#if defined(DEBUG_GARBAGE_COLLECTOR_STATUS)
  funk2_hash__iteration(&(this->used_fiber_hash), key, value,
			funk2_protected_alloc_array_t* protected_alloc_array = (funk2_protected_alloc_array_t*)from_ptr(value);
			f2ptr                          fiber                 = key;
			garbage_collector_status("funk2_protected_alloc_array_fiber_hash: touch_all.  pool_index=" u64__fstr " fiber=" f2ptr__fstr " used_num=" u64__fstr " reentrance_count=" s64__fstr,
						 this_processor_thread__pool_index(),
						 fiber,
						 protected_alloc_array->used_num,
						 protected_alloc_array->reentrance_count);
			funk2_protected_alloc_array__touch_all(protected_alloc_array, garbage_collector_pool);
			);
#else
  funk2_hash__value__iteration(&(this->used_fiber_hash), value,
			       funk2_protected_alloc_array_t* protected_alloc_array = (funk2_protected_alloc_array_t*)from_ptr(value);
			       funk2_protected_alloc_array__touch_all(protected_alloc_array, garbage_collector_pool);
			       );
#endif
}

void funk2_protected_alloc_array_fiber_hash__defragment__fix_pointers(funk2_protected_alloc_array_fiber_hash_t* this) {
  {
    u64                             used_fiber_hash__key_count                   = this->used_fiber_hash.key_count;
    f2ptr*                          used_fiber_hash__fiber_array                 = (f2ptr*)from_ptr(f2__malloc(sizeof(f2ptr) * used_fiber_hash__key_count));
    funk2_protected_alloc_array_t** used_fiber_hash__protected_alloc_array_array = (funk2_protected_alloc_array_t**)from_ptr(f2__malloc(sizeof(funk2_protected_alloc_array_t*) * used_fiber_hash__key_count));
    {
      u64 index = 0;
      funk2_hash__iteration(&(this->used_fiber_hash), key, value,
			    f2ptr                          fiber                 = key;
			    funk2_protected_alloc_array_t* protected_alloc_array = (funk2_protected_alloc_array_t*)from_ptr(value);
			    {
			      used_fiber_hash__fiber_array[index]                 = fiber;
			      used_fiber_hash__protected_alloc_array_array[index] = protected_alloc_array;
			    }
			    index ++;
			    );
    }
    {
      u64 index;
      for (index = 0; index < used_fiber_hash__key_count; index ++) {
	f2ptr fiber = used_fiber_hash__fiber_array[index];
	funk2_hash__remove(&(this->used_fiber_hash), (u64)fiber);
      }
    }
    {
      u64 index;
      for (index = 0; index < used_fiber_hash__key_count; index ++) {
	f2ptr                          fiber                 = used_fiber_hash__fiber_array[index];
	funk2_protected_alloc_array_t* protected_alloc_array = used_fiber_hash__protected_alloc_array_array[index];
	defragment__fix_pointer(fiber);
	funk2_protected_alloc_array__defragment__fix_pointers(protected_alloc_array);
	funk2_hash__add(&(this->used_fiber_hash), (u64)fiber, (u64)to_ptr(protected_alloc_array));
      }
    }
    f2__free(to_ptr(used_fiber_hash__fiber_array));
    f2__free(to_ptr(used_fiber_hash__protected_alloc_array_array));
  }
  {
    u64 index;
    for (index = 0; index < this->extra_array_buffer__count; index ++) {
      funk2_protected_alloc_array_t* extra_array_buffer = this->extra_array_buffer[index];
      funk2_protected_alloc_array__defragment__fix_pointers(extra_array_buffer);
    }
  }
}

