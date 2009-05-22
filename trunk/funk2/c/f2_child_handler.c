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

void funk2_child_process_handler__init(funk2_child_process_handler_t* this) {
  pthread_mutex_init(&(this->access_mutex), NULL);
  this->child_process_list = NULL;
}

void funk2_child_process_handler__destroy(funk2_child_process_handler_t* this) {
  pthread_mutex_lock(&(this->access_mutex));
  pthread_mutex_destroy(&(this->access_mutex));
  funk2_child_process_list_t* iter = this->child_process_list;
  while (iter) {
    funk2_child_process_list_t* next          = iter->next;
    funk2_child_process_t*      child_process = &(iter->child_process);
    funk2_child_process__destroy(child_process);
    free(iter);
    iter = next;
  }
}

pid_t funk2_child_process_handler__add_new_child_process(funk2_child_process_handler_t* this, char** argv, char** envp) {
  pthread_mutex_lock(&(this->access_mutex));
  funk2_child_process_list_t* child_process_node = (funk2_child_process_list_t*)malloc(sizeof(funk2_child_process_list_t));
  funk2_child_process_init_t  result             = funk2_child_process__init(&(child_process_node->child_process), argv, envp);
  if (result != funk2_child_process_init__success) {
    free(child_process_node);
    pthread_mutex_unlock(&(this->access_mutex));
    return 0;
  }
  child_process_node->next = this->child_process_list;
  this->child_process_list = child_process_node;
  pthread_mutex_unlock(&(this->access_mutex));
  return child_process_node->child_process.pid;
}

void funk2_child_process_handler__handle_child_processes(funk2_child_process_handler_t* this) {
  pthread_mutex_lock(&(this->access_mutex));
  funk2_child_process_list_t* iter = this->child_process_list;
  funk2_child_process_list_t* prev = NULL;
  funk2_child_process_list_t* next;
  while (iter) {
    next = iter->next;
    funk2_child_process_t* child_process = &(iter->child_process);
    funk2_child_process__handle(child_process);
    if (funk2_child_process__is_completed(child_process)) {
      if (prev) {
	prev->next = iter->next;
      } else {
	this->child_process_list = iter->next;
      }
      free(iter);
    } else {
      prev = iter;
    }
    iter = next;
  }
  pthread_mutex_unlock(&(this->access_mutex));
}



f2ptr f2__child_handler__add_new_child_process(f2ptr cause, f2ptr argv, f2ptr envp) {
  u64 argv__length = raw__length(cause, argv);
  u64 envp__length = raw__length(cause, envp);
  
  char** raw_argv;
  {
    raw_argv = (char**)alloca(sizeof(char*) * (argv__length + 1));
    u64 index;
    for (index = 0; index < argv__length; index ++) {
      f2ptr elt = raw__elt(cause, argv, index);
      if (! raw__stringp(elt, cause)) {
	printf("\nchild_handler-add_new_child_process error: argv must contain only strings.\n");
	return f2larva__new(cause, 1);
      }
      u64 elt__length = f2string__length(elt, cause);
      raw_argv[index] = (char*)alloca(elt__length + 1);
      f2string__str_copy(elt, cause, raw_argv[index]);
      raw_argv[index][elt__length] = 0;
    }
    raw_argv[index] = NULL;
  }
  char** raw_envp;
  {
    raw_envp = (char**)alloca(sizeof(char*) * (envp__length + 1));
    u64 index;
    for (index = 0; index < envp__length; index ++) {
      f2ptr elt = raw__elt(cause, envp, index);
      if (! raw__stringp(elt, cause)) {
	printf("\nchild_handler-add_new_child_process error: envp must contain only strings.\n");
	return f2larva__new(cause, 1);
      }
      u64 elt__length = f2string__length(elt, cause);
      raw_envp[index] = (char*)alloca(elt__length + 1);
      f2string__str_copy(elt, cause, raw_envp[index]);
      raw_envp[index][elt__length] = 0;
    }
    raw_envp[index] = NULL;
  }
  pid_t pid = funk2_child_process_handler__add_new_child_process(&(__funk2.child_handler), raw_argv, raw_envp);
  f2ptr result = nil;
  if (pid != 0) {
    result = f2integer__new(cause, pid);
  }
  return result;
}
def_pcfunk2(child_handler__add_new_child_process, argv, envp, return f2__child_handler__add_new_child_process(this_cause, argv, envp));

// **

void f2__child_handler__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_child_handler_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__child_handler__initialize() {
  //f2ptr cause = initial_cause(); //f2_child_handler_c__cause__new(initial_cause(), nil, global_environment());
  pause_gc();
  
  f2__child_handler__reinitialize_globalvars();
  
  f2__primcfunk__init(child_handler__add_new_child_process);
  
  resume_gc();
  try_gc();
}


