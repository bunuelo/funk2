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

#include "funk2.h"

void f2dynamicmemory__init_and_alloc(f2dynamicmemory_t* this, f2size_t byte_num) {
  this->byte_num = byte_num;
  this->ptr      = f2__malloc(byte_num);
  if (from_ptr(this->ptr) == NULL) {
    perror("malloc");
    exit(-1);
  }
  memset(from_ptr(this->ptr), 0, byte_num);
}

void f2dynamicmemory__destroy_and_free(f2dynamicmemory_t* this) {
  f2__free(this->ptr);
  this->byte_num = 0;
  this->ptr      = to_ptr(NULL);
}

void f2dynamicmemory__realloc(f2dynamicmemory_t* new_memory, f2dynamicmemory_t* old_memory, f2size_t byte_num) {
  new_memory->ptr = to_ptr(realloc(from_ptr(old_memory->ptr), byte_num));
  if (from_ptr(new_memory->ptr) == NULL) {
    status("f2dynamicmemory__realloc fatal: realloc error \"%s\".", strerror(errno));
    status("                                byte_num=" u64__fstr ".", (u64)byte_num);
    perror("realloc");
    exit(-1);
  }
  if (old_memory->byte_num > byte_num) {
    memset(((u8*)from_ptr(new_memory->ptr)) + old_memory->byte_num, 0, byte_num - (old_memory->byte_num));
  }
  new_memory->byte_num = byte_num;
}


