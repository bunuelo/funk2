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

// funk2_thread_safe_hash_keyvalue_pair

void funk2_thread_safe_hash_keyvalue_pair__init(funk2_thread_safe_hash_keyvalue_pair_t* this, u64 key, u64 value) {
  funk2_atomic_u64__init(&(this->key),   key);
  funk2_atomic_u64__init(&(this->value), value);
}

void funk2_thread_safe_hash_keyvalue_pair__destroy(funk2_thread_safe_hash_keyvalue_pair_t* this) {
  funk2_atomic_u64__destroy(&(this->key));
  funk2_atomic_u64__destroy(&(this->value));
}


// funk2_thread_safe_hash_bin_node

void funk2_thread_safe_hash_bin_node__init(funk2_thread_safe_hash_bin_node_t* this, u64 key, u64 value) {
  funk2_thread_safe_hash_keyvalue_pair__init(&(this->keyvalue_pair), key, value);
  funk2_atomic_u64__init(&(this->next), (u64)to_ptr(NULL));
}

void funk2_thread_safe_hash_bin_node__destroy(funk2_thread_safe_hash_bin_node_t* this) {
  funk2_thread_safe_hash_keyvalue_pair__destroy(&(this->keyvalue_pair));
  funk2_atomic_u64__destroy(&(this->next));
}


// funk2_thread_safe_hash

void funk2_thread_safe_hash__init(funk2_thread_safe_hash_t* this, u64 bin_num_power) {
  funk2_atomic_u64__init(&(this->key_count), 0);
  this->bin_num_power = bin_num_power;
  u64 bin_count = funk2_thread_safe_hash__bin_count(this);
  {
    this->bin_array = (funk2_atomic_u64_t*)from_ptr(f2__malloc(sizeof(funk2_atomic_u64_t) * bin_count));
    {
      u64 index;
      for (index = 0; index < bin_count; index ++) {
	funk2_atomic_u64__init(&(this->bin_array[index]), (u64)to_ptr(NULL));
      }
    }
  }
}

void funk2_thread_safe_hash__destroy(funk2_thread_safe_hash_t* this) {
  funk2_atomic_u64__destroy(&(this->key_count));
  {
    u64 bin_count = funk2_thread_safe_hash__bin_count(this);
    {
      s64 index;
      for (index = 0; index < funk2_thread_safe_hash__bin_count(this); index ++) {
	funk2_thread_safe_hash_bin_node_t* keyvalue_pair_iter = funk2_thread_safe_hash__bin_array(this, index);
	while(keyvalue_pair_iter) {
	  funk2_thread_safe_hash_bin_node_t* next = funk2_thread_safe_hash_bin_node__next(keyvalue_pair_iter);
	  funk2_thread_safe_hash_bin_node__destroy(keyvalue_pair_iter);
	  f2__free(to_ptr(keyvalue_pair_iter));
	  keyvalue_pair_iter = next;
	}
      }
    }
    {
      u64 index;
      for (index = 0; index < bin_count; index ++) {
	funk2_atomic_u64__destroy(&(this->bin_array[index]));
      }
    }
    f2__free(to_ptr(this->bin_array));
  }
}

void funk2_thread_safe_hash__remove_all(funk2_thread_safe_hash_t* this) {
}

void funk2_thread_safe_hash__add(funk2_thread_safe_hash_t* this, u64 key, u64 value) {
  u64 key__hash_value = key;
  u64 hash_value      = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64 hash_value_mask = (0xffffffffffffffffll >> (64 - (this->bin_num_power)));
  u64 index           = hash_value & hash_value_mask;
  {
    funk2_thread_safe_hash_keyvalue_pair_t* keyvalue_pair = NULL;
    {
      funk2_thread_safe_hash_bin_node_t* keyvalue_pair_iter = funk2_thread_safe_hash__bin_array(this, index);
      while(keyvalue_pair_iter) {
	funk2_thread_safe_hash_keyvalue_pair_t* iter__keyvalue_pair = &(keyvalue_pair_iter->keyvalue_pair);
	u64                                     keyvalue_pair__key  = funk2_thread_safe_hash_keyvalue_pair__key(iter__keyvalue_pair);
	if (key == keyvalue_pair__key) {
	  keyvalue_pair = iter__keyvalue_pair;
	  break;
	}
	keyvalue_pair_iter = funk2_thread_safe_hash_bin_node__next(keyvalue_pair_iter);
      }
    }
    if (! keyvalue_pair) {
      funk2_thread_safe_hash_bin_node_t* new_bin_node = (funk2_thread_safe_hash_bin_node_t*)from_ptr(f2__malloc(sizeof(funk2_thread_safe_hash_bin_node_t)));
      funk2_thread_safe_hash_bin_node__init(new_bin_node, key, value);
      keyvalue_pair = &(new_bin_node->keyvalue_pair);
      {
	boolean_t success = boolean__false;
	{
	  while (! success) {
	    u64 bin_array_value = funk2_thread_safe_hash__bin_array(this, index);
	    funk2_atomic_u64__set_value(&(new_bin_node->next), bin_array_value);
	    success = funk2_atomic_u64__compare_and_swap(&(this->bin_array[index]), bin_array_value, (u64)to_ptr(new_bin_node));
	  }
	}
      }
      { // increase key count only if didn't already have this key.
	funk2_atomic_u64__increment(&(this->key_count));
	// we don't change size when too many keys are inserted to avoid global mutex
      }
    } else {
      funk2_atomic_u64__set_value(&(keyvalue_pair->value), value);
    }
  }
}

boolean_t funk2_thread_safe_hash__remove(funk2_thread_safe_hash_t* this, u64 key) {
  boolean_t key_was_removed = boolean__false;
  {
    u64 key__hash_value = key;
    u64 hash_value      = (key__hash_value * PRIME_NUMBER__16_BIT);
    u64 hash_value_mask = (0xffffffffffffffffll >> (64 - (this->bin_num_power)));
    u64 index           = hash_value & hash_value_mask;
    {
      boolean_t success     = boolean__false;
      boolean_t keep_trying = boolean__true;
      while (keep_trying && (! success)) {
	keep_trying = boolean__false;
	{
	  funk2_thread_safe_hash_bin_node_t* prev = NULL;
	  funk2_thread_safe_hash_bin_node_t* iter = funk2_thread_safe_hash__bin_array(this, index);
	  while(iter) {
	    funk2_thread_safe_hash_bin_node_t*      next               = funk2_thread_safe_hash_bin_node__next(iter);
	    funk2_thread_safe_hash_keyvalue_pair_t* keyvalue_pair      = &(iter->keyvalue_pair);
	    u64                                     keyvalue_pair__key = funk2_thread_safe_hash_keyvalue_pair__key(keyvalue_pair);
	    if (key == keyvalue_pair__key) {
	      keep_trying = boolean__true;
	      if (prev) {
		u64 old_prev_next = funk2_atomic_u64__value(&(prev->next));
		if (old_prev_next == iter) {
		  success = funk2_atomic_u64__compare_and_swap(&(prev->next), old_prev_next, (u64)to_ptr(next));
		}
	      } else {
		u64 old_bin_array_value = funk2_thread_safe_hash__bin_array(this, index);
		if (old_bin_array_value == iter) {
		  success = funk2_atomic_u64__compare_and_swap(&(this->bin_array[index]), old_bin_array_value, (u64)to_ptr(next));
		}
	      }
	      if (success) {
		funk2_atomic_u64__decrement(&(this->key_count));
		key_was_removed = boolean__true;
		f2__free(to_ptr(iter));
	      }
	      break;
	    }
	    prev = iter;
	    iter = next;
	  }
	}
      }
    }
  }
  return key_was_removed;
}

funk2_thread_safe_hash_keyvalue_pair_t* funk2_thread_safe_hash__lookup_keyvalue_pair(funk2_thread_safe_hash_t* this, u64 key) {
  u64 key__hash_value = key;
  u64 hash_value      = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64 hash_value_mask = (0xffffffffffffffffll >> (64 - (this->bin_num_power)));
  u64 index           = hash_value & hash_value_mask;
  {
    funk2_thread_safe_hash_bin_node_t* keyvalue_pair_iter = funk2_thread_safe_hash__bin_array(this, index);
    while(keyvalue_pair_iter) {
      funk2_thread_safe_hash_keyvalue_pair_t* keyvalue_pair      = &(keyvalue_pair_iter->keyvalue_pair);
      u64                                     keyvalue_pair__key = funk2_thread_safe_hash_keyvalue_pair__key(keyvalue_pair);
      if (key == keyvalue_pair__key) {
	return keyvalue_pair;
      }
      keyvalue_pair_iter = funk2_thread_safe_hash_bin_node__next(keyvalue_pair_iter);
    }
  }
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

