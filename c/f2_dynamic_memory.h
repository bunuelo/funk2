// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#ifndef F2__DYNAMIC_MEMORY__H
#define F2__DYNAMIC_MEMORY__H

//#include "f2_memory.h"
#include "f2_archconfig.h"

typedef struct f2dynamicmemory_s {
  f2size_t byte_num;
  ptr      ptr;
  ptr      raw_ptr;
} f2dynamicmemory_t;

void f2dynamicmemory__init_and_alloc(f2dynamicmemory_t* this, f2size_t byte_num);
void f2dynamicmemory__destroy_and_free(f2dynamicmemory_t* this);
void f2dynamicmemory__realloc(f2dynamicmemory_t* new_swapmemory, f2dynamicmemory_t* old_swapmemory, f2size_t byte_num);

#endif // F2__DYNAMIC_MEMORY__H

