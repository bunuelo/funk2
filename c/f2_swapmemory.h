// 
// Copyright (c) 2007-2009 Bo Morgan.
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

#ifndef F2__SWAPMEMORY__H
#define F2__SWAPMEMORY__H

#include "f2_memory.h"
#include "f2_archconfig.h"

typedef struct f2swapmemory_s {
  char     swap_directory[1024];
  char     filename[1024];
  f2size_t byte_num;
  int      fd;
  ptr      ptr;
} f2swapmemory_t;

void f2swapmemory__init_and_alloc(f2swapmemory_t* this, f2size_t byte_num, char* swap_directory);
void f2swapmemory__destroy_and_free(f2swapmemory_t* this);
void f2swapmemory__realloc(f2swapmemory_t* new_swapmemory, f2swapmemory_t* old_swapmemory, f2size_t byte_num);

#endif // F2__SWAPMEMORY__H

