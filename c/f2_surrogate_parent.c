// 
// Copyright (c) 2007-2012 Bo Morgan.
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

void waitpid_reap_children() {
  waitpid(-1, NULL, WNOHANG);
  //int status;
  //pid_t wait_pid = waitpid(-1, &status, WNOHANG);
  //if (wait_pid != -1 && wait_pid != 0) {
  //pid_t this_pid = getpid();
  //printf("\nfunk2 pid = %d: wait_pid = %d, status = %d\n", (int)this_pid, (int)wait_pid, (int)status);
  //}
}

// funk2_pipe

void funk2_pipe__init(funk2_pipe_t* this, boolean_t nonblocking_read, boolean_t nonblocking_write) {
  int file_descriptors[2];
  if (pipe(file_descriptors) == -1) {
    perror("pipe");
    exit(1);
  }
  this->read_file_descriptor  = file_descriptors[0];
  this->write_file_descriptor = file_descriptors[1];
  file_descriptor__set_nonblocking(this->read_file_descriptor,  nonblocking_read);
  file_descriptor__set_nonblocking(this->write_file_descriptor, nonblocking_write);
}

void funk2_pipe__destroy(funk2_pipe_t* this) {
  close(this->read_file_descriptor);
  close(this->write_file_descriptor);
}

void funk2_pipe__write(funk2_pipe_t* this, void* data, f2size_t byte_count) {
  f2size_t bytes_written_count = write(this->write_file_descriptor, data, byte_count);
  if (bytes_written_count != byte_count) {
    const char* error_message = "funk2_pipe__write error: couldn't write data.";
    printf("\n%s\n", (char*)error_message);
    error(nil, (char*)error_message);
  }
}

f2size_t funk2_pipe__try_read(funk2_pipe_t* this, void* data, f2size_t byte_count) {
  f2size_t bytes_read_count = read(this->read_file_descriptor, data, byte_count);
  if (bytes_read_count == -1) {
    if (errno == EAGAIN) {
      return 0;
    } else {
      perror("read");
      error(nil, "funk2_pipe__try_read error.");
    }
  }
  return bytes_read_count;
}

void funk2_pipe__read(funk2_pipe_t* this, void* data, f2size_t byte_count) {
  f2size_t bytes_read_count = funk2_pipe__try_read(this, data, byte_count);
  if (bytes_read_count != byte_count) {
    const char* error_message = "funk2_pipe__read error: couldn't read data.";
    printf("\n%s\n", (char*)error_message);
    error(nil, (char*)error_message);
  }
}

// funk2_surrogate_parent

void funk2_surrogate_parent__init(funk2_surrogate_parent_t* this) {
  funk2_processor_mutex__init(&(this->write_to_child__mutex));
  funk2_pipe__init(&(this->parent_to_child_pipe), boolean__true, boolean__false);
  funk2_pipe__init(&(this->child_to_parent_pipe), boolean__true, boolean__false);
  
  pid_t surrogate_parent_pid = fork();
  if (surrogate_parent_pid == -1) {
    const char* error_message = "funk2_surrogate_parent__init error: couldn't read data.";
    printf("\n%s\n", (char*)error_message);
    perror("fork");
    error(nil, (char*)error_message);
  } else if (surrogate_parent_pid == 0) {
    u64 read_buffer__length = 128 * 1024;
    u8* read_buffer         = malloc(read_buffer__length);
    while (getppid() != 1) {
      waitpid_reap_children();
      f2ptr fiber;
      {
	u8 f2ptr_buffer[sizeof(f2ptr)];
	u64 bytes_in_buffer = 0;
	while (bytes_in_buffer < sizeof(f2ptr)) {
	  u64 bytes_read = funk2_pipe__try_read(&(this->parent_to_child_pipe), f2ptr_buffer + bytes_in_buffer, sizeof(f2ptr) - bytes_in_buffer);
	  bytes_in_buffer += bytes_read;
	  if (getppid() == 1) { // when parent has died, init takes over as parent.  init is process #1
	    exit(0);
	  }
	  if (bytes_in_buffer == 0) {
	    f2__nanosleep(100000);
	  }
	}
	memcpy(&fiber, f2ptr_buffer, sizeof(f2ptr));
      }
      u64 read_buffer__strlen;
      {
	u64 index;
	for (index = 0; index < (read_buffer__length - 1); index ++) {
	  u8 ch;
	  {
	    u8 ch_buffer[sizeof(u8)];
	    u64 bytes_in_buffer = 0;
	    while (bytes_in_buffer < sizeof(u8)) {
	      u64 bytes_read = funk2_pipe__try_read(&(this->parent_to_child_pipe), ch_buffer + bytes_in_buffer, sizeof(u8) - bytes_in_buffer);
	      bytes_in_buffer += bytes_read;
	      if (getppid() == 1) {
		exit(0);
	      }
	      if (bytes_in_buffer == 0) {
		f2__nanosleep(100000);
	      }
	    }
	    memcpy(&ch, ch_buffer, sizeof(u8));
	  }
	  if (ch == 0) {
	    break;
	  }
	  read_buffer[index] = ch;
	}
	read_buffer__strlen = index;
	read_buffer[read_buffer__strlen] = 0;
      }
      pid_t system_child_pid = fork();
      if (system_child_pid == -1) {
	const char* error_message = "funk2_surrogate_parent__init error: couldn't read data.";
	printf("\n%s\n", (char*)error_message);
	perror("fork");
	error(nil, (char*)error_message);
      } else if (system_child_pid == 0) {
	u64 return_value = system((char*)read_buffer);
	{
	  funk2_return_result_t result;
	  result.fiber       = fiber;
	  result.return_value = return_value;
	  funk2_pipe__write(&(this->child_to_parent_pipe), &result, sizeof(funk2_return_result_t));
	}
	exit(0);
      }
    }
    exit(0);
  }
  funk2_processor_mutex__init(&(this->return_values__mutex));
  this->return_values = NULL;
}

void funk2_surrogate_parent__destroy(funk2_surrogate_parent_t* this) {
  funk2_processor_mutex__destroy(&(this->write_to_child__mutex));
  funk2_pipe__destroy(&(this->parent_to_child_pipe));
  funk2_pipe__destroy(&(this->child_to_parent_pipe));
  funk2_processor_mutex__destroy(&(this->return_values__mutex));
}

void funk2_surrogate_parent__unsafe_start_system_command(funk2_surrogate_parent_t* this, f2ptr fiber, u8* command) {
  funk2_pipe__write(&(this->parent_to_child_pipe), &fiber, sizeof(f2ptr));
  funk2_pipe__write(&(this->parent_to_child_pipe), command, strlen((char*)command) + 1);
}

void funk2_surrogate_parent__management_start_system_command(funk2_surrogate_parent_t* this, f2ptr fiber, u8* command) {
  funk2_processor_mutex__lock(&(this->write_to_child__mutex));
  funk2_surrogate_parent__unsafe_start_system_command(this, fiber, command);
  funk2_processor_mutex__unlock(&(this->write_to_child__mutex));
}

void funk2_surrogate_parent__user_start_system_command(funk2_surrogate_parent_t* this, f2ptr fiber, u8* command) {
  funk2_processor_mutex__user_lock(&(this->write_to_child__mutex));
  funk2_surrogate_parent__unsafe_start_system_command(this, fiber, command);
  funk2_processor_mutex__unlock(&(this->write_to_child__mutex));
}

void funk2_surrogate_parent__handle(funk2_surrogate_parent_t* this) {
  waitpid_reap_children();
  u64 read_byte_num = 0;
  do {
    u8  buffer[sizeof(funk2_return_result_t)];
    u64 bytes_available = funk2_pipe__try_read(&(this->child_to_parent_pipe), buffer + read_byte_num, sizeof(funk2_return_result_t) - read_byte_num);
    read_byte_num += bytes_available;
    if (read_byte_num == sizeof(funk2_return_result_t)) {
      funk2_return_result_t result;
      memcpy(&result, buffer, sizeof(funk2_return_result_t));
      funk2_processor_mutex__lock(&(this->return_values__mutex));
      {
	funk2_return_value_node_t* new_node = (funk2_return_value_node_t*)malloc(sizeof(funk2_return_value_node_t));
	memcpy(&(new_node->result), &result, sizeof(funk2_return_result_t));
	new_node->next = this->return_values;
	this->return_values = new_node;
      }
      funk2_processor_mutex__unlock(&(this->return_values__mutex));
    }
  } while ((read_byte_num > 0) && (read_byte_num < sizeof(u64)));
}

boolean_t funk2_surrogate_parent__unsafe_check_return_value(funk2_surrogate_parent_t* this, f2ptr fiber, funk2_return_result_t* result) {
  boolean_t return_value_available = boolean__false;
  funk2_return_value_node_t* prev = NULL;
  funk2_return_value_node_t* iter = this->return_values;
  while (iter) {
    funk2_return_value_node_t* next        = iter->next;
    funk2_return_result_t*     iter_result = &(iter->result);
    if (iter_result->fiber == fiber) {
      memcpy(result, iter_result, sizeof(funk2_return_result_t));
      return_value_available = boolean__true;
      if (prev) {
	prev->next = iter->next;
      } else {
	this->return_values = iter->next;
      }
      free(iter);
    }
    prev = iter;
    iter = next;
  }
  return return_value_available;
}

boolean_t funk2_surrogate_parent__management_check_return_value(funk2_surrogate_parent_t* this, f2ptr fiber, funk2_return_result_t* result) {
  boolean_t return_value_available = boolean__false;
  funk2_processor_mutex__lock(&(this->return_values__mutex));
  return_value_available = funk2_surrogate_parent__unsafe_check_return_value(this, fiber, result);
  funk2_processor_mutex__unlock(&(this->return_values__mutex));
  return return_value_available;
}

boolean_t funk2_surrogate_parent__user_check_return_value(funk2_surrogate_parent_t* this, f2ptr fiber, funk2_return_result_t* result) {
  boolean_t return_value_available = boolean__false;
  funk2_processor_mutex__user_lock(&(this->return_values__mutex));
  return_value_available = funk2_surrogate_parent__unsafe_check_return_value(this, fiber, result);
  funk2_processor_mutex__unlock(&(this->return_values__mutex));
  return return_value_available;
}

void raw__surrogate_parent__start_system_command(f2ptr cause, u8* command) {
  f2ptr fiber = f2__this__fiber(cause);
  funk2_surrogate_parent__user_start_system_command(&(__funk2.surrogate_parent), fiber, command);
}

f2ptr f2__surrogate_parent__start_system_command(f2ptr cause, f2ptr command) {
  assert_argument_type(string, command);
  u64 command__utf8_length = raw__string__utf8_length(cause, command);
  u8* command__utf8_str    = alloca(command__utf8_length + 1);
  raw__string__utf8_str_copy(cause, command, command__utf8_str);
  command__utf8_str[command__utf8_length] = 0;
  raw__surrogate_parent__start_system_command(cause, command__utf8_str);
  return nil;
}
def_pcfunk1(surrogate_parent__start_system_command, command,
	    "executes a system command as a new process.returns a new conslist that is this conslist sorted by user-provided comparison_funk.",
	    return f2__surrogate_parent__start_system_command(this_cause, command));

f2ptr f2__surrogate_parent__check_return_value(f2ptr cause) {
  f2ptr fiber = f2__this__fiber(cause);
  funk2_return_result_t result;
  boolean_t return_value_available = funk2_surrogate_parent__user_check_return_value(&(__funk2.surrogate_parent), fiber, &result);
  if (return_value_available) {
    return f2integer__new(cause, result.return_value);
  }
  return nil;
}
def_pcfunk0(surrogate_parent__check_return_value,
	    "checks for the return value for a finished system command started by this fiber.",
	    return f2__surrogate_parent__check_return_value(this_cause));

// **

void f2__surrogate_parent__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(surrogate_parent__start_system_command);
  f2__primcfunk__init__defragment__fix_pointers(surrogate_parent__check_return_value);
}

void f2__surrogate_parent__reinitialize_globalvars() {
  f2__primcfunk__init__1(surrogate_parent__start_system_command, command);
  f2__primcfunk__init__0(surrogate_parent__check_return_value);
}

void f2__surrogate_parent__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "surrogate_parent", "", &f2__surrogate_parent__reinitialize_globalvars, &f2__surrogate_parent__defragment__fix_pointers);
  
  f2__surrogate_parent__reinitialize_globalvars();
}

