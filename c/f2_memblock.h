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

#ifndef F2__MEMBLOCK__H
#define F2__MEMBLOCK__H

struct funk2_memblock_s;

#include "f2_ptype.h"

typedef struct funk2_memblock_s funk2_memblock_t;
struct funk2_memblock_s {
  rbt_node_t rbt_node;
  u8         used           : 1;
  u8         gc_touch       : 1;
  u8         generation_num : 3;
  u8         ptype          : ptype__min_bits;
  u8         raw_mem[0];
} __attribute__((__packed__));

#define funk2_memblock__byte_num(this)         ((this)->rbt_node.key)

// funk2_memblock

void      funk2_memblock__init(funk2_memblock_t* block, f2size_t byte_num, int used, int gc_touch);
boolean_t funk2_memblock__check_all_memory_pointers_valid_in_memory(funk2_memblock_t* this, funk2_memory_t* memory);

#endif // F2__MEMBLOCK__H

