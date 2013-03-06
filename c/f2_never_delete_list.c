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

#include "funk2.h"

// funk2_never_delete_list

void funk2_never_delete_list__init(funk2_never_delete_list_t* this) {
  this->alloc_num = 1024;
  this->used_num  = 0;
  this->data = (f2ptr*)from_ptr(f2__malloc(sizeof(f2ptr) * this->alloc_num));
}

void funk2_never_delete_list__destroy(funk2_never_delete_list_t* this) {
  f2__free(to_ptr(this->data));
}

void funk2_never_delete_list__add_f2ptr(funk2_never_delete_list_t* this, f2ptr exp) {
  if (this->used_num == this->alloc_num) {
    u64 old_alloc_num = this->alloc_num;
    this->alloc_num <<= 1;
    this->data = (f2ptr*)from_ptr(f2__new_alloc(to_ptr(this->data), old_alloc_num * sizeof(f2ptr), this->alloc_num * sizeof(f2ptr)));
  }
  this->data[this->used_num] = exp;
  this->used_num ++;
}

s64 funk2_never_delete_list__calculate_save_size(funk2_never_delete_list_t* this) {
  s64 save_size = 0;
  {
    u64 used_num = this->used_num;
    save_size += sizeof(used_num);
    save_size += (used_num * sizeof(f2ptr));
  }
  return save_size;
}

void funk2_never_delete_list__save_to_stream(funk2_never_delete_list_t* this, int fd) {
  u64 used_num = this->used_num;
  safe_write(fd, to_ptr(&used_num), sizeof(used_num));
  u64 index;
  for (index = 0; index < used_num; index ++) {
    f2ptr exp = this->data[index];
    safe_write(fd, to_ptr(&exp), sizeof(exp));
  }
}

void funk2_never_delete_list__load_from_stream(funk2_never_delete_list_t* this, int fd) {
  u64 used_num;
  safe_read(fd, to_ptr(&used_num), sizeof(used_num));
  u64 index;
  for (index = 0; index < used_num; index ++) {
    f2ptr exp;
    safe_read(fd, to_ptr(&exp), sizeof(exp));
    funk2_never_delete_list__add_f2ptr(this, exp);
  }
}

s64 funk2_never_delete_list__load_from_buffer(funk2_never_delete_list_t* this, u8* buffer) {
  u8* buffer_iter = buffer;
  {
    u64 used_num;
    memcpy(&used_num, buffer_iter, sizeof(used_num)); buffer_iter += sizeof(used_num);
    u64 index;
    for (index = 0; index < used_num; index ++) {
      f2ptr exp;
      memcpy(&exp, buffer_iter, sizeof(exp)); buffer_iter += sizeof(exp);
      funk2_never_delete_list__add_f2ptr(this, exp);
    }
  }
  return (s64)(buffer_iter - buffer);
}

void funk2_never_delete_list__defragment__fix_pointers(funk2_never_delete_list_t* this) {
  u64 used_num = this->used_num;
  u64 index;
  for (index = 0; index < used_num; index ++) {
    f2ptr exp = this->data[index];
    defragment__fix_pointer(exp);
    this->data[index] = exp;
  }
}

