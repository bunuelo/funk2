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

#ifndef F2__GARBAGE_COLLECTOR_BLOCK_HEADER__TYPES__H
#define F2__GARBAGE_COLLECTOR_BLOCK_HEADER__TYPES__H

typedef struct funk2_garbage_collector_block_header_s funk2_garbage_collector_block_header_t;

#endif // F2__GARBAGE_COLLECTOR_BLOCK_HEADER__TYPES__H

#ifndef F2__GARBAGE_COLLECTOR_BLOCK_HEADER__H
#define F2__GARBAGE_COLLECTOR_BLOCK_HEADER__H

// garbage_collector_block_header

struct funk2_garbage_collector_block_header_s {
  funk2_tricolor_t tricolor : 2;
} __attribute__((__packed__));

void funk2_garbage_collector_block_header__init   (funk2_garbage_collector_block_header_t* this);
void funk2_garbage_collector_block_header__destroy(funk2_garbage_collector_block_header_t* this);

#endif // F2__GARBAGE_COLLECTOR_BLOCK_HEADER__H

