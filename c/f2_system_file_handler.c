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

#include "funk2.h"

// funk2_system_file_handle

void funk2_system_file_handle__init(funk2_system_file_handle_t* this, int fd) {
  funk2_processor_mutex__init(&(this->access_mutex));
  this->fd = fd;
}

void funk2_system_file_handle__destroy(funk2_system_file_handle_t* this) {
  funk2_processor_mutex__destroy(&(this->access_mutex));
}


// funk2_system_file_handler

void funk2_system_file_handler__init(funk2_system_file_handler_t* this) {
  funk2_hash__init(&(this->system_file_handle_fd_hash), 16); // 2^16 bins
}

void funk2_system_file_handler__destroy(funk2_system_file_handler_t* this) {
  funk2_hash__destroy(&(this->system_file_handle_fd_hash));
}


// **

void f2__system_file_handler__reinitialize_globalvars() {
}

void f2__system_file_handler__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "system_file_handler", "", &f2__system_file_handler__reinitialize_globalvars);
  
  f2__system_file_handler__reinitialize_globalvars();
  
}

