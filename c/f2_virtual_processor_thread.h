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

typedef struct funk2_virtual_processor_thread_s funk2_virtual_processor_thread_t;
struct funk2_virtual_processor_thread_s {
  funk2_processor_mutex_t                   command_mutex;
  boolean_t                                 command_ready;
  funk2_processor_thread_function_pointer_t command_start_function;
  void*                                     command_args;
  funk2_processor_thread_t*                 processor_thread;
};



#endif // F2__VIRTUAL_PROCESSOR_THREAD__H

