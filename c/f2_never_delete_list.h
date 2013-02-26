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

#ifndef F2__NEVER_DELETE_LIST__H
#define F2__NEVER_DELETE_LIST__H

#include "f2_defragmenter.h"

typedef struct funk2_never_delete_list_s {
  u64    alloc_num;
  u64    used_num;
  f2ptr* data;
} funk2_never_delete_list_t;

void funk2_never_delete_list__init                    (funk2_never_delete_list_t* this);
void funk2_never_delete_list__destroy                 (funk2_never_delete_list_t* this);
void funk2_never_delete_list__add_f2ptr               (funk2_never_delete_list_t* this, f2ptr exp);
s64  funk2_never_delete_list__calculate_save_size     (funk2_never_delete_list_t* this);
void funk2_never_delete_list__save_to_stream          (funk2_never_delete_list_t* this, int fd);
void funk2_never_delete_list__load_from_stream        (funk2_never_delete_list_t* this, int fd);
s64  funk2_never_delete_list__load_from_buffer        (funk2_never_delete_list_t* this, u8* buffer);
void funk2_never_delete_list__defragment__fix_pointers(funk2_never_delete_list_t* this);

#endif // F2__NEVER_DELETE_LIST__H

