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

#ifndef F2__CHILD_HANDLER__H
#define F2__CHILD_HANDLER__H

#include "f2_primfunks.h"
#include "f2_child.h"

typedef struct funk2_child_process_handler_s {
  funk2_processor_mutex_t     access_mutex;
  funk2_child_process_list_t* child_process_list;
} funk2_child_process_handler_t;

void  funk2_child_process_handler__init(funk2_child_process_handler_t* this);
void  funk2_child_process_handler__destroy(funk2_child_process_handler_t* this);
pid_t funk2_child_process_handler__add_new_child_process(funk2_child_process_handler_t* this, char** argv, char** envp);
void  funk2_child_process_handler__handle_child_processes(funk2_child_process_handler_t* this);

// **

void f2__child_handler__reinitialize_globalvars();
void f2__child_handler__initialize();

#endif // F2__CHILD_HANDLER__H

