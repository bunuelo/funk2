// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#ifndef F2__F2PTR__H
#define F2__F2PTR__H

#include "f2_memory.h"

extern f2ptr_t* nil;

typedef unsigned long      ip_addr_t;
typedef unsigned char      pool_index_t;
typedef unsigned long long pool_offset_t;

struct f2ptr_s {
  ip_addr_t     ip_addr;
  pool_index_t  pool_index;
  pool_offset_t pool_offset;
} __attribute__((__packed__));
typedef struct f2ptr_s f2ptr_t;

void     big_f2ptr__init(f2ptr_t* this, ip_addr_t ip_addr, pool_index_t pool_index, pool_offset_t pool_offset);
f2ptr_t* big_f2ptr__new(ip_addr_t ip_addr, pool_index_t pool_index, pool_offset_t pool_offset);
void     big_f2ptr__delete(f2ptr_t* this);

#define f2ptr__init(this, pool_offset) big_f2ptr__init(this, 0, 0, pool_offset);
#define f2ptr__memcpy(dest, src)       memcpy(dest, src, sizeof(f2ptr_t))
#define f2ptr__bzero(this)             bzero(this, sizeof(f2ptr_t))

#endif // F2__F2PTR__H
