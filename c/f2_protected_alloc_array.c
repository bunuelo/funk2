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
  this->length   = 1024 * 1024;
  this->data = (f2ptr*)from_ptr(f2__malloc(sizeof(f2ptr) * this->length));
  u64 i;
  for (i = 0; i < this->length; i ++) {
    this->data[i] = nil;
  }
  this->reentrance_count     = 0;
  this->max_reentrance_count = 0;
  funk2_protected_alloc_array_event_array__init(&(this->event_array));
}

void funk2_protected_alloc_array__destroy(funk2_protected_alloc_array_t* this) {
  free(this->data);
  funk2_protected_alloc_array_event_array__destroy(&(this->event_array));
}

void funk2_protected_alloc_array__add_protected_alloc_f2ptr(funk2_protected_alloc_array_t* this, f2ptr exp) {
  this->data[this->used_num] = exp;
  this->used_num ++;
  if (this->used_num >= this->length) {
    u64 old_length = this->length;
    this->length <<= 1;
    status("funk2_protected_alloc_array__add_protected_alloc_f2ptr: doubling size of protected_alloc_array from " u64__fstr " to " u64__fstr " f2ptrs.", old_length, this->length);
    this->data = from_ptr(f2__new_alloc(to_ptr(this->data), sizeof(f2ptr) * old_length, sizeof(f2ptr) * this->length));
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
  return (this->reentrance_count > 0);
}

s64 funk2_protected_alloc_array__calculate_save_size(funk2_protected_alloc_array_t* this) {
  s64 save_size = 0;
  {
    u64 used_num = this->used_num;
    save_size += sizeof(used_num);
    save_size += (sizeof(f2ptr) * used_num);
  }
  return save_size;
}

void funk2_protected_alloc_array__save_to_stream(funk2_protected_alloc_array_t* this, int fd) {
  u64 used_num = this->used_num;
  safe_write(fd, to_ptr(&used_num), sizeof(used_num));
  f2ptr* write_buffer = (f2ptr*)from_ptr(f2__malloc(sizeof(f2ptr) * used_num));
  {
    u64 index;
    for (index = 0; index < used_num; index ++) {
      f2ptr exp = this->data[index];
      write_buffer[index] = exp;
    }
  }
  safe_write(fd, to_ptr(write_buffer), sizeof(f2ptr) * used_num);
  f2__free(to_ptr(write_buffer));
}

void funk2_protected_alloc_array__load_from_stream(funk2_protected_alloc_array_t* this, int fd) {
  u64 used_num;
  safe_read(fd, to_ptr(&used_num), sizeof(used_num));
  f2ptr* read_buffer = (f2ptr*)from_ptr(f2__malloc(sizeof(f2ptr) * used_num));
  safe_read(fd, to_ptr(read_buffer), sizeof(f2ptr) * used_num);
  {
    u64 index;
    for (index = 0; index < used_num; index ++) {
      f2ptr exp = read_buffer[index];
      funk2_protected_alloc_array__add_protected_alloc_f2ptr(this, exp);
    }
  }
  f2__free(to_ptr(read_buffer));
}

