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

#ifndef F2__STATICMEMORY__H
#define F2__STATICMEMORY__H

#include "f2_memory.h"
#include "f2_archconfig.h"

typedef struct f2staticmemory_s {
  u8 ptr[STATIC_MEMORY__BYTE_NUM];
} f2staticmemory_t;

void f2staticmemory__initialize(f2staticmemory_t* this);

f2staticmemory_t* global_static_memory();

#endif // F2__SWAPMEMORY__H
