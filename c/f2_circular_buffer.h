// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#ifndef F2__CIRCULAR_BUFFER__H
#define F2__CIRCULAR_BUFFER__H

#include "f2_global.h"

typedef struct circular_buffer_s {
  u32 byte_num;
  u32 start;
  u32 end;
  u8* bytes;
} circular_buffer_t;

typedef enum circular_buffer__seek_ahead_result_e {
  circular_buffer__seek_ahead_result__success = 0,
  circular_buffer__seek_ahead_result__not_enough_data
} circular_buffer__seek_ahead_result_t;

typedef enum circular_buffer__read_result_e {
  circular_buffer__read_result__success = 0,
  circular_buffer__read_result__not_enough_data
} circular_buffer__read_result_t;

typedef enum circular_buffer__write_result_e {
  circular_buffer__write_result__success = 0,
  circular_buffer__write_result__not_enough_room
} circular_buffer__write_result_t;

typedef enum circular_buffer__socket_recv_result_e {
  circular_buffer__socket_recv_result__connected = 0,
  circular_buffer__socket_recv_result__disconnected
} circular_buffer__socket_recv_result_t;

typedef enum circular_buffer__socket_send_result_e {
  circular_buffer__socket_send_result__connected = 0,
  circular_buffer__socket_send_result__disconnected
} circular_buffer__socket_send_result_t;

typedef enum circular_buffer__file_read_result_e {
  circular_buffer__file_read_result__success = 0,
  circular_buffer__file_read_result__end_of_file
} circular_buffer__file_read_result_t;

typedef enum circular_buffer__file_write_result_e {
  circular_buffer__file_write_result__success = 0,
  circular_buffer__file_write_result__end_of_file
} circular_buffer__file_write_result_t;

typedef enum read_nonblocking_result_e {
  read_nonblocking_result__success = 0,
  read_nonblocking_result__end_of_file,
  read_nonblocking_result__read_failure,
  read_nonblocking_result__select_failure,
  read_nonblocking_result__unknown_failure,
} read_nonblocking_result_t;

typedef enum write_nonblocking_result_e {
  write_nonblocking_result__success = 0,
  write_nonblocking_result__end_of_file,
  write_nonblocking_result__write_failure,
  write_nonblocking_result__select_failure,
  write_nonblocking_result__unknown_failure,
} write_nonblocking_result_t;

typedef enum recv_nonblocking_result_e {
  recv_nonblocking_result__success = 0,
  recv_nonblocking_result__disconnected,
  recv_nonblocking_result__recv_failure,
  recv_nonblocking_result__select_failure,
  recv_nonblocking_result__unknown_failure,
} recv_nonblocking_result_t;

typedef enum send_nonblocking_result_e {
  send_nonblocking_result__success = 0,
  send_nonblocking_result__disconnected,
  send_nonblocking_result__send_failure,
  send_nonblocking_result__select_failure,
  send_nonblocking_result__unknown_failure,
} send_nonblocking_result_t;

read_nonblocking_result_t  read_nonblocking(int fd, void* data, u32 byte_num, u32* bytes_read);
write_nonblocking_result_t write_nonblocking(int fd, void* data, u32 byte_num, u32* bytes_sent);
recv_nonblocking_result_t recv_nonblocking(int socket_fd, void* data, u32 byte_num, u32* bytes_read);
send_nonblocking_result_t send_nonblocking(int socket_fd, void* data, u32 byte_num, u32* bytes_sent);

void                                  circular_buffer__init(circular_buffer_t* this, u32 byte_num);
void                                  circular_buffer__destroy(circular_buffer_t* this);
u32                                   circular_buffer__get_used_byte_num(circular_buffer_t* this);
u32                                   circular_buffer__get_free_byte_num(circular_buffer_t* this);
circular_buffer__seek_ahead_result_t  circular_buffer__seek_ahead(circular_buffer_t* this, u32 byte_num, u32* next_start_place);
circular_buffer__read_result_t        circular_buffer__peek_read(circular_buffer_t* this, void* data, u32 byte_num, u32* next_start_place);
circular_buffer__read_result_t        circular_buffer__read(circular_buffer_t* this, void* data, u32 byte_num);
circular_buffer__write_result_t       circular_buffer__write(circular_buffer_t* this, void* data, u32 byte_num);
circular_buffer__socket_send_result_t circular_buffer__socket_send(circular_buffer_t* this, int socket_fd);
circular_buffer__socket_recv_result_t circular_buffer__socket_recv(circular_buffer_t* this, int socket_fd);
circular_buffer__file_write_result_t  circular_buffer__file_write(circular_buffer_t* this, int fd);
circular_buffer__file_read_result_t   circular_buffer__file_read(circular_buffer_t* this, int fd);

#endif // F2__CIRCULAR_BUFFER__H
