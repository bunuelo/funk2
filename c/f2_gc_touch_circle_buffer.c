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

// funk2_gc_touch_circle_buffer

void funk2_gc_touch_circle_buffer__init(funk2_gc_touch_circle_buffer_t* this) {
  this->num         = GC_TOUCH_CIRCLE_BUF_START_SIZE;
  this->start       = (funk2_memblock_t**)from_ptr(f2__malloc(GC_TOUCH_CIRCLE_BUF_START_SIZE * sizeof(funk2_memblock_t*)));
  this->end         = this->start + GC_TOUCH_CIRCLE_BUF_START_SIZE;  
  this->start_index = NULL;
  this->end_index   = NULL;
}

void funk2_gc_touch_circle_buffer__destroy(funk2_gc_touch_circle_buffer_t* this) {
  free(this->start);
}

void funk2_gc_touch_circle_buffer__print(funk2_gc_touch_circle_buffer_t* this, char* message) {
  ptr* iter = (ptr*)this->start;
  printf("\n%16s: {", message);
  for(; iter < (ptr*)this->end; iter++) {
    if (iter == (ptr*)this->start_index) {
      printf(" *S*");
    }
    if (iter == (ptr*)this->end_index) {
      printf(" *E*");
    }
    printf(" %lx", (long)*iter);
    fflush(stdout);
  }
  printf("}\n");
  fflush(stdout);
}

void funk2_gc_touch_circle_buffer__advance_end(funk2_gc_touch_circle_buffer_t* this) {
  this->end_index ++;
  if (this->end_index == this->end) {
    this->end_index = this->start;
  }
  if (this->end_index == this->start_index) {
    //funk2_gc_touch_circle_buffer__print(this, "buffer");
    //printf("\nincreasing buffer."); fflush(stdout);
    //printf("\n  start = %lx.", (int)(this->start_index - this->start)); fflush(stdout);
    //printf("\n  end   = %lx.", (int)(this->end_index   - this->start)); fflush(stdout);
    //funk2_gc_touch_circle_buffer__print(this, "debug 0");
    // increasing size by two makes a lot of these memory moves conveniently easy.
    int old_num = this->num;
    this->num = old_num << 1;
    //printf("\n__gc_touch_circle_buffer.start = %x", (int)this->start);
    funk2_memblock_t** new_location = (funk2_memblock_t**)from_ptr(f2__new_alloc(to_ptr(this->start), sizeof(funk2_memblock_t*) * old_num, sizeof(funk2_memblock_t*) * this->num));
    //printf("\nnew_location = %lx", (int)new_location); fflush(stdout);
    int location_diff = new_location - this->start;
    this->start = new_location;
    
    this->start_index += location_diff;
    this->end_index   += location_diff;
    
    this->end = this->start + this->num;
    //printf("\n  copying %d bytes ((u8*)__circle_buf_end_index) - ((u8*)__gc_touch_circle_buffer.start).", ((u8*)__circle_buf_end_index) - ((u8*)__gc_touch_circle_buffer.start));
    //printf("\n  sizeof(funk2_memblock_t**) = %d bytes.", sizeof(funk2_memblock_t**));
    //printf("\n  old_num = %d", old_num);
    //funk2_gc_touch_circle_buffer__print(this, "just before copy");
    memcpy(this->start + old_num, this->start, ((u8*)this->end_index) - ((u8*)this->start));
    //funk2_gc_touch_circle_buffer__print(this, "just after copy");
    this->end_index += old_num;
    //printf("\ncircle_buffer size increased to %d.", this->num); fflush(stdout);
    //printf("\n  start = %lx.", (int)(this->circle_buf_start_index - this->start)); fflush(stdout);
    //printf("\n  end   = %lx.", (int)(this->circle_buf_end_index   - this->start)); fflush(stdout);
    //funk2_gc_touch_circle_buffer__print(this, "after all");
  }
}

void funk2_gc_touch_circle_buffer__advance_start_index(funk2_gc_touch_circle_buffer_t* this) {
  //printf("\nadvance start."); fflush(stdout);
  //printf("\n  start = %x.", (int)(this->circle_buf_start_index - this->start)); fflush(stdout);
  //printf("\n  end   = %x.", (int)(this->circle_buf_end_index   - this->start)); fflush(stdout);
  this->start_index ++;
  if (this->start_index == this->end) {
    this->start_index = this->start;
  }
}

void funk2_gc_touch_circle_buffer__touch_f2ptr(funk2_gc_touch_circle_buffer_t* this, f2ptr block_f2ptr) {
  if (block_f2ptr) {
    ptr block_ptr = __f2ptr_to_ptr(block_f2ptr);
    (this)->end_index[0] = (funk2_memblock_t*)from_ptr(block_ptr);
    funk2_gc_touch_circle_buffer__advance_end(this);
  }
}

void funk2_gc_touch_circle_buffer__touch_dptr(funk2_gc_touch_circle_buffer_t* this, dptr_t* dptr) {
  funk2_gc_touch_circle_buffer__touch_f2ptr(this, dptr->p);
  funk2_gc_touch_circle_buffer__touch_f2ptr(this, dptr->tracing_on);
  funk2_gc_touch_circle_buffer__touch_f2ptr(this, dptr->trace);
}

void funk2_gc_touch_circle_buffer__touch_all_referenced_from_block(funk2_gc_touch_circle_buffer_t* this, ptr start_block_ptr) {
  
  release__assert(start_block_ptr, nil, "exp__gc_touch_all_referenced assertion failed: got null value.");
  
  ptype_block_t* start_block = (ptype_block_t*)from_ptr(start_block_ptr);
  this->start_index    = this->start;
  this->end_index      = this->start_index + 1;
  this->start_index[0] = (funk2_memblock_t*)start_block;
  ptype_block_t* block;
  while (this->end_index != this->start_index) {
    block = (ptype_block_t*)(this->start_index[0]);
    if (block && (! block->block.gc_touch)) {
      funk2_gc_touch_circle_buffer__touch_f2ptr(this, block->cause);
      switch(block->ptype) {
      case ptype_free_memory:  error(nil, "block of type free_memory in garbage collector.");
      case ptype_integer:      block->block.gc_touch = 1; break;
      case ptype_double:       block->block.gc_touch = 1; break;
      case ptype_float:        block->block.gc_touch = 1; break;
      case ptype_pointer:      block->block.gc_touch = 1; break;
      case ptype_gfunkptr:     block->block.gc_touch = 1; break;
      case ptype_mutex:        block->block.gc_touch = 1; break;
      case ptype_char:         block->block.gc_touch = 1; break;
      case ptype_string:       block->block.gc_touch = 1; break;
      case ptype_symbol:       block->block.gc_touch = 1; break;
      case ptype_chunk:        block->block.gc_touch = 1; break;
      case ptype_simple_array: block->block.gc_touch = 1; {
	int i;
	f2ptr* iter = (f2ptr*)((ptype_simple_array_block_t*)block)->f2ptr_data;
	for (i = ((ptype_simple_array_block_t*)block)->length; i > 0; i --) {
	  funk2_gc_touch_circle_buffer__touch_f2ptr(this, *iter);
	  iter ++;
	}
      } break;
      case ptype_traced_array: block->block.gc_touch = 1; {
	int i;
	dptr_t* iter = (dptr_t*)((ptype_traced_array_block_t*)block)->dptr_data;
	for (i = ((ptype_traced_array_block_t*)block)->length; i > 0; i --) {
	  funk2_gc_touch_circle_buffer__touch_dptr(this, (dptr_t*)iter);
	  iter ++;
	}
      } break;
      case ptype_larva:        block->block.gc_touch = 1; break;
      default:
	{
	  char str[1024];
	  sprintf(str, "unknown type (%d) of block in garbage collector.", (int)(block->ptype));
	  error(nil, str);
	}
      }
    }
    funk2_gc_touch_circle_buffer__advance_start_index(this);
  }
}

void funk2_gc_touch_circle_buffer__touch_all_referenced_from_f2ptr(funk2_gc_touch_circle_buffer_t* this, f2ptr exp) {
  if(!exp) {return;}
  ptype_block_t* exp_block = (ptype_block_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (exp_block->block.gc_touch) {return;}
  funk2_gc_touch_circle_buffer__touch_all_referenced_from_block(this, to_ptr(exp_block));
}

