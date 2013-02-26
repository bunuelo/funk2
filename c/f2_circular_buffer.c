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

#include "funk2.h"

void circular_buffer__init(circular_buffer_t* this, u32 byte_num) {
  this->byte_num = byte_num;
  this->start    = 0;
  this->end      = 0;
  this->bytes    = (u8*)from_ptr(f2__malloc(byte_num));
}

void circular_buffer__destroy(circular_buffer_t* this) {
  f2__free(to_ptr(this->bytes));
}

u32 circular_buffer__get_used_byte_num(circular_buffer_t* this) {
  if (this->start <= this->end) {
    return this->end - this->start;
  }
  return (this->end + this->byte_num) - this->start;
}

u32 circular_buffer__get_free_byte_num(circular_buffer_t* this) {
  return this->byte_num - circular_buffer__get_used_byte_num(this) - 1;
}

circular_buffer__seek_ahead_result_t circular_buffer__seek_ahead(circular_buffer_t* this, u32 byte_num, u32* next_start_place) {
  if (circular_buffer__get_used_byte_num(this) < byte_num) {
    return circular_buffer__seek_ahead_result__not_enough_data;
  }
  u32 next_start = this->start + byte_num;
  if (next_start > this->byte_num) {
    next_start -= this->byte_num;
  }
  this->start = next_start;
  if (next_start_place) {*next_start_place = next_start;}
  return circular_buffer__seek_ahead_result__success;
}

circular_buffer__read_result_t circular_buffer__peek_read(circular_buffer_t* this, void* data, u32 byte_num, u32* next_start_place) {
  if (circular_buffer__get_used_byte_num(this) < byte_num) {
    return circular_buffer__read_result__not_enough_data;
  }
  u32 next_start = this->start + byte_num;
  if (next_start >= this->byte_num) {
    next_start -= this->byte_num;
    u32 start_to_loop__byte_num = this->byte_num - this->start;
    memcpy(data, this->bytes + this->start, start_to_loop__byte_num);
    memcpy(data + start_to_loop__byte_num, this->bytes, next_start);
  } else {
    memcpy(data, this->bytes + this->start, byte_num);
  }
  if (next_start_place) {*next_start_place = next_start;}
  return circular_buffer__read_result__success;
}

circular_buffer__read_result_t circular_buffer__read(circular_buffer_t* this, void* data, u32 byte_num) {
  return circular_buffer__peek_read(this, data, byte_num, &(this->start));
}

circular_buffer__write_result_t circular_buffer__write(circular_buffer_t* this, void* data, u32 byte_num) {
  if (circular_buffer__get_free_byte_num(this) < byte_num) {
    return circular_buffer__write_result__not_enough_room;
  }
  u32 next_end = this->end + byte_num;
  if (next_end >= this->byte_num) {
    next_end -= this->byte_num;
    u32 end_to_loop__byte_num = this->byte_num - this->end;
    memcpy(this->bytes + this->end, data, end_to_loop__byte_num);
    memcpy(this->bytes, data + end_to_loop__byte_num, next_end);
  } else {
    memcpy(this->bytes + this->end, data, byte_num);
  }
  this->end = next_end;
  return circular_buffer__write_result__success;
}

typedef enum select_read_result_e {
  select_read_result__no_data,
  select_read_result__data_available,
  select_read_result__signal_caught,
  select_read_result__select_failure
} select_read_result_t;

select_read_result_t select_read(int fd) {
  fd_set         rfds;
  struct timeval tv;
  int            retval;
  
  FD_ZERO(&rfds);
  FD_SET(fd, &rfds);
  
  tv.tv_sec  = 0;
  tv.tv_usec = 0;
  
  retval = select(fd + 1, &rfds, NULL, NULL, &tv);
  
  if (retval == -1) {
    switch(errno) {
    case EBADF:
      status("select_read (fd=%d) failure!  An invalid file descriptor was given in one of the sets.  (Perhaps a file descriptor that was already closed, or one on which an error has occurred.)", fd);
      return select_read_result__select_failure;
    case EINTR:
      //status("select_read (fd=%d) failure!  A signal was caught.", fd);
      return select_read_result__signal_caught;
    case EINVAL:
      status("select_read (fd=%d) failure!  nfds is negative or the value contained within timeout is invalid.", fd);
      break;
    case ENOMEM:
      status("select_read (fd=%d) failure!  unable to allocate memory for internal tables.", fd);
      break;
    default:
      status("select_read (fd=%d) failure!  unknown failure.", fd);
      break;
    }
    return select_read_result__select_failure;
  } else if (retval) {
    //status("select_read (fd=%d) success!  data is ready to read.", fd);
    return select_read_result__data_available;
  }
  return select_read_result__no_data;
}

typedef enum select_write_result_e {
  select_write_result__no_space,
  select_write_result__space_available,
  select_write_result__signal_caught,
  select_write_result__select_failure
} select_write_result_t;

select_read_result_t select_write(int fd) {
  fd_set         wfds;
  struct timeval tv;
  int            retval;
  
  FD_ZERO(&wfds);
  FD_SET(fd, &wfds);
  
  tv.tv_sec  = 0;
  tv.tv_usec = 0;
  
  retval = select(fd + 1, NULL, &wfds, NULL, &tv);
  
  if (retval == -1) {
    switch(errno) {
    case EBADF:
      status("select_write (fd=%d) failure!  An invalid file descriptor was given in one of the sets.  (Perhaps a file descriptor that was already closed, or one on which an error has occurred.)", fd);
      break;
    case EINTR:
      //status("select_write (fd=%d) failure!  A signal was caught.", fd);
      return select_write_result__signal_caught;
    case EINVAL:
      status("select_write (fd=%d) failure!  nfds is negative or the value contained within timeout is invalid.", fd);
      break;
    case ENOMEM:
      status("select_write (fd=%d) failure!  unable to allocate memory for internal tables.", fd);
      break;
    default:
      status("select_write (fd=%d) failure!  unknown failure.", fd);
      break;
    }
    return select_write_result__select_failure;
  } else if (retval) {
    //status("select_write (fd=%d) success!  space is ready to be written.", fd);
    return select_write_result__space_available;
  }
  return select_write_result__no_space;
}

recv_nonblocking_result_t recv_nonblocking(int socket_fd, void* data, u32 byte_num, u32* bytes_read) {
  select_read_result_t select_read_result = select_read(socket_fd);
  switch(select_read_result) {
  case select_read_result__data_available: {
    int recv_result = recv(socket_fd, data, byte_num, 0);
    if (recv_result == 0) {
      *bytes_read = 0;
      //status("recv reports socket disconnected! (1)");
      return recv_nonblocking_result__disconnected;
    } else if (recv_result == -1) {
      *bytes_read = 0;
      switch(errno) {
      case EAGAIN:      // nonblocking socket has no data
	break; // returns success below
      case ECONNRESET:
	//status("recv reports socket disconnected! (2)");
	return recv_nonblocking_result__disconnected;
      default:
	return recv_nonblocking_result__recv_failure;
      }
    } else {
      *bytes_read = recv_result;
      status("recv_nonblocking received data!  (socket_fd=%d, bytes_read=%d)", socket_fd, recv_result);
    }
  } break;
  case select_read_result__no_data:
  case select_read_result__signal_caught:
    *bytes_read = 0;
    break;
  case select_read_result__select_failure:
    status("select failure! (died a nasty death!)");
    return recv_nonblocking_result__select_failure;
  default:
    return recv_nonblocking_result__unknown_failure;
  }
  //status("recv reports success.");
  return recv_nonblocking_result__success;
}

void whoa_time() {
  printf("\nwhoa time.\n"); fflush(stdout);
}

send_nonblocking_result_t send_nonblocking(int socket_fd, void* data, u32 byte_num, u32* bytes_sent) {
  select_write_result_t select_write_result = select_write(socket_fd);
  switch(select_write_result) {
  case select_write_result__space_available: {
    int send_result = send(socket_fd, data, byte_num, 0);
    if (send_result == -1) {
      *bytes_sent = 0;
      switch(errno) {
      case EAGAIN: // nonblocking socket has no space
	break;     // returns success below
      case ECONNRESET:
	//status("send reports socket disconnected!");
	status("send_nonblocking disconnected!  (socket_fd=%d)", socket_fd);
	return send_nonblocking_result__disconnected;
      default:
	status("send_nonblocking failure!  (socket_fd=%d)", socket_fd);
	return send_nonblocking_result__send_failure;
      }
    } else {
      *bytes_sent = send_result;
      if (send_result == 128) {
	whoa_time();
      }
      status("send_nonblocking sent data!  (socket_fd=%d, bytes_sent=%d)", socket_fd, send_result);
    }
  } break;
  case select_write_result__no_space:
  case select_write_result__signal_caught:
    *bytes_sent = 0;
    break;
  case select_write_result__select_failure:
    status("send_nonblocking select failure!  (socket_fd=%d)", socket_fd);
    return send_nonblocking_result__select_failure;
  default:
    status("send_nonblocking unknown failure!  (socket_fd=%d)", socket_fd);
    return send_nonblocking_result__unknown_failure;
  }
  //status("send reports success.");
  return send_nonblocking_result__success;
}

read_nonblocking_result_t read_nonblocking(int fd, void* data, u32 byte_num, u32* bytes_read) {
  if (byte_num == 0) {
    if (bytes_read) {*bytes_read = 0;}
    return read_nonblocking_result__success;
  }
  select_read_result_t select_read_result = select_read(fd);
  switch(select_read_result) {
  case select_read_result__data_available: {
    //printf("\n  trying to read %d bytes.", byte_num);
    int read_result = read(fd, data, byte_num);
    if (read_result == 0) {
      *bytes_read = 0;
      return read_nonblocking_result__end_of_file;
    } else if (read_result == -1) {
      *bytes_read = 0;
      switch(errno) {
      case EAGAIN: // nonblocking file has no data
	break;     // returns success below
      case ECONNRESET:
	status("send_nonblocking disconnected!  (socket_fd=%d)", fd);
	return read_nonblocking_result__read_failure;
      default:
	status("read_nonblocking failure!  (socket_fd=%d)", fd);
	return read_nonblocking_result__read_failure;
      }
    } else {
      *bytes_read = read_result;
    }
  } break;
  case select_read_result__no_data:
    *bytes_read = 0;
    break;
  case select_read_result__select_failure:
    status("read_nonblocking select failure!  (socket_fd=%d)", fd);
    return read_nonblocking_result__select_failure;
  default:
    status("send_nonblocking unknown failure!  (socket_fd=%d)", fd);
    return read_nonblocking_result__unknown_failure;
  }
  return read_nonblocking_result__success;
}

write_nonblocking_result_t write_nonblocking(int fd, void* data, u32 byte_num, u32* bytes_sent) {
  if (byte_num == 0) {
    if (bytes_sent) {*bytes_sent = 0;}
    return write_nonblocking_result__success;
  }
  select_write_result_t select_write_result = select_write(fd);
  switch(select_write_result) {
  case select_write_result__space_available: {
    int write_result = write(fd, data, byte_num);
    if (write_result == -1) {
      *bytes_sent = 0;
      switch(errno) {
      case EAGAIN: // nonblocking file has no buffer space
	break;     // returns success below
      case EFBIG:      // file too big
      case ENOSPC:     // no space left on device
      case ECONNRESET: // disconnected (pipe/socket)
      default:
	return write_nonblocking_result__write_failure;
      }
    } else {
      *bytes_sent = write_result;
    }
  } break;
  case select_write_result__no_space:
    *bytes_sent = 0;
    break;
  case select_write_result__select_failure:
    status("select failure!");
    return write_nonblocking_result__select_failure;
  default:
    return write_nonblocking_result__unknown_failure;
  }
  return write_nonblocking_result__success;
}

circular_buffer__socket_recv_result_t circular_buffer__socket_recv(circular_buffer_t* this, int socket_fd) {
  u32 byte_num_to_recv = circular_buffer__get_free_byte_num(this);
  if (byte_num_to_recv == 0) {
    return circular_buffer__socket_recv_result__connected;
  }
  u32 next_end = this->end + byte_num_to_recv;
  u32 total_byte_num_recv = 0;
  u32 bytes_read = 0;
  if (next_end >= this->byte_num) {
    next_end -= this->byte_num;
    u32 end_to_loop__byte_num = this->byte_num - this->end;
    {
      recv_nonblocking_result_t recv_result = recv_nonblocking(socket_fd, this->bytes + this->end, end_to_loop__byte_num, &bytes_read);
      if ((recv_result == recv_nonblocking_result__disconnected) ||
	  (recv_result == recv_nonblocking_result__select_failure)) {
	status("circular_buffer__socket_recv error: disconnecting!  (socket_fd=%d)", socket_fd);
	return circular_buffer__socket_recv_result__disconnected;
      }
    }
    total_byte_num_recv += bytes_read;
    if (total_byte_num_recv == end_to_loop__byte_num) {
      recv_nonblocking_result_t recv_result = recv_nonblocking(socket_fd, this->bytes, next_end, &bytes_read);
      if ((recv_result == recv_nonblocking_result__disconnected) ||
	  (recv_result == recv_nonblocking_result__select_failure)) {
	status("circular_buffer__socket_recv error: disconnecting!  (socket_fd=%d)", socket_fd);
	return circular_buffer__socket_recv_result__disconnected;
      }
      total_byte_num_recv += bytes_read;
    }
  } else {
    recv_nonblocking_result_t recv_result = recv_nonblocking(socket_fd, this->bytes + this->end, byte_num_to_recv, &bytes_read);
    if ((recv_result == recv_nonblocking_result__disconnected) ||
	(recv_result == recv_nonblocking_result__select_failure)) {
      status("circular_buffer__socket_recv error: disconnecting!  (socket_fd=%d)", socket_fd);
      return circular_buffer__socket_recv_result__disconnected;
    }
    total_byte_num_recv += bytes_read;
  }
  next_end = this->end + total_byte_num_recv;
  if (next_end >= this->byte_num) {
    next_end -= this->byte_num;
  }
  this->end = next_end;
  return circular_buffer__socket_recv_result__connected;
}

circular_buffer__socket_send_result_t circular_buffer__socket_send(circular_buffer_t* this, int socket_fd) {
  u32 byte_num_to_send = circular_buffer__get_used_byte_num(this);
  if (byte_num_to_send == 0) {
    return circular_buffer__socket_send_result__connected;
  }
  u32 next_start = this->start + byte_num_to_send;
  u32 total_byte_num_send = 0;
  u32 bytes_sent = 0;
  if (next_start >= this->byte_num) {
    next_start -= this->byte_num;
    u32 start_to_loop__byte_num = this->byte_num - this->start;
    if (send_nonblocking(socket_fd, this->bytes + this->start, start_to_loop__byte_num, &bytes_sent) == send_nonblocking_result__disconnected) {
      status("circular_buffer__socket_send error: disconnected!  (socket_fd=%d)", socket_fd);
      return circular_buffer__socket_send_result__disconnected;
    }
    total_byte_num_send += bytes_sent;
    if (total_byte_num_send == start_to_loop__byte_num) {
      if (send_nonblocking(socket_fd, this->bytes, next_start, &bytes_sent) == send_nonblocking_result__disconnected) {
	status("circular_buffer__socket_send error: disconnected!  (socket_fd=%d)", socket_fd);
	return circular_buffer__socket_send_result__disconnected;
      }
      total_byte_num_send += bytes_sent;
    }
  } else {
    if (send_nonblocking(socket_fd, this->bytes + this->start, byte_num_to_send, &bytes_sent) == send_nonblocking_result__disconnected) {
      status("circular_buffer__socket_send error: disconnected!  (socket_fd=%d)", socket_fd);
      return circular_buffer__socket_send_result__disconnected;
    }
    total_byte_num_send += bytes_sent;
  }
  next_start = this->start + total_byte_num_send;
  if (next_start >= this->byte_num) {
    next_start -= this->byte_num;
  }
  this->start = next_start;
  return circular_buffer__socket_send_result__connected;
}

circular_buffer__file_read_result_t circular_buffer__file_read(circular_buffer_t* this, int fd) {
  u32 byte_num_to_read = circular_buffer__get_free_byte_num(this);
  if (byte_num_to_read == 0) {
    return circular_buffer__file_read_result__success;
  }
  u32 next_end = this->end + byte_num_to_read;
  u32 total_byte_num_read = 0;
  u32 bytes_read = 0;
  if (next_end >= this->byte_num) {
    next_end -= this->byte_num;
    u32 end_to_loop__byte_num = this->byte_num - this->end;
    if (read_nonblocking(fd, this->bytes + this->end, end_to_loop__byte_num, &bytes_read) == read_nonblocking_result__end_of_file) {
      return circular_buffer__file_read_result__end_of_file;
    }
    total_byte_num_read += bytes_read;
    if (total_byte_num_read == end_to_loop__byte_num) {
      if (read_nonblocking(fd, this->bytes, next_end, &bytes_read) == read_nonblocking_result__end_of_file) {
	return circular_buffer__file_read_result__end_of_file;
      }
      total_byte_num_read += bytes_read;
    }
  } else {
    if (read_nonblocking(fd, this->bytes + this->end, byte_num_to_read, &bytes_read) == read_nonblocking_result__end_of_file) {
      return circular_buffer__file_read_result__end_of_file;
    }
    total_byte_num_read += bytes_read;
  }
  next_end = this->end + total_byte_num_read;
  if (next_end >= this->byte_num) {
    next_end -= this->byte_num;
  }
  this->end = next_end;
  return circular_buffer__file_read_result__success;
}

circular_buffer__file_write_result_t circular_buffer__file_write(circular_buffer_t* this, int fd) {
  u32 byte_num_to_write = circular_buffer__get_used_byte_num(this);
  if (byte_num_to_write == 0) {
    return circular_buffer__file_write_result__success;
  }
  u32 next_start = this->start + byte_num_to_write;
  u32 total_byte_num_write = 0;
  u32 bytes_sent = 0;
  if (next_start >= this->byte_num) {
    next_start -= this->byte_num;
    u32 start_to_loop__byte_num = this->byte_num - this->start;
    if (write_nonblocking(fd, this->bytes + this->start, start_to_loop__byte_num, &bytes_sent) == write_nonblocking_result__end_of_file) {
      return circular_buffer__file_write_result__end_of_file;
    }
    total_byte_num_write += bytes_sent;
    if (total_byte_num_write == start_to_loop__byte_num) {
      if (write_nonblocking(fd, this->bytes, next_start, &bytes_sent) == write_nonblocking_result__end_of_file) {
	return circular_buffer__file_write_result__end_of_file;
      }
      total_byte_num_write += bytes_sent;
    }
  } else {
    if (write_nonblocking(fd, this->bytes + this->start, byte_num_to_write, &bytes_sent) == write_nonblocking_result__end_of_file) {
      return circular_buffer__file_write_result__end_of_file;
    }
    total_byte_num_write += bytes_sent;
  }
  next_start = this->start + total_byte_num_write;
  if (next_start >= this->byte_num) {
    next_start -= this->byte_num;
  }
  this->start = next_start;
  return circular_buffer__file_write_result__success;
}

