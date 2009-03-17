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

void error_writing_status_message() {
  // a debugging breakpoint
}

void funk2_status(char* filename, int line_num, char* msg, ...) {
  va_list args;
  char temp_msg[2048];
  va_start(args, msg);
  vsprintf(temp_msg, msg, args);
  va_end(args);
  pthread_mutex_lock(&(__funk2.status.trace_mutex));
  int trace_fd = open("/tmp/funk2_trace.log", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
  if (trace_fd == -1) {
    status("[WARNING] funk2_status couldn't open funk2_trace.log");
    return;
  }
  u64 microseconds_since_1970    = raw__system_microseconds_since_1970();
  u64 milliseconds_since_1970    = microseconds_since_1970 / 1000;
  u64 seconds_since_1970         = milliseconds_since_1970 / 1000;
  u64 minutes_since_1970         = seconds_since_1970      / 60;
  u64 hours_since_1970           = minutes_since_1970      / 60;
  u64 earth_rotations_since_1970 = hours_since_1970        / 24;
  u64 hours        = hours_since_1970        - (earth_rotations_since_1970 * 24);
  u64 minutes      = minutes_since_1970      - (hours_since_1970           * 60);
  u64 seconds      = seconds_since_1970      - (minutes_since_1970         * 60);
  u64 milliseconds = milliseconds_since_1970 - (seconds_since_1970         * 1000);
  u64 microseconds = microseconds_since_1970 - (milliseconds_since_1970    * 1000);
  char temp_msg2[2048];
  sprintf(temp_msg2, "\n[%-32s %5d] 0x%X_%02d_%02d_%02d.%03d,%03d funk2 status: %s", filename, line_num, (int)earth_rotations_since_1970, (int)hours, (int)minutes, (int)seconds, (int)milliseconds, (int)microseconds, temp_msg);
  size_t size_to_write = strlen(temp_msg2) + 1;
  size_t size_written  = write(trace_fd, temp_msg2, size_to_write);
  if (size_written != size_to_write) {
    error_writing_status_message();
  }
  close(trace_fd);
  pthread_mutex_unlock(&(__funk2.status.trace_mutex));
}

ssize_t raw__stream__writef(f2ptr cause, f2ptr stream, char* msg, ...) {
  va_list args;
  if (! raw__streamp(stream, cause)) {error(nil, "stream_writef error: stream is not stream.");}
  f2ptr file_descriptor = f2stream__file_descriptor(stream, cause);
  int fd = f2integer__i(file_descriptor, cause);
  int msg_len = strlen(msg);
  char* temp_msg = alloca(2048 + msg_len);
  va_start(args, msg);
  vsprintf(temp_msg, msg, args);
  va_end(args);
  return write(fd, temp_msg, strlen(temp_msg));
}

ssize_t writef(int fd, char* msg, ...) {
  va_list args;
  int msg_len = strlen(msg);
  char* temp_msg = alloca(2048 + msg_len);
  va_start(args, msg);
  vsprintf(temp_msg, msg, args);
  va_end(args);
  return write(fd, temp_msg, strlen(temp_msg));
}

// **

void f2__status__reinitialize_globalvars() {
  //f2ptr cause = f2_status_c__cause__new(initial_cause(), nil, nil);
  
}

void f2__status__initialize() {
  f2__status__reinitialize_globalvars();
  //f2ptr cause = f2_status_c__cause__new(initial_cause(), nil, nil);
  
  pthread_mutex_init(&(__funk2.status.trace_mutex), NULL);
}

void f2__status__destroy() {
  pthread_mutex_destroy(&(__funk2.status.trace_mutex));
}

