// 
// Copyright (c) 2007-2012 Bo Morgan.
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

u64 funk2_hash__bin_count(funk2_hash_t* this) {
  return (((u64)1) << (this->bin_num_power));
}

void funk2_hash__init(funk2_hash_t* this, u64 bin_num_power) {
  this->key_count            = 0;
  this->bin_num_power        = bin_num_power;
  this->bin_array            = (funk2_hash_bin_node_t**)from_ptr(f2__malloc(sizeof(funk2_hash_bin_node_t*) * funk2_hash__bin_count(this)));
  memset(this->bin_array, 0, sizeof(funk2_hash_bin_node_t*) * funk2_hash__bin_count(this));
}

void funk2_hash__destroy(funk2_hash_t* this) {
  funk2_hash__remove_all(this);
  f2__free(to_ptr(this->bin_array));
}

void funk2_hash__remove_all(funk2_hash_t* this) {
  s64 index;
  for (index = 0; index < funk2_hash__bin_count(this); index ++) {
    funk2_hash_bin_node_t* keyvalue_pair_iter = this->bin_array[index];
    while(keyvalue_pair_iter) {
      funk2_hash_bin_node_t* next = keyvalue_pair_iter->next;
      f2__free(to_ptr(keyvalue_pair_iter));
      keyvalue_pair_iter = next;
    }
    this->bin_array[index] = NULL;
  }
}

void funk2_hash__add(funk2_hash_t* this, u64 key, u64 value) {
  u64                         key__hash_value    = key;
  u64                         hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64                         hash_value_mask    = (0xffffffffffffffffll >> (64 - (this->bin_num_power)));
  u64                         index              = hash_value & hash_value_mask;
  funk2_hash_keyvalue_pair_t* keyvalue_pair      = NULL;
  {
    funk2_hash_bin_node_t* keyvalue_pair_iter = this->bin_array[index];
    while(keyvalue_pair_iter) {
      funk2_hash_keyvalue_pair_t* iter__keyvalue_pair = &(keyvalue_pair_iter->keyvalue_pair);
      u64                         keyvalue_pair__key  = iter__keyvalue_pair->key;
      if (key == keyvalue_pair__key) {
	keyvalue_pair = iter__keyvalue_pair;
	break;
      }
      keyvalue_pair_iter = keyvalue_pair_iter->next;
    }
  }
  if (! keyvalue_pair) {
    funk2_hash_bin_node_t* new_bin_node = (funk2_hash_bin_node_t*)from_ptr(f2__malloc(sizeof(funk2_hash_bin_node_t)));
    keyvalue_pair                       = &(new_bin_node->keyvalue_pair);
    keyvalue_pair->key                  = key;
    keyvalue_pair->value                = value;
    new_bin_node->next                  = this->bin_array[index];
    this->bin_array[index] = new_bin_node;
    { // increase key count only if didn't already have this key.
      this->key_count ++;
      //
      // -- If we wanted to write the double_size function, this is where it would be called.
      //
      //if ((key_count__i << 1) >= (1ll << bin_num_power__i)) {
      //  funk2_hash__double_size(this);
      //}
      //
      // --
      //
    }
  } else {
    keyvalue_pair->value = value;
  }
}

boolean_t funk2_hash__remove(funk2_hash_t* this, u64 key) {
  boolean_t key_was_removed = boolean__false;
  {
    u64 key__hash_value  = key;
    u64 hash_value       = (key__hash_value * PRIME_NUMBER__16_BIT);
    u64 hash_value_mask  = (0xffffffffffffffffll >> (64 - (this->bin_num_power)));
    u64 index            = hash_value & hash_value_mask;
    {
      funk2_hash_bin_node_t* prev = NULL;
      funk2_hash_bin_node_t* iter = this->bin_array[index];
      while(iter) {
	funk2_hash_bin_node_t*      next               = iter->next;
	funk2_hash_keyvalue_pair_t* keyvalue_pair      = &(iter->keyvalue_pair);
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
  }
  return key_was_removed;
}

funk2_hash_keyvalue_pair_t* funk2_hash__lookup_keyvalue_pair(funk2_hash_t* this, u64 key) {
  u64 key__hash_value = key;
  u64 hash_value      = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64 hash_value_mask = (0xffffffffffffffffll >> (64 - (this->bin_num_power)));
  u64 index           = hash_value & hash_value_mask;
  {
    funk2_hash_bin_node_t* keyvalue_pair_iter = this->bin_array[index];
    while(keyvalue_pair_iter) {
      funk2_hash_keyvalue_pair_t* keyvalue_pair      = &(keyvalue_pair_iter->keyvalue_pair);
      u64                         keyvalue_pair__key = keyvalue_pair->key;
      if (key == keyvalue_pair__key) {
	return keyvalue_pair;
      }
      keyvalue_pair_iter = keyvalue_pair_iter->next;
    }
  }
  return nil;
}

u64 funk2_hash__lookup(funk2_hash_t* this, u64 key) {
  funk2_hash_keyvalue_pair_t* keyvalue_pair = funk2_hash__lookup_keyvalue_pair(this, key);
  if (keyvalue_pair) {
    return keyvalue_pair->value;
  }
  error(nil, "funk2_hash__lookup error: attempted to lookup key that is not in funk2_hash.");
}

boolean_t funk2_hash__contains(funk2_hash_t* this, u64 key) {
  funk2_hash_keyvalue_pair_t* keyvalue_pair = funk2_hash__lookup_keyvalue_pair(this, key);
  return keyvalue_pair ? boolean__true : boolean__false;
}

