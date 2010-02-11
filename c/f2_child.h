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

#ifndef F2__CHILD__H
#define F2__CHILD__H

#include "f2_primfunks.h"

typedef struct funk2_child_process_s {
  char**    argv;
  char**    envp;
  pid_t     pid;
  boolean_t exited;
  boolean_t killed;
  boolean_t stopped;  
  boolean_t no_longer_exists;
} funk2_child_process_t;

typedef struct funk2_child_process_list_s {
  funk2_child_process_t              child_process;
  struct funk2_child_process_list_s* next;
} funk2_child_process_list_t;

typedef enum funk2_child_process_init_e {
  funk2_child_process_init__success,
  funk2_child_process_init__fork_failed
} funk2_child_process_init_t;

funk2_child_process_init_t funk2_child_process__init(        funk2_child_process_t* this, char** argv, char** envp);
void                       funk2_child_process__destroy(     funk2_child_process_t* this);
boolean_t                  funk2_child_process__is_completed(funk2_child_process_t* this);
void                       funk2_child_process__handle(      funk2_child_process_t* this);

#endif // F2__CHILD__H

