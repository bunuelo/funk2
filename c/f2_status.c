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

void error_writing_status_message() {
  // a debugging breakpoint
}

boolean_t __funk2_status_disabled = boolean__false;

void funk2_status(char* filename, int line_num, char* msg, ...) {
  va_list args;
  if (__funk2_status_disabled) {
    return;
  }
  char temp_msg[2048];
  va_start(args, msg);
  vsprintf(temp_msg, msg, args);
  va_end(args);
  funk2_processor_mutex__lock(&(__funk2.status.trace_mutex));
  int trace_fd = open("funk2_debug.log", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
  if (trace_fd == -1) {
    __funk2_status_disabled = boolean__true;
    //printf("[WARNING] funk2_status couldn't open funk2_trace.log");
    funk2_processor_mutex__unlock(&(__funk2.status.trace_mutex));
    return;
  }
  pthread_t self_thread = pthread_self();
  u64 nanoseconds_since_1970     = raw__nanoseconds_since_1970();
  u64 seconds_since_1970         = nanoseconds_since_1970 / nanoseconds_per_second;
  u64 minutes_since_1970         = seconds_since_1970     / 60;
  u64 hours_since_1970           = minutes_since_1970     / 60;
  u64 earth_rotations_since_1970 = hours_since_1970       / 24;
  u64 hours        = hours_since_1970        - (earth_rotations_since_1970 * 24);
  u64 minutes      = minutes_since_1970      - (hours_since_1970           * 60);
  u64 seconds      = seconds_since_1970      - (minutes_since_1970         * 60);
  u64 nanoseconds  = nanoseconds_since_1970  - (seconds_since_1970         * nanoseconds_per_second);
  char temp_msg2[2048];
  sprintf(temp_msg2, "\n[%-40s %5d] tid=0x" "%-16" x64__fstr_without_percent " 0x%X_%02d_%02d_%02d." nano_decimal_fraction__fstr " funk2 status: %s", filename, line_num, (u64)to_ptr(self_thread), (int)earth_rotations_since_1970, (int)hours, (int)minutes, (int)seconds, (u64)nanoseconds, temp_msg);
  size_t size_to_write = strlen(temp_msg2) + 1;
  size_t size_written  = write(trace_fd, temp_msg2, size_to_write);
  if (size_written != size_to_write) {
    error_writing_status_message();
  }
  close(trace_fd);
  funk2_processor_mutex__unlock(&(__funk2.status.trace_mutex));
}

ssize_t raw__stream__writef(f2ptr cause, f2ptr stream, char* msg, ...) {
  va_list args;
  if (! raw__stream__is_type(cause, stream)) {error(nil, "stream_writef error: stream is not stream.");}
  f2ptr file_handle = f2stream__file_handle(stream, cause);
  int msg_len = strlen(msg);
  u8* temp_msg = (u8*)alloca(2048 + msg_len);
  va_start(args, msg);
  vsprintf((char*)temp_msg, msg, args);
  va_end(args);
  if (raw__file_stream__is_type(cause, stream)) {
    return raw__file_handle__write(cause, file_handle, strlen((char*)temp_msg), temp_msg);
  } else if (raw__socket_stream__is_type(cause, stream)) {
    return raw__file_handle__send(cause, file_handle, strlen((char*)temp_msg), temp_msg);
  } else {
    return -1;
  }
}

ssize_t raw__stream__write_character(f2ptr cause, f2ptr stream, funk2_character_t ch) {
  if (! raw__stream__is_type(cause, stream)) {error(nil, "stream_writef error: stream is not stream.");}
  f2ptr file_handle = f2stream__file_handle(stream, cause);
  int temp_msg__length;
  u8  temp_msg[6];
  if (ch <= 0x7f) {
    temp_msg__length = 1;
    temp_msg[0]      = ch;
  } else if (ch <= 0x07ff) {
    temp_msg__length = 2;
    temp_msg[0]      = 0xc0 + (0x1f & (ch >> 6));
    temp_msg[1]      = 0x80 + (0x3f & ch);
  } else if (ch <= 0xffff) {
    temp_msg__length = 3;
    temp_msg[0]      = 0xe0 + (0x0f & (ch >> 12));
    temp_msg[1]      = 0x80 + (0x3f & (ch >> 6));
    temp_msg[2]      = 0x80 + (0x3f & ch);
  } else if (ch <= 0x1fffff) {
    temp_msg__length = 4;
    temp_msg[0]      = 0xf0 + (0x07 & (ch >> 18));
    temp_msg[1]      = 0x80 + (0x3f & (ch >> 12));
    temp_msg[2]      = 0x80 + (0x3f & (ch >> 6));
    temp_msg[3]      = 0x80 + (0x3f & ch);
  } else if (ch <= 0x3ffffff) {
    temp_msg__length = 5;
    temp_msg[0]      = 0xf7 + (0x03 & (ch >> 24));
    temp_msg[1]      = 0x80 + (0x3f & (ch >> 18));
    temp_msg[2]      = 0x80 + (0x3f & (ch >> 12));
    temp_msg[3]      = 0x80 + (0x3f & (ch >> 6));
    temp_msg[4]      = 0x80 + (0x3f & ch);
  } else if (ch <= 0x7fffffff) {
    temp_msg__length = 6;
    temp_msg[0]      = 0xfc + (0x01 & (ch >> 30));
    temp_msg[1]      = 0x80 + (0x3f & (ch >> 24));
    temp_msg[2]      = 0x80 + (0x3f & (ch >> 18));
    temp_msg[3]      = 0x80 + (0x3f & (ch >> 12));
    temp_msg[4]      = 0x80 + (0x3f & (ch >> 6));
    temp_msg[5]      = 0x80 + (0x3f & ch);
  } else {
    temp_msg__length = 1;
    temp_msg[0]      = (u8)'?';
  }
  if (raw__file_stream__is_type(cause, stream)) {
    return raw__file_handle__write(cause, file_handle, temp_msg__length, temp_msg);
  } else if (raw__socket_stream__is_type(cause, stream)) {
    return raw__file_handle__send(cause, file_handle, temp_msg__length, temp_msg);
  } else {
    return -1;
  }
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
  
  funk2_processor_mutex__init(&(__funk2.status.trace_mutex));
}

void f2__status__destroy() {
  funk2_processor_mutex__destroy(&(__funk2.status.trace_mutex));
}

