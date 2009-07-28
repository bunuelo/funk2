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

#ifndef F2__PROTECTED_ALLOC_ARRAY__H
#define F2__PROTECTED_ALLOC_ARRAY__H

typedef struct funk2_protected_alloc_array_s {
  u64    used_num;
  u64    length;
  f2ptr* data;
  u64    reentrance_count;
  u64    max_reentrance_count;
} funk2_protected_alloc_array_t;

void funk2_protected_alloc_array__init(funk2_protected_alloc_array_t* this);
void funk2_protected_alloc_array__destroy(funk2_protected_alloc_array_t* this);
void funk2_protected_alloc_array__add_protected_alloc_f2ptr(funk2_protected_alloc_array_t* this, f2ptr exp);
void funk2_protected_alloc_array__signal_enter_protected_region(funk2_protected_alloc_array_t* this);
void funk2_protected_alloc_array__signal_exit_protected_region(funk2_protected_alloc_array_t* this);

#endif // F2__PROTECTED_ALLOC_ARRAY__H

