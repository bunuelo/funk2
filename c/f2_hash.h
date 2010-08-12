// 
// Copyright (c) 2007-2010 Bo Morgan.
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

#ifndef F2__HASH__H
#define F2__HASH__H

typedef struct funk2_hash_keyvalue_pair_s funk2_hash_keyvalue_pair_t;
struct funk2_hash_keyvalue_pair_s {
  u64 key;
  u64 value;
};

typedef struct funk2_hash_bin_node_s funk2_hash_bin_node_t;
struct funk2_hash_bin_node_s {
  funk2_hash_keyvalue_pair_t    keyvalue_pair;
  struct funk2_hash_bin_node_s* next;
};

typedef struct funk2_hash_s funk2_hash_t;
struct funk2_hash_s {
  u64                          key_count;
  u64                          bin_num_power;
  funk2_hash_keyvalue_pair_t** bin_array;
};

u64                         funk2_hash__bin_count(funk2_hash_t* this);
void                        funk2_hash__init(funk2_hash_t* this, u64 bin_num_power);
void                        funk2_hash__destroy(funk2_hash_t* this);
void                        funk2_hash__add(funk2_hash_t* this, u64 key, u64 value);
boolean_t                   funk2_hash__remove(funk2_hash_t* this, u64 key);
funk2_hash_keyvalue_pair_t* funk2_hash__lookup_keyvalue_pair(funk2_hash_t* this, u64 key);
u64                         funk2_hash__lookup(funk2_hash_t* this, u64 key);
boolean_t                   funk2_hash__contains(funk2_hash_t* this, u64 key);

#endif // F2__HASH__H

