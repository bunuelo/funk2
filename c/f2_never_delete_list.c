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

// funk2_never_delete_list

void funk2_never_delete_list__init(funk2_never_delete_list_t* this) {
  this->alloc_num = 1024;
  this->used_num  = 0;
  this->data = (f2ptr*)f2__malloc(sizeof(f2ptr) * this->alloc_num);
}

void funk2_never_delete_list__destroy(funk2_never_delete_list_t* this) {
  free(this->data);
}

void funk2_never_delete_list__add_f2ptr(funk2_never_delete_list_t* this, f2ptr exp) {
  if (this->used_num == this->alloc_num) {
    u64 old_alloc_num = this->alloc_num;
    this->alloc_num <<= 1;
    this->data = f2__new_alloc(this->data, old_alloc_num * sizeof(f2ptr), this->alloc_num * sizeof(f2ptr));
  }
  this->data[this->used_num] = exp;
  this->used_num ++;
}

