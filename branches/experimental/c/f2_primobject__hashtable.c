// 
// Copyright (c) 2007-2009 Bo Morgan.
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

// hashtable primobject definition

defprimobject__static_slot(hashtable__bin_num_power, 0);
defprimobject__static_slot(hashtable__bin_array,     1);

f2ptr __hashtable__symbol = -1;

f2ptr f2hashtable__new(f2ptr cause, f2ptr bin_num_power, f2ptr bin_array) {
  release__assert(__hashtable__symbol != -1, nil, "f2hashtable__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __hashtable__symbol, 2, nil);
  f2hashtable__bin_num_power__set(this, cause, bin_num_power);
  f2hashtable__bin_array__set(    this, cause, bin_array);
  return this;
}

// hardcoded hashtable functions

boolean_t raw__hashtablep(f2ptr this, f2ptr cause) {
  return raw__arrayp(this, cause) && f2primobject__is_hashtable(this, cause);
}

f2ptr f2__hashtablep(f2ptr this, f2ptr cause) {
  return f2bool__new(raw__hashtablep(this, cause));
}

boolean_t raw__hashtable__valid(f2ptr cause, f2ptr this) {
  if (! raw__hashtablep(this, cause)) {return 0;}
  f2ptr bin_num_power = f2hashtable__bin_num_power(this, cause);
  f2ptr bin_array     = f2hashtable__bin_array(this, cause);
  if (! raw__integerp(bin_num_power, cause)) {return 0;}
  if (! raw__arrayp(bin_array, cause))       {return 0;}
  s64 bin_num_power__i = f2integer__i(bin_num_power, cause);
  s64 length           = raw__array__length(cause, bin_array);
  if (! (length == (1ll << bin_num_power__i))) {return 0;}
  return 1;
}

f2ptr raw__hashtable__new(f2ptr cause, s64 bin_num_power) {
  f2ptr bin_array = raw__array__new(cause, 1ll << bin_num_power);
  f2ptr this = f2hashtable__new(cause, f2integer__new(cause, bin_num_power), bin_array);
  resume_gc();
  debug__assert(raw__hashtable__valid(cause, this), nil, "f2__hashtable__new assert failed: f2__hashtable__valid(this)");
  return this;
}

f2ptr f2__hashtable__new(f2ptr cause, f2ptr bin_num_power) {
  if(! raw__integerp(bin_num_power, cause)) {
    return f2larva__new(cause, 1);
  }
  pause_gc();
  f2ptr this = raw__hashtable__new(cause, f2integer__i(bin_num_power, cause));
  resume_gc();
  debug__assert(raw__hashtable__valid(cause, this), nil, "f2__hashtable__new assert failed: f2__hashtable__valid(this)");
  return this;
}

f2ptr f2__hashtable__add_keyvalue_pair(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  debug__assert(raw__hashtable__valid(cause, this), nil, "f2__hashtable__add_keyvalue_pair assert failed: f2__hashtable__valid(this)");
  if(! raw__symbolp(key, cause)) {
    return f2larva__new(cause, 1);
  }
  pause_gc();
  f2ptr bin_num_power      = f2hashtable__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2hashtable__bin_array(this, cause);
  u64   key__hash_value    = f2symbol__hash_value(key, cause);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr keyvalue_pair      = nil;
  f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
  while(keyvalue_pair_iter) {
    f2ptr iter__keyvalue_pair = f2cons__car(keyvalue_pair_iter,  cause);
    f2ptr keyvalue_pair__key  = f2cons__car(iter__keyvalue_pair, cause);
    if (f2__symbol__eq(cause, key, keyvalue_pair__key)) {
      keyvalue_pair = iter__keyvalue_pair;
      break;
    }
    keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
  }
  if (! keyvalue_pair) {
    keyvalue_pair = f2cons__new(cause, key, value);
    raw__array__elt__set(cause, bin_array, index, f2cons__new(cause, keyvalue_pair, raw__array__elt(cause, bin_array, index)));
  } else {
    f2cons__cdr__set(keyvalue_pair, cause, value);
  }
  resume_gc();
  return nil;
}

f2ptr f2__hashtable__lookup_keyvalue_pair(f2ptr this, f2ptr cause, f2ptr key) {
  debug__assert(raw__hashtable__valid(cause, this), nil, "f2__hashtable__lookup_keyvalue_pair assert failed: f2__hashtable__valid(this)");
  if(! raw__symbolp(key, cause)) {
    return f2larva__new(cause, 1);
  }
  pause_gc();
  f2ptr bin_num_power      = f2hashtable__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2hashtable__bin_array(this, cause);
  u64   key__hash_value    = f2symbol__hash_value(key, cause);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
  while(keyvalue_pair_iter) {
    f2ptr keyvalue_pair      = f2cons__car(keyvalue_pair_iter, cause);
    f2ptr keyvalue_pair__key = f2cons__car(keyvalue_pair, cause);
    if (f2__symbol__eq(cause, key, keyvalue_pair__key)) {
      resume_gc(); return keyvalue_pair;
    }
    keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
  }
  resume_gc(); return nil;
}

f2ptr f2__hashtable__lookup_value(f2ptr this, f2ptr cause, f2ptr key) {
  debug__assert(raw__hashtable__valid(cause, this), nil, "f2__hashtable__lookup_value assert failed: f2__hashtable__valid(this)");
  pause_gc();
  f2ptr keyvalue_pair = f2__hashtable__lookup_keyvalue_pair(this, cause, key);
  if (keyvalue_pair) {
    f2ptr retval = f2cons__cdr(keyvalue_pair, cause);
    resume_gc(); return retval;
  }
  resume_gc(); return nil;
}




// end of object

void f2__primobject_hashtable__reinitialize_globalvars() {
  __hashtable__symbol = f2symbol__new(initial_cause(), strlen("hashtable"), (u8*)"hashtable");
}

void f2__primobject_hashtable__initialize() {
  pause_gc();
  f2__primobject_hashtable__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __hashtable__symbol, nil);
  
  resume_gc();
  try_gc();
}

