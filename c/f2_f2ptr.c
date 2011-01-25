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

#include "f2_f2ptr.h"

void f2ptr__init(f2ptr_t* this, ip_addr_t ip_addr, pool_index_t pool_index, pool_offset_t pool_offset) {
  this->ip_addr     = ip_addr;
  this->pool_index  = pool_index;
  this->pool_offset = pool_offset;
}

f2ptr_t* f2ptr__new(ip_addr_t ip_addr, pool_index_t pool_index, pool_offset_t pool_offset) {
  f2ptr_t* this = (f2ptr_t*)f2__malloc(sizeof(f2ptr_t));
  f2ptr__init(this, ip_addr, pool_index, pool_offset);
  return this;
}

void f2ptr__delete(f2ptr_t* this) {
  f2__free(this);
}


