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

#ifndef F2__GARBAGE_COLLECTOR__TYPES__H
#define F2__GARBAGE_COLLECTOR__TYPES__H

typedef enum   funk2_garbage_collector_tricolor_e     funk2_garbage_collector_tricolor_t;
typedef struct funk2_garbage_collector_block_header_s funk2_garbage_collector_block_header_t;
typedef struct funk2_garbage_collector_set_node_s     funk2_garbage_collector_set_node_t;
typedef struct funk2_garbage_collector_set_s          funk2_garbage_collector_set_t;
typedef struct funk2_garbage_collector_s              funk2_garbage_collector_t;

#endif // F2__GARBAGE_COLLECTOR__TYPES__H

#ifndef F2__GARBAGE_COLLECTOR__H
#define F2__GARBAGE_COLLECTOR__H

// garbage_collector_tricolor

enum funk2_garbage_collector_tricolor_e {
  funk2_garbage_collector_tricolor__black = 1,
  funk2_garbage_collector_tricolor__grey,
  funk2_garbage_collector_tricolor__white
};

// garbage_collector_block_header

struct funk2_garbage_collector_block_header_s {
  funk2_garbage_collector_tricolor_t tricolor;
} __attribute__((__packed__));

void funk2_garbage_collector_block_header__init(funk2_garbage_collector_block_header_t* this);
void funk2_garbage_collector_block_header__destroy(funk2_garbage_collector_block_header_t* this);

// garbage_collector_set

struct funk2_garbage_collector_set_s {
  funk2_set_t set;
};

void funk2_garbage_collector_set__init(funk2_garbage_collector_set_t* this);
void funk2_garbage_collector_set__destroy(funk2_garbage_collector_set_t* this);
void funk2_garbage_collector_set__add_block(funk2_garbage_collector_set_t* this, funk2_memblock_t* block);
void funk2_garbage_collector_set__remove_block(funk2_garbage_collector_set_t* this, funk2_memblock_t* block);

// garbage_collector

struct funk2_garbage_collector_s {
  funk2_garbage_collector_set_t black_set;
  funk2_garbage_collector_set_t grey_set;
  funk2_garbage_collector_set_t white_set;
};

void funk2_garbage_collector__init(funk2_garbage_collector_t* this, funk2_memory_t* memory);
void funk2_garbage_collector__destroy(funk2_garbage_collector_t* this);

#endif // F2__GARBAGE_COLLECTOR__H

