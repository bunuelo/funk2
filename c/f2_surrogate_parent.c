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

#include "funk2.h"

// funk2_pipe

void funk2_pipe__init(funk2_pipe_t* this) {
  int file_descriptors[2];
  if (pipe(file_descriptors) == -1) {
    perror("pipe");
    exit(1);
  }
  this->read_file_descriptor  = file_descriptors[0];
  this->write_file_descriptor = file_descriptors[1];
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

void funk2_pipe__read(funk2_pipe_t* this, void* data, f2size_t byte_count) {
  f2size_t bytes_read_count = read(this->read_file_descriptor, data, byte_count);
  if (bytes_read_count != byte_count) {
    const char* error_message = "funk2_pipe__read error: couldn't read data.";
    printf("\n%s\n", (char*)error_message);
    error(nil, (char*)error_message);
  }
}

// funk2_surrogate_parent

void funk2_surrogate_parent__init(funk2_surrogate_parent_t* this) {
  funk2_pipe__init(&(this->parent_to_child_pipe));
  funk2_pipe__init(&(this->child_to_parent_pipe));
}

void funk2_surrogate_parent__destroy(funk2_surrogate_parent_t* this) {
  funk2_pipe__destroy(&(this->parent_to_child_pipe));
  funk2_pipe__destroy(&(this->child_to_parent_pipe));
}

