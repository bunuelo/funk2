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
  this->child_process_list = NULL;
}

void funk2_child_process_handler__destroy(funk2_child_process_handler_t* this) {
  funk2_child_process_list_t* iter = this->child_process_list;
  while (iter) {
    funk2_child_process_list_t* next          = iter->next;
    funk2_child_process_t*      child_process = &(iter->child_process);
    funk2_child_process__destroy(child_process);
    free(iter);
    iter = next;
  }
}

funk2_child_process_init_t funk2_child_process_handler__add_new_child_process(funk2_child_process_handler_t* this, char** argv, char** envp) {
  funk2_child_process_list_t* child_process_node = (funk2_child_process_list_t*)malloc(sizeof(funk2_child_process_list_t));
  funk2_child_process_init_t  result             = child_process__init(&(child_process_node->child_process), argv, envp);
  if (result != funk2_child_process_init__success) {
    free(child_process_node);
    return result;
  }
  child_process_node->next = this->child_process_list;
  this->child_process_list = child_process_node;
  return funk2_child_process_init__success;
}

void funk2_child_process_handler__handle_child_processes(funk2_child_process_handler_t* this) {
  funk2_child_process_list_t* iter;
  funk2_child_process_list_t* prev = NULL;
  funk2_child_process_list_t* next;
  while (iter) {
    next = iter->next;
    funk2_child_process_t* child_process = &(this->child_process);
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
}



