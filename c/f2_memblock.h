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

#ifndef F2__MEMBLOCK__TYPES__H
#define F2__MEMBLOCK__TYPES__H

typedef struct funk2_memblock_s funk2_memblock_t;

#endif // F2__MEMBLOCK__TYPES__H

#ifndef F2__MEMBLOCK__H
#define F2__MEMBLOCK__H

#include "f2_heap.h"
#include "f2_ptype.h"
#include "f2_garbage_collector_block_header.h"
#include "f2_atomic.h"

#define memblock__minimum_size ((((sizeof(funk2_memblock_t) - 1) >> f2ptr_block__bit_num) + 1) << f2ptr_block__bit_num)

struct funk2_memblock_s {
  funk2_heap_node_t                      heap_node;
  u64                                    previous_byte_num : pool_address__bit_num;
  funk2_garbage_collector_block_header_t gc;
  ptype_t                                ptype : ptype__min_bits;
  u8                                     used  : 1;
  atomic_t                               reference_count;
  u8                                     raw_mem[0];
} __attribute__((__packed__));

#define funk2_memblock__byte_num(this)          ((this)->heap_node.key)
#define funk2_memblock__previous_byte_num(this) ((this)->previous_byte_num)

// funk2_memblock

void      funk2_memblock__init(funk2_memblock_t* block, f2size_t byte_num, boolean_t used);
boolean_t funk2_memblock__check_all_memory_pointers_valid_in_memory(funk2_memblock_t* this, funk2_memory_t* memory);
boolean_t funk2_memblock__is_self_consistently_valid(funk2_memblock_t* this);
void      funk2_memblock__decrement_reference_count(funk2_memblock_t* this, f2ptr this_f2ptr, funk2_garbage_collector_t* garbage_collector);

#endif // F2__MEMBLOCK__H

