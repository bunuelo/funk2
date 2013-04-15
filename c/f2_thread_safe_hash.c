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

u64 funk2_thread_safe_hash__bin_count(funk2_thread_safe_hash_t* this) {
  return (((u64)1) << (this->bin_num_power));
}

void funk2_thread_safe_hash__init(funk2_thread_safe_hash_t* this, u64 bin_num_power) {
  this->key_count            = 0;
  this->bin_num_power        = bin_num_power;
  u64 bin_count = funk2_thread_safe_hash__bin_count(this);
  {
    this->bin_array = (funk2_thread_safe_hash_bin_node_t**)from_ptr(f2__malloc(sizeof(funk2_thread_safe_hash_bin_node_t*) * bin_count));
    memset(this->bin_array, 0, sizeof(funk2_thread_safe_hash_bin_node_t*) * bin_count);
  }
  {
    this->bin_spinlock = (funk2_processor_spinlock_t*)from_ptr(f2__malloc(sizeof(funk2_processor_spinlock_t) * bin_count));
    s64 index;
    for (index = 0; index < bin_count; index ++) {
      funk2_processor_spinlock__init(&(this->bin_spinlock[index]));
    }
  }
}

void funk2_thread_safe_hash__destroy(funk2_thread_safe_hash_t* this) {
  u64 bin_count = funk2_thread_safe_hash__bin_count(this);
  funk2_thread_safe_hash__remove_all(this);
  f2__free(to_ptr(this->bin_array));
  {
    s64 index;
    for (index = 0; index < bin_count; index ++) {
      funk2_processor_spinlock__destroy(&(this->bin_spinlock[index]));
    }
  }
  f2__free(to_ptr(this->bin_spinlock));
}

void funk2_thread_safe_hash__remove_all(funk2_thread_safe_hash_t* this) {
  this->key_count = 0;
  {
    s64 index;
    for (index = 0; index < funk2_thread_safe_hash__bin_count(this); index ++) {
      funk2_thread_safe_hash_bin_node_t* keyvalue_pair_iter = this->bin_array[index];
      while(keyvalue_pair_iter) {
	funk2_thread_safe_hash_bin_node_t* next = keyvalue_pair_iter->next;
	f2__free(to_ptr(keyvalue_pair_iter));
	keyvalue_pair_iter = next;
      }
      this->bin_array[index] = NULL;
    }
  }
}

void funk2_thread_safe_hash__add(funk2_thread_safe_hash_t* this, u64 key, u64 value) {
  u64                         key__hash_value = key;
  u64                         hash_value      = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64                         hash_value_mask = (0xffffffffffffffffll >> (64 - (this->bin_num_power)));
  u64                         index           = hash_value & hash_value_mask;
  funk2_processor_spinlock_t* bin_spinlock    = &(this->bin_spinlock[index]);
  funk2_processor_spinlock__lock(bin_spinlock);
  {
    funk2_thread_safe_hash_keyvalue_pair_t* keyvalue_pair   = NULL;
    {
      funk2_thread_safe_hash_bin_node_t* keyvalue_pair_iter = this->bin_array[index];
      while(keyvalue_pair_iter) {
	funk2_thread_safe_hash_keyvalue_pair_t* iter__keyvalue_pair = &(keyvalue_pair_iter->keyvalue_pair);
	u64                                     keyvalue_pair__key  = iter__keyvalue_pair->key;
	if (key == keyvalue_pair__key) {
	  keyvalue_pair = iter__keyvalue_pair;
	  break;
	}
	keyvalue_pair_iter = keyvalue_pair_iter->next;
      }
    }
    if (! keyvalue_pair) {
      funk2_thread_safe_hash_bin_node_t* new_bin_node = (funk2_thread_safe_hash_bin_node_t*)from_ptr(f2__malloc(sizeof(funk2_thread_safe_hash_bin_node_t)));
      keyvalue_pair                                   = &(new_bin_node->keyvalue_pair);
      keyvalue_pair->key                              = key;
      keyvalue_pair->value                            = value;
      new_bin_node->next                              = this->bin_array[index];
      this->bin_array[index] = new_bin_node;
      { // increase key count only if didn't already have this key.
	this->key_count ++;
	// in order to avoid a global mutex, we don't change size.
      }
    } else {
      keyvalue_pair->value = value;
    }
  }
  funk2_processor_spinlock__unlock(bin_spinlock);
}

boolean_t funk2_thread_safe_hash__remove(funk2_thread_safe_hash_t* this, u64 key) {
  boolean_t key_was_removed = boolean__false;
  {
    u64                         key__hash_value = key;
    u64                         hash_value      = (key__hash_value * PRIME_NUMBER__16_BIT);
    u64                         hash_value_mask = (0xffffffffffffffffll >> (64 - (this->bin_num_power)));
    u64                         index           = hash_value & hash_value_mask;
    funk2_processor_spinlock_t* bin_spinlock    = &(this->bin_spinlock[index]);
    funk2_processor_spinlock__lock(bin_spinlock);
    {
      funk2_thread_safe_hash_bin_node_t* prev = NULL;
      funk2_thread_safe_hash_bin_node_t* iter = this->bin_array[index];
      while(iter) {
	funk2_thread_safe_hash_bin_node_t*      next               = iter->next;
	funk2_thread_safe_hash_keyvalue_pair_t* keyvalue_pair      = &(iter->keyvalue_pair);
	u64                         keyvalue_pair__key = keyvalue_pair->key;
	if (key == keyvalue_pair__key) {
	  if (prev) {
	    prev->next = next;
	  } else {
	    this->bin_array[index] = next;
	  }
	  this->key_count --;
	  key_was_removed = boolean__true;
	  f2__free(to_ptr(iter));
	  break;
	}
	prev = iter;
	iter = next;
      }
    }
    funk2_processor_spinlock__unlock(bin_spinlock);
  }
  return key_was_removed;
}

funk2_thread_safe_hash_keyvalue_pair_t* funk2_thread_safe_hash__lookup_keyvalue_pair(funk2_thread_safe_hash_t* this, u64 key) {
  u64                         key__hash_value = key;
  u64                         hash_value      = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64                         hash_value_mask = (0xffffffffffffffffll >> (64 - (this->bin_num_power)));
  u64                         index           = hash_value & hash_value_mask;
  funk2_processor_spinlock_t* bin_spinlock    = &(this->bin_spinlock[index]);
  funk2_processor_spinlock__lock(bin_spinlock);
  {
    funk2_thread_safe_hash_bin_node_t* keyvalue_pair_iter = this->bin_array[index];
    while(keyvalue_pair_iter) {
      funk2_thread_safe_hash_keyvalue_pair_t* keyvalue_pair      = &(keyvalue_pair_iter->keyvalue_pair);
      u64                         keyvalue_pair__key = keyvalue_pair->key;
      if (key == keyvalue_pair__key) {
	return keyvalue_pair;
      }
      keyvalue_pair_iter = keyvalue_pair_iter->next;
    }
  }
  funk2_processor_spinlock__unlock(bin_spinlock);
  return nil;
}

u64 funk2_thread_safe_hash__lookup(funk2_thread_safe_hash_t* this, u64 key) {
  funk2_thread_safe_hash_keyvalue_pair_t* keyvalue_pair = funk2_thread_safe_hash__lookup_keyvalue_pair(this, key);
  if (keyvalue_pair) {
    return keyvalue_pair->value;
  }
  error(nil, "funk2_thread_safe_hash__lookup error: attempted to lookup key that is not in funk2_thread_safe_hash.");
}

u64 funk2_thread_safe_hash__try_lookup(funk2_thread_safe_hash_t* this, u64 key, u64 fail_value) {
  funk2_thread_safe_hash_keyvalue_pair_t* keyvalue_pair = funk2_thread_safe_hash__lookup_keyvalue_pair(this, key);
  if (keyvalue_pair) {
    return keyvalue_pair->value;
  }
  return fail_value;
}

boolean_t funk2_thread_safe_hash__contains(funk2_thread_safe_hash_t* this, u64 key) {
  funk2_thread_safe_hash_keyvalue_pair_t* keyvalue_pair = funk2_thread_safe_hash__lookup_keyvalue_pair(this, key);
  return keyvalue_pair ? boolean__true : boolean__false;
}

