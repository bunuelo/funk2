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

// management_thread_command__save_memory_image

funk2_management_thread_command__save_memory_image_t* funk2_management_thread_command__save_memory_image__new(u8* filename) {
  u64 filename__length = strlen((char*)filename);
  funk2_management_thread_command__save_memory_image_t* this = (funk2_management_thread_command__save_memory_image_t*)f2__malloc(sizeof(funk2_management_thread_command__save_memory_image_t) + filename__length + 1);
  this->header.type      = funk2_management_thread_command_type__save_memory_image;
  this->filename__length = filename__length;
  strcpy((char*)this->filename, (char*)filename);
  return this;
}

void funk2_management_thread_command__save_memory_image__execute(funk2_management_thread_command__save_memory_image_t* this) {
  funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait(&(__funk2.scheduler_thread_controller));
  
  this->result = boolean__false;
  funk2_scheduler_thread_controller__let_scheduler_threads_continue(&(__funk2.scheduler_thread_controller));
}

// management_thread_command__load_memory_image

funk2_management_thread_command__load_memory_image_t* funk2_management_thread_command__load_memory_image__new(u8* filename) {
  u64 filename__length = strlen((char*)filename);
  funk2_management_thread_command__load_memory_image_t* this = (funk2_management_thread_command__load_memory_image_t*)f2__malloc(sizeof(funk2_management_thread_command__load_memory_image_t) + filename__length + 1);
  this->header.type      = funk2_management_thread_command_type__load_memory_image;
  this->filename__length = filename__length;
  strcpy((char*)this->filename, (char*)filename);
  return this;
}

void funk2_management_thread_command__load_memory_image__execute(funk2_management_thread_command__load_memory_image_t* this) {
  funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait(&(__funk2.scheduler_thread_controller));
  
  this->result = boolean__false;
  funk2_scheduler_thread_controller__let_scheduler_threads_continue(&(__funk2.scheduler_thread_controller));
}

// management_thread_command__exit

funk2_management_thread_command__exit_t* funk2_management_thread_command__exit__new(s64 value) {
  funk2_management_thread_command__exit_t* this = (funk2_management_thread_command__exit_t*)f2__malloc(sizeof(funk2_management_thread_command__exit_t));
  this->header.type = funk2_management_thread_command_type__exit;
  this->value       = value;
  return this;
}

void funk2_management_thread_command__exit__execute(funk2_management_thread_command__exit_t* this) {
  funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait(&(__funk2.scheduler_thread_controller));
  
  // exit(this->value);
  funk2_scheduler_thread_controller__let_scheduler_threads_continue(&(__funk2.scheduler_thread_controller));
}

// management_thread

void funk2_management_thread__init(funk2_management_thread_t* this) {
  funk2_processor_mutex__init(&(this->next_uid__mutex));
  this->next_uid = 0;
  funk2_processor_mutex__init(&(this->command_list__mutex));
  this->command_list__first = NULL;
  this->command_list__last  = NULL;
  funk2_processor_mutex__init(&(this->finished_command_list__mutex));
}

void funk2_management_thread__destroy(funk2_management_thread_t* this) {
  funk2_processor_mutex__destroy(&(this->next_uid__mutex));
  funk2_processor_mutex__destroy(&(this->command_list__mutex));
  funk2_processor_mutex__destroy(&(this->finished_command_list__mutex));
  {
    funk2_management_thread_command_node_t* iter = this->command_list__first;
    while (iter) {
      funk2_management_thread_command_node_t* next = iter->next;
      free(iter->command);
      free(iter);
      iter = next;
    }
  }
  {
    funk2_management_thread_command_node_t* iter = this->finished_command_list;
    while (iter) {
      funk2_management_thread_command_node_t* next = iter->next;
      free(iter->command);
      free(iter);
      iter = next;
    }
  }
}

u64 funk2_management_thread__new_uid(funk2_management_thread_t* this) {
  u64 new_uid;
  funk2_processor_mutex__lock(&(this->next_uid__mutex));
  new_uid = this->next_uid;
  this->next_uid ++;
  funk2_processor_mutex__unlock(&(this->next_uid__mutex));
  return new_uid;
}

void funk2_management_thread__add_command_node_to_command_list(funk2_management_thread_t* this, funk2_management_thread_command_node_t* node) {
  node->next = NULL;
  funk2_processor_mutex__lock(&(this->command_list__mutex));
  if (this->command_list__last) {
    this->command_list__last->next = node;
  } else {
    this->command_list__first = node;
    this->command_list__last  = node;
  }
  funk2_processor_mutex__unlock(&(this->command_list__mutex));
}

u64 funk2_management_thread__add_command(funk2_management_thread_t* this, funk2_management_thread_command_t* command) {
  funk2_management_thread_command_node_t* new_node = (funk2_management_thread_command_node_t*)f2__malloc(sizeof(funk2_management_thread_command_node_t));
  command->header.uid = funk2_management_thread__new_uid(this);
  new_node->command = command;
  funk2_management_thread__add_command_node_to_command_list(this, new_node);
  return command->header.uid;
}

boolean_t funk2_management_thread__command_list__is_empty(funk2_management_thread_t* this) {
  boolean_t is_empty = boolean__false;
  funk2_processor_mutex__lock(&(this->command_list__mutex));
  if (! this->command_list__first) {
    is_empty = boolean__true;
  }
  funk2_processor_mutex__unlock(&(this->command_list__mutex));
  return is_empty;
}

funk2_management_thread_command_t* funk2_management_thread__pop_command(funk2_management_thread_t* this) {
  debug__assert(this->command_list__first, nil, "command list is empty.");
  funk2_processor_mutex__lock(&(this->command_list__mutex));
  funk2_management_thread_command_node_t* node = this->command_list__first;
  this->command_list__first = node->next;
  if (! this->command_list__first) {
    this->command_list__last = NULL;
  }
  funk2_processor_mutex__unlock(&(this->command_list__mutex));
  funk2_management_thread_command_t* command = node->command;
  free(node);
  return command;
}

u64 funk2_management_thread__add_save_memory_image_command(funk2_management_thread_t* this, u8* filename) {
  return funk2_management_thread__add_command(this, (funk2_management_thread_command_t*)funk2_management_thread_command__save_memory_image__new(filename));
}

u64 funk2_management_thread__add_load_memory_image_command(funk2_management_thread_t* this, u8* filename) {
  return funk2_management_thread__add_command(this, (funk2_management_thread_command_t*)funk2_management_thread_command__load_memory_image__new(filename));
}

u64 funk2_management_thread__add_exit_command(funk2_management_thread_t* this, s64 value) {
  return funk2_management_thread__add_command(this, (funk2_management_thread_command_t*)funk2_management_thread_command__exit__new(value));
}

void funk2_management_thread__add_command_node_to_finished_command_list(funk2_management_thread_t* this, funk2_management_thread_command_node_t* node) {
  funk2_processor_mutex__lock(&(this->finished_command_list__mutex));
  node->next    = this->finished_command_list;
  this->finished_command_list = node;
  funk2_processor_mutex__unlock(&(this->finished_command_list__mutex));
}

void funk2_management_thread__command_finished(funk2_management_thread_t* this, funk2_management_thread_command_t* command) {
  funk2_management_thread_command_node_t* new_node = (funk2_management_thread_command_node_t*)f2__malloc(sizeof(funk2_management_thread_command_node_t));
  new_node->command = command;
  funk2_management_thread__add_command_node_to_finished_command_list(this, new_node);
}

void funk2_management_thread__handle_user_threads(funk2_management_thread_t* this) {
  while (! funk2_management_thread__command_list__is_empty(this)) {
    funk2_management_thread_command_t* command = funk2_management_thread__pop_command(this);
    switch (command->header.type) {
    case funk2_management_thread_command_type__save_memory_image: funk2_management_thread_command__save_memory_image__execute((funk2_management_thread_command__save_memory_image_t*)command); break;
    case funk2_management_thread_command_type__load_memory_image: funk2_management_thread_command__load_memory_image__execute((funk2_management_thread_command__load_memory_image_t*)command); break;
    case funk2_management_thread_command_type__exit:              funk2_management_thread_command__exit__execute(             (funk2_management_thread_command__exit_t*)             command); break;
    }
    funk2_management_thread__command_finished(this, command);
  }
}

boolean_t funk2_management_thread__check_command_uid_finished(funk2_management_thread_t* this, u64 uid, void* user_result) {
  boolean_t found_uid = boolean__false;
  funk2_processor_mutex__lock(&(this->finished_command_list__mutex));
  funk2_management_thread_command_node_t* prev = NULL;
  funk2_management_thread_command_node_t* iter = this->finished_command_list;
  while (iter) {
    funk2_management_thread_command_node_t* next = iter->next;
    funk2_management_thread_command_t* command = iter->command;
    if (command->header.uid == uid) {
      if (user_result) {
	switch(command->header.type) {
	case funk2_management_thread_command_type__save_memory_image: {
	  funk2_management_thread_command__save_memory_image_t* save_command = (funk2_management_thread_command__save_memory_image_t*)command;
	  *((boolean_t*)user_result) = save_command->result;
	} break;
	case funk2_management_thread_command_type__load_memory_image: {
	  funk2_management_thread_command__load_memory_image_t* load_command = (funk2_management_thread_command__load_memory_image_t*)command;
	  *((boolean_t*)user_result) = load_command->result;
	} break;
	case funk2_management_thread_command_type__exit: {
	  //funk2_management_thread_command__exit_t* exit_command = (funk2_management_thread_command__exit_t*)command;
	  *((boolean_t*)user_result) = boolean__false;
	} break;
	}
      }
      if (prev) {
	prev->next = next;
      } else {
	this->finished_command_list = next;
      }
      free(iter->command);
      free(iter);
      found_uid = boolean__true;
      break;
    }
    prev = iter;
    iter = next;
  }
  funk2_processor_mutex__unlock(&(this->finished_command_list__mutex));
  return found_uid;
}

// --

u64  raw__management_thread__add_save_memory_image_command(u8* filename) {return funk2_management_thread__add_save_memory_image_command(&(__funk2.management_thread), filename);}
f2ptr f2__management_thread__add_save_memory_image_command(f2ptr cause, f2ptr filename) {
  if (! raw__string__is_type(cause, filename)) {
    return f2larva__new(cause, 1);
  }
  u64 filename__length = f2string__length(filename, cause);
  u8* raw_filename = (u8*)alloca(filename__length + 1);
  f2string__str_copy(filename, cause, raw_filename);
  raw_filename[filename__length] = 0;
  f2ptr uid = f2integer__new(cause, raw__management_thread__add_save_memory_image_command(raw_filename));
  return uid;
}
def_pcfunk1(management_thread__add_save_memory_image_command, filename, return f2__management_thread__add_save_memory_image_command(this_cause, filename));

u64  raw__management_thread__add_load_memory_image_command(u8* filename) {return funk2_management_thread__add_load_memory_image_command(&(__funk2.management_thread), filename);}
f2ptr f2__management_thread__add_load_memory_image_command(f2ptr cause, f2ptr filename) {
  if (! raw__string__is_type(cause, filename)) {
    return f2larva__new(cause, 1);
  }
  u64 filename__length = f2string__length(filename, cause);
  u8* raw_filename = (u8*)alloca(filename__length + 1);
  f2string__str_copy(filename, cause, raw_filename);
  raw_filename[filename__length] = 0;
  f2ptr uid = f2integer__new(cause, raw__management_thread__add_load_memory_image_command(raw_filename));
  return uid;
}
def_pcfunk1(management_thread__add_load_memory_image_command, filename, return f2__management_thread__add_load_memory_image_command(this_cause, filename));

u64  raw__management_thread__add_exit_command(s64 value) {return funk2_management_thread__add_exit_command(&(__funk2.management_thread), value);}
f2ptr f2__management_thread__add_exit_command(f2ptr cause, f2ptr value) {
  if (! raw__integer__is_type(cause, value)) {
    return f2larva__new(cause, 1);
  }
  f2ptr uid = f2integer__new(cause, raw__management_thread__add_exit_command(f2integer__i(value, cause)));
  return uid;
}
def_pcfunk1(management_thread__add_exit_command, value, return f2__management_thread__add_exit_command(this_cause, value));

boolean_t raw__management_thread__check_command_uid_finished(u64 uid, void* user_result) {return funk2_management_thread__check_command_uid_finished(&(__funk2.management_thread), uid, user_result);}
f2ptr      f2__management_thread__check_command_uid_finished(f2ptr cause, f2ptr uid, f2ptr user_result_place) {
  if ((! raw__integer__is_type(cause, uid)) ||
      (user_result_place && (! raw__place__is_type(cause, user_result_place)))) {
    return f2larva__new(cause, 1);
  }
  u64 raw_uid = (u64)f2integer__i(uid, cause);
  boolean_t result;
  boolean_t is_finished = raw__management_thread__check_command_uid_finished(raw_uid, &result);
  if (user_result_place) {
    f2place__thing__set(user_result_place, cause, f2bool__new(result));
  }
  return f2bool__new(is_finished);
}
def_pcfunk2(management_thread__check_command_uid_finished, uid, user_result_place, return f2__management_thread__check_command_uid_finished(this_cause, uid, user_result_place));

// **

void f2__management_thread__reinitialize_globalvars() {
}

void f2__management_thread__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "management_thread", "", &f2__management_thread__reinitialize_globalvars);
  
  f2__management_thread__reinitialize_globalvars();
  
  f2__primcfunk__init__1(management_thread__add_save_memory_image_command, filename,               "add save command to management thread command list.");
  f2__primcfunk__init__1(management_thread__add_load_memory_image_command, filename,               "add load command to management thread command list.");
  f2__primcfunk__init__1(management_thread__add_exit_command,              value,                  "add exit command to management thread command list.");
  f2__primcfunk__init__2(management_thread__check_command_uid_finished,    uid, user_result_place, "check to see if a management thread command has finished.");
}

