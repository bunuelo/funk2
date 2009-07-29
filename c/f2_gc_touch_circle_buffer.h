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

#ifndef F2__GC_TOUCH_CIRCLE_BUFFER__H
#define F2__GC_TOUCH_CIRCLE_BUFFER__H

#include "f2_memblock.h"

typedef struct funk2_gc_touch_circle_buffer_s {
  s64                length;
  funk2_memblock_t** data;
  s64                start_index;
  s64                end_index;
} funk2_gc_touch_circle_buffer_t;

#define funk2_gc_touch_circle_buffer__touch_f2ptr(this, exp)                     funk2_gc_touch_circle_buffer__touch_block(this, (funk2_memblock_t*)(from_ptr(__f2ptr_to_ptr(exp))))
#define funk2_gc_touch_circle_buffer__touch_all_referenced_from_f2ptr(this, exp) funk2_gc_touch_circle_buffer__touch_all_referenced_from_block(this, (funk2_memblock_t*)(from_ptr(__f2ptr_to_ptr(exp))))

void              funk2_gc_touch_circle_buffer__init(funk2_gc_touch_circle_buffer_t* this);
void              funk2_gc_touch_circle_buffer__destroy(funk2_gc_touch_circle_buffer_t* this);
void              funk2_gc_touch_circle_buffer__empty(funk2_gc_touch_circle_buffer_t* this);
boolean_t         funk2_gc_touch_circle_buffer__is_empty(funk2_gc_touch_circle_buffer_t* this);
void              funk2_gc_touch_circle_buffer__add_block(funk2_gc_touch_circle_buffer_t* this, funk2_memblock_t* block);
funk2_memblock_t* funk2_gc_touch_circle_buffer__pop_block(funk2_gc_touch_circle_buffer_t* this);
void              funk2_gc_touch_circle_buffer__touch_block(funk2_gc_touch_circle_buffer_t* this, funk2_memblock_t* block);
void              funk2_gc_touch_circle_buffer__touch_dptr(funk2_gc_touch_circle_buffer_t* this, dptr_t* dptr);
void              funk2_gc_touch_circle_buffer__touch_all_referenced_from_block(funk2_gc_touch_circle_buffer_t* this, funk2_memblock_t* start_block);

void funk2_gc_touch_circle_buffer__test();

/*
typedef struct funk2_gc_touch_circle_buffer_s {
  s64                num;
  funk2_memblock_t** start;
  funk2_memblock_t** end;
  funk2_memblock_t** start_index;
  funk2_memblock_t** end_index;
} funk2_gc_touch_circle_buffer_t;
*/

// funk2_gc_touch_circle_buffer

//void funk2_gc_touch_circle_buffer__init(funk2_gc_touch_circle_buffer_t* this);
//void funk2_gc_touch_circle_buffer__destroy(funk2_gc_touch_circle_buffer_t* this);
//void funk2_gc_touch_circle_buffer__print(funk2_gc_touch_circle_buffer_t* this, char* message);
//void funk2_gc_touch_circle_buffer__advance_end(funk2_gc_touch_circle_buffer_t* this);
//void funk2_gc_touch_circle_buffer__advance_start_index(funk2_gc_touch_circle_buffer_t* this);
//void funk2_gc_touch_circle_buffer__touch_f2ptr(funk2_gc_touch_circle_buffer_t* this, f2ptr block_f2ptr);
//void funk2_gc_touch_circle_buffer__touch_dptr(funk2_gc_touch_circle_buffer_t* this, dptr_t* dptr);
//void funk2_gc_touch_circle_buffer__touch_all_referenced_from_block(funk2_gc_touch_circle_buffer_t* this, ptr start_block_ptr);
//void funk2_gc_touch_circle_buffer__touch_all_referenced_from_f2ptr(funk2_gc_touch_circle_buffer_t* this, f2ptr exp);

#endif // F2__GC_TOUCH_CIRCLE_BUFFER__H
