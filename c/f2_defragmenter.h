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

#ifndef F2__DEFRAGMENTER__TYPES__H
#define F2__DEFRAGMENTER__TYPES__H

typedef struct funk2_defragmenter_s funk2_defragmenter_t;

#endif // F2__DEFRAGMENTER__TYPES__H

#ifndef F2__DEFRAGMENTER__H
#define F2__DEFRAGMENTER__H

#include "f2_heap.h"
#include "f2_hash.h"

#define position_hash__bit_num (17ull)

struct funk2_defragmenter_s {
  u64           total_defragmentation_count;
  boolean_t     need_defragmentation;
  funk2_hash_t* new_old_memory_position_hash;
};

void  funk2_defragmenter__init                          (funk2_defragmenter_t* this);
void  funk2_defragmenter__destroy                       (funk2_defragmenter_t* this);
void  funk2_defragmenter__memory_pool__move_memory      (funk2_defragmenter_t* this, u64 pool_index);
f2ptr funk2_defragmenter__memory_pool__lookup_new_f2ptr (funk2_defragmenter_t* this, f2ptr exp);
void  funk2_defragmenter__memory_pool__fix_pointers     (funk2_defragmenter_t* this, u64 pool_index);
void  funk2_defragmenter__defragment                    (funk2_defragmenter_t* this);
void  funk2_defragmenter__stop_everything_and_defragment(funk2_defragmenter_t* this);
void  funk2_defragmenter__handle                        (funk2_defragmenter_t* this);

#define defragment__fix_pointer(fix_variable) {				\
    (fix_variable) = funk2_defragmenter__memory_pool__lookup_new_f2ptr(&(__funk2.defragmenter), fix_variable); \
  }


// **

void f2__defragmenter__reinitialize_globalvars();
void f2__defragmenter__initialize();

#endif // F2__DEFRAGMENTER__H
