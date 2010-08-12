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

#ifndef F2__VIRTUAL_PROCESSOR_THREAD__H
#define F2__VIRTUAL_PROCESSOR_THREAD__H

typedef struct funk2_processor_thread_array_s funk2_processor_thread_array_t;
struct funk2_processor_thread_array_s {
  u64                       alloc_length;
  u64                       length;
  funk2_processor_thread_t* array;
};

void funk2_processor_thread_array__init(   funk2_processor_thread_array_t* this);
void funk2_processor_thread_array__destroy(funk2_processor_thread_array_t* this);


typedef struct funk2_virtual_processor_thread_s funk2_virtual_processor_thread_t;
struct funk2_virtual_processor_thread_s {
  funk2_processor_thread_array_t processor_thread_array;
};

void funk2_virtual_processor_thread__init(   funk2_virtual_processor_thread_t* this);
void funk2_virtual_processor_thread__destroy(funk2_virtual_processor_thread_t* this);

#endif // F2__VIRTUAL_PROCESSOR_THREAD__H

