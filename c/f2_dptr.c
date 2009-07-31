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

// struct dptr

void funk2_dptr__init(funk2_dptr_t* this, f2ptr p, f2ptr tracing_on, f2ptr trace, f2ptr imagination_frame) {
  this->p                 = p;
  this->tracing_on        = tracing_on;
  this->trace             = trace;
  this->imagination_frame = imagination_frame;
}

void funk2_dptr__check_all_memory_pointers_valid_in_memory(funk2_dptr_t* this, funk2_memory_t* memory) {
  funk2_memblock__check_valid_in_memory(this, __f2ptr_to_ptr(dptr->p));
  funk2_memblock__check_valid_in_memory(this, __f2ptr_to_ptr(dptr->tracing_on));
  funk2_memblock__check_valid_in_memory(this, __f2ptr_to_ptr(dptr->trace));
  funk2_memblock__check_valid_in_memory(this, __f2ptr_to_ptr(dptr->imagination_frame));
}



