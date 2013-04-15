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

#ifndef F2__THREAD_SAFE_HASH__H
#define F2__THREAD_SAFE_HASH__H

#include "f2_processor_spinlock.h"

typedef struct funk2_thread_safe_hash_keyvalue_pair_s funk2_thread_safe_hash_keyvalue_pair_t;
struct funk2_thread_safe_hash_keyvalue_pair_s {
  u64 key;
  u64 value;
};

typedef struct funk2_thread_safe_hash_bin_node_s funk2_thread_safe_hash_bin_node_t;
struct funk2_thread_safe_hash_bin_node_s {
  funk2_thread_safe_hash_keyvalue_pair_t    keyvalue_pair;
  struct funk2_thread_safe_hash_bin_node_s* next;
};

typedef struct funk2_thread_safe_hash_s funk2_thread_safe_hash_t;
struct funk2_thread_safe_hash_s {
  u64                                 key_count;
  u64                                 bin_num_power;
  funk2_thread_safe_hash_bin_node_t** bin_array;
  funk2_processor_spinlock_t*         bin_spinlock;
};

u64                                     funk2_thread_safe_hash__bin_count           (funk2_thread_safe_hash_t* this);
void                                    funk2_thread_safe_hash__init                (funk2_thread_safe_hash_t* this, u64 bin_num_power);
void                                    funk2_thread_safe_hash__destroy             (funk2_thread_safe_hash_t* this);
void                                    funk2_thread_safe_hash__remove_all          (funk2_thread_safe_hash_t* this);
void                                    funk2_thread_safe_hash__add                 (funk2_thread_safe_hash_t* this, u64 key, u64 value);
boolean_t                               funk2_thread_safe_hash__remove              (funk2_thread_safe_hash_t* this, u64 key);
funk2_thread_safe_hash_keyvalue_pair_t* funk2_thread_safe_hash__lookup_keyvalue_pair(funk2_thread_safe_hash_t* this, u64 key);
u64                                     funk2_thread_safe_hash__lookup              (funk2_thread_safe_hash_t* this, u64 key);
u64                                     funk2_thread_safe_hash__try_lookup          (funk2_thread_safe_hash_t* this, u64 key, u64 fail_value);
boolean_t                               funk2_thread_safe_hash__contains            (funk2_thread_safe_hash_t* this, u64 key);

#define funk2_thread_safe_hash__iteration(this, funk2_thread_safe_hash__iteration__user_key, funk2_thread_safe_hash__iteration__user_value, code) {			\
    funk2_thread_safe_hash_t* funk2_thread_safe_hash__iteration__this  = (this);		\
    u64           funk2_thread_safe_hash__iteration__index = 0;			\
    u64           funk2_thread_safe_hash__iteration__this__bin_num = 1ull << (funk2_thread_safe_hash__iteration__this->bin_num_power); \
    while (funk2_thread_safe_hash__iteration__index < funk2_thread_safe_hash__iteration__this__bin_num) { \
      funk2_thread_safe_hash_bin_node_t* funk2_thread_safe_hash__iteration__bin_node = funk2_thread_safe_hash__iteration__this->bin_array[funk2_thread_safe_hash__iteration__index]; \
      while (funk2_thread_safe_hash__iteration__bin_node != NULL) {			\
	u64 funk2_thread_safe_hash__iteration__user_key   = funk2_thread_safe_hash__iteration__bin_node->keyvalue_pair.key;	\
	u64 funk2_thread_safe_hash__iteration__user_value = funk2_thread_safe_hash__iteration__bin_node->keyvalue_pair.value; \
	{								\
	  code;								\
	}								\
	funk2_thread_safe_hash__iteration__bin_node = funk2_thread_safe_hash__iteration__bin_node->next; \
      }									\
      funk2_thread_safe_hash__iteration__index ++;					\
    }									\
  }

#define funk2_thread_safe_hash__key__iteration(this, funk2_thread_safe_hash__iteration__user_key, code) {			\
    funk2_thread_safe_hash_t* funk2_thread_safe_hash__iteration__this  = (this);		\
    u64           funk2_thread_safe_hash__iteration__index = 0;			\
    u64           funk2_thread_safe_hash__iteration__this__bin_num = 1ull << (funk2_thread_safe_hash__iteration__this->bin_num_power); \
    while (funk2_thread_safe_hash__iteration__index < funk2_thread_safe_hash__iteration__this__bin_num) { \
      funk2_thread_safe_hash_bin_node_t* funk2_thread_safe_hash__iteration__bin_node = funk2_thread_safe_hash__iteration__this->bin_array[funk2_thread_safe_hash__iteration__index]; \
      while (funk2_thread_safe_hash__iteration__bin_node != NULL) {			\
	u64 funk2_thread_safe_hash__iteration__user_key = funk2_thread_safe_hash__iteration__bin_node->keyvalue_pair.key; \
	{								\
	  code;								\
	}								\
	funk2_thread_safe_hash__iteration__bin_node = funk2_thread_safe_hash__iteration__bin_node->next; \
      }									\
      funk2_thread_safe_hash__iteration__index ++;					\
    }									\
  }

#define funk2_thread_safe_hash__value__iteration(this, funk2_thread_safe_hash__iteration__user_value, code) {			\
    funk2_thread_safe_hash_t* funk2_thread_safe_hash__iteration__this  = (this);		\
    u64           funk2_thread_safe_hash__iteration__index = 0;			\
    u64           funk2_thread_safe_hash__iteration__this__bin_num = 1ull << (funk2_thread_safe_hash__iteration__this->bin_num_power); \
    while (funk2_thread_safe_hash__iteration__index < funk2_thread_safe_hash__iteration__this__bin_num) { \
      funk2_thread_safe_hash_bin_node_t* funk2_thread_safe_hash__iteration__bin_node = funk2_thread_safe_hash__iteration__this->bin_array[funk2_thread_safe_hash__iteration__index]; \
      while (funk2_thread_safe_hash__iteration__bin_node != NULL) {			\
	u64 funk2_thread_safe_hash__iteration__user_value = funk2_thread_safe_hash__iteration__bin_node->keyvalue_pair.value; \
	{								\
	  code;								\
	}								\
	funk2_thread_safe_hash__iteration__bin_node = funk2_thread_safe_hash__iteration__bin_node->next; \
      }									\
      funk2_thread_safe_hash__iteration__index ++;					\
    }									\
  }

#endif // F2__THREAD_SAFE_HASH__H

