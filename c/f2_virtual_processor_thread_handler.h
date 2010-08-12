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

#ifndef F2__VIRTUAL_PROCESSOR_THREAD_HANDLER__H
#define F2__VIRTUAL_PROCESSOR_THREAD_HANDLER__H

#include "f2_virtual_processor_thread.h"

typedef struct funk2_virtual_processor_thread_handler_s funk2_virtual_processor_thread_handler_t;
struct funk2_virtual_processor_thread_handler_s {
  u64                                virtual_processor_thread_count;
  funk2_virtual_processor_thread_t** virtual_processor_thread;
};

void funk2_virtual_processor_thread_handler__init(   funk2_virtual_processor_thread_handler_t* this, u64 virtual_processor_thread_count);
void funk2_virtual_processor_thread_handler__destroy(funk2_virtual_processor_thread_handler_t* this);

#endif // F2__VIRTUAL_PROCESSOR_THREAD_HANDLER__H

